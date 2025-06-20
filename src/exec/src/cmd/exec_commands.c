/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwassim <rwassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 10:46:17 by mfernand          #+#    #+#             */
/*   Updated: 2025/06/20 11:32:30 by rwassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	close_and_wait(t_shell *shell, int status);
static void	error(char **envp, char *full_path, t_shell *shell);
static void	exec(t_command *cmd, char **envp, char **full_path);

int	exec_commands(t_shell *shell)
{
	int		i;
	pid_t	pid;
	char	**envp;
	char	*full_path;
	int		status;
	t_cmd	*cmd;

	i = 0;
	status = 0;
	cmd = shell->cmd_list;
	init_pipes(shell);
	while (cmd)
	{
		envp = env_list_to_array(shell->env_vars);
		full_path = find_path(cmd->name, envp);
		pid = fork();
		check_pid(pid, shell);
		if (pid == 0)
		{
			if (i > 0 && shell->pipeline.n_pipes > 0)
				if (dup2(shell->pipeline.pipefd[i - 1][0], STDIN_FILENO) == -1)
					error(envp, full_path, shell, 1);
			if (cmd->next && shell->pipeline.n_pipes > 0)
				if (dup2(shell->pipeline.pipefd[i][1], STDOUT_FILENO) == -1)
					error(envp, full_path, shell, 1);
			exec(cmd, envp, full_path);
		}
		error(envp, full_path, shell, 0);
		cmd = cmd->next;
		i++;
	}
	return (close_and_wait(shell, status), shell->exit_status);
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
		perror("minishell");
		exit(127);
	}
}

static void	exec(t_command *cmd, char **envp, char **full_path)
{
	close_all_pipes(shell);
	handle_redirections(cmd);
	if (is_builtin(cmd->name))
		exit(exec_built_in(shell));
	else if (full_path)
		execve(full_path, cmd->args, envp);
	error(envp, full_path, shell);
}