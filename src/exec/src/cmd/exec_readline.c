/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_readline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwassim <rwassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 10:53:55 by mfernand          #+#    #+#             */
/*   Updated: 2025/06/20 14:06:06 by rwassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_last_command(t_shell *shell);
static int	exec_last_builtin(t_shell *shell, t_cmd *cmd);
static int	exec_last_external(t_shell *shell, t_cmd *cmd);

int	exec_readline(t_shell *shell)
{
	t_command	*cmd;
	t_redirect	*redir;

	if (!shell->cmd_list)
		return (0);
	cmd = shell->cmd_list;
	while (cmd)
	{
		redir = cmd->redirects;
		while (redir)
		{
			if (redir->type == R_HEREDOC)
				exec_here_doc(cmd, redir->filename);
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	if (!shell->cmd_list)
		return ;
	if (!shell->cmd_list->next)
		shell->exit_status = exec_last_command(shell);
	else
		shell->exit_status = exec_commands(shell);
	return (shell->exit_status);
}

static int	exec_last_command(t_shell *shell)
{
	t_cmd	*cmd;

	cmd = shell->cmd_list;
	while (cmd && cmd->next)
		cmd = cmd->next;
	if (!cmd)
		return (1);
	if (is_builtin(cmd->argv[0]))
		return (exec_last_builtin(shell, cmd));
	else
		return (exec_last_external(shell, cmd));
}

static int	exec_last_builtin(t_shell *shell, t_cmd *cmd)
{
	int	status;

	handle_redirections(cmd);
	status = exec_builtin(shell, cmd);
	restore_redirections(cmd);
	shell->exit_status = status;
	return (status);
}

static int	exec_last_external(t_shell *shell, t_cmd *cmd)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (1);
	}
	if (pid == 0)
	{
		handle_redirections(cmd);
		execve(cmd->path, cmd->argv, shell->envp);
		perror("execve");
		exit(127);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		shell->exit_status = WEXITSTATUS(status);
	else
		shell->exit_status = 1;
	return (shell->exit_status);
}
