/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 10:46:17 by mfernand          #+#    #+#             */
/*   Updated: 2025/06/23 11:41:28 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_child(t_shell *sh, t_command *cmd, int i, char *full_path);
static void	close_and_wait(t_shell *shell, int status);
static void	error(char **envp, char *full_path, t_shell *shell, int flag);
static void	exec(t_command *cmd, char **envp, char *full_path, t_shell *shell);

int	exec_commands(t_shell *shell)
{
	int			i;
	t_command	*cmd;
	pid_t		pid;
	char		**envp;
	char		*path;

	i = 0;
	cmd = shell->cmd_list;
	init_pipes(shell);
	while (cmd)
	{
		envp = env_list_to_array(shell->env_vars);
		path = find_path(cmd->name, envp);
		pid = fork();
		check_pid(pid, shell);
		if (pid == 0)
			exec_child(shell, cmd, i, path);
		error(envp, path, shell, 0);
		cmd = cmd->next;
		i++;
	}
	close_and_wait(shell, 0);
	return (shell->exit_status);
}

static void	exec_child(t_shell *sh, t_command *cmd, int i, char *path)
{
	char	**envp;

	envp = env_list_to_array(sh->env_vars);
	if (i > 0 && sh->pipeline.n_pipes > 0 && dup2(sh->pipeline.pipefd[i - 1][0],
		STDIN_FILENO) == -1)
		error(envp, path, sh, 1);
	if (cmd->next && sh->pipeline.n_pipes > 0 && dup2(sh->pipeline.pipefd[i][1],
		STDOUT_FILENO) == -1)
		error(envp, path, sh, 1);
	handle_redirections(cmd);
	close_all_pipes(sh);
	exec(cmd, envp, path, sh);
	error(envp, path, sh, 1);
}

static void	close_and_wait(t_shell *shell, int status)
{
	close_all_pipes(shell);
	while (wait(&status) > 0)
		if (WIFEXITED(status))
			shell->exit_status = WEXITSTATUS(status);
}

static void	error(char **envp, char *full_path, t_shell *shell, int flag)
{
	if (envp)
		free_array(envp);
	if (full_path)
		free(full_path);
	if (flag)
	{
		close_all_pipes(shell);
		print_error(shell->cmd_list->name);
		exit(127);
	}
}

static void	exec(t_command *cmd, char **envp, char *full_path, t_shell *shell)
{
	if (is_builtin(cmd->name))
		exit(exec_built_in(cmd, shell));
	else if (full_path)
		execve(full_path, cmd->args, envp);
	error(envp, full_path, shell, 1);
}
