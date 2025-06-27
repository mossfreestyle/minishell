/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwassim <rwassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 10:46:17 by mfernand          #+#    #+#             */
/*   Updated: 2025/06/27 21:56:21 by rwassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_child(t_shell *sh, t_command *cmd, int i);
static void	close_and_wait(t_shell *shell, int status);
static void	error(char **envp, char *full_path, t_shell *shell, t_command *cmd);
static void	exec(t_command *cmd, char **envp, char *full_path, t_shell *shell);

int	exec_commands(t_shell *shell)
{
	int			i;
	t_command	*cmd;
	pid_t		pid;

	i = 0;
	cmd = shell->cmd_list;
	init_pipes(shell);
	while (cmd)
	{
		if (cmd->name)
		{
			pid = fork();
			check_pid(pid, shell);
			if (pid == 0)
				exec_child(shell, cmd, i);
			i++;
		}
		cmd = cmd->next;
	}
	close_and_wait(shell, 0);
	return (shell->exit_status);
}

static void	exec_child(t_shell *sh, t_command *cmd, int i)
{
	char	**envp;
	char	*path;

	envp = env_list_to_array(sh->env_vars);
	if (!envp)
		exit(free_shell(sh));
	path = find_path(cmd->name, envp);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (i > 0 && sh->pipeline.n_pipes > 0 && dup2(sh->pipeline.pipefd[i - 1][0],
		STDIN_FILENO) == -1)
		error(envp, path, sh, cmd);
	if (cmd->next && sh->pipeline.n_pipes > 0 && dup2(sh->pipeline.pipefd[i][1],
		STDOUT_FILENO) == -1)
		error(envp, path, sh, cmd);
	if (handle_redirections(cmd, sh) == -1)
	{
		free_envp_path(envp, path);
		free_shell(sh);
		exit(1);
	}
	close_all_pipes(sh);
	exec(cmd, envp, path, sh);
	error(envp, path, sh, cmd);
}

static void	close_and_wait(t_shell *shell, int status)
{
	int	nb_cmds;
	int	i;
	int	last_status;

	close_all_pipes(shell);
	nb_cmds = count_cmds(shell->cmd_list);
	i = -1;
	last_status = 0;
	while (++i < nb_cmds)
	{
		wait(&status);
		if (i == nb_cmds - 1)
			last_status = status;
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGQUIT)
			ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
	}
	if (WIFEXITED(last_status))
		shell->exit_status = WEXITSTATUS(last_status);
	else if (WIFSIGNALED(last_status))
		shell->exit_status = 128 + WTERMSIG(last_status);
}

static void	error(char **envp, char *full_path, t_shell *shell, t_command *cmd)
{
	free_envp_path(envp, full_path);
	close_all_pipes(shell);
	print_error(cmd->name);
	free_shell(shell);
	exit(127);
}

static void	exec(t_command *cmd, char **envp, char *full_path, t_shell *shell)
{
	int	status;

	status = 0;
	if (is_builtin(cmd->name))
	{
		status = exec_built_in(cmd, shell, envp, full_path);
		free_shell(shell);
		free_envp_path(envp, full_path);
		exit(status);
	}
	else if (full_path)
		execve(full_path, cmd->args, envp);
	error(envp, full_path, shell, cmd);
}
