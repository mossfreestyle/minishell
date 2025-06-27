/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwassim <rwassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 20:55:36 by mfernand          #+#    #+#             */
/*   Updated: 2025/06/27 22:18:23 by rwassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	res_readline(int res, t_command *cmd, t_shell *shell)
{
	if (res == -1)
	{
		free_commands(cmd);
		shell->cmd_list = NULL;
		return (-1);
	}
	return (0);
}

void	end_safe_redir(t_shell *shell)
{
	if (dup2(shell->saved_stdout, STDOUT_FILENO) == -1)
	{
		perror("dup2 stdout");
		if (shell->saved_stdin)
			close(shell->saved_stdin);
		if (shell->saved_stdout)
			close(shell->saved_stdout);
		free_shell(shell);
		exit(1);
	}
	if (dup2(shell->saved_stdin, STDIN_FILENO) == -1)
	{
		perror("dup2 stdin");
		if (shell->saved_stdout > 2)
			close(shell->saved_stdout);
		if (shell->saved_stdin > 2)
			close(shell->saved_stdin);
		free_shell(shell);
		exit(1);
	}
	if (shell->saved_stdout)
		close(shell->saved_stdout);
	if (shell->saved_stdin)
		close(shell->saved_stdin);
}

void	only_one_builtin(t_shell *shell, t_command *cmd)
{
	shell->saved_stdout = dup(STDOUT_FILENO);
	if (shell->saved_stdout == -1)
		return (perror("dup"), shell->exit_status = 1, (void)0);
	shell->saved_stdin = dup(STDIN_FILENO);
	if (shell->saved_stdin == -1)
	{
		perror("dup");
		close(shell->saved_stdout);
		shell->exit_status = 1;
		return ;
	}
	else if (!ft_strcmp(cmd->name, "exit"))
		check_exit(shell, cmd, shell->saved_stdout, shell->saved_stdin);
	else
	{
		if (handle_redirections(cmd, shell) != -1)
			shell->exit_status = exec_built_in(cmd, shell, NULL, NULL);
	}
	end_safe_redir(shell);
}

void	reset_sig(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	close_write_fd_and_free_line(int write_fd, char *line)
{
	if (line)
		free(line);
	if (write_fd >= 3)
		close(write_fd);
}
