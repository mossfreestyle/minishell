/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 20:55:36 by mfernand          #+#    #+#             */
/*   Updated: 2025/06/24 21:18:23 by mfernand         ###   ########.fr       */
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

void	end_safe_redir(int saved_stdin, int saved_stdout, t_shell *shell)
{
	if (dup2(saved_stdout, STDOUT_FILENO) == -1)
	{
		perror("saved_stdout");
		free_shell(shell);
		exit(1);
	}
	if (dup2(saved_stdin, STDIN_FILENO) == -1)
	{
		if (saved_stdout)
			close(saved_stdout);
		perror("saved_stdout");
		free_shell(shell);
		exit(1);
	}
	close(saved_stdout);
	close(saved_stdin);
}

void	only_one_builtin(t_shell *shell, t_command *cmd)
{
	int	saved_stdout;
	int	saved_stdin;

	saved_stdout = dup(STDOUT_FILENO);
	saved_stdin = dup(STDIN_FILENO);
	if (handle_redirections(cmd, shell) != -1)
		shell->exit_status = exec_built_in(cmd, shell);
	end_safe_redir(saved_stdin, saved_stdout, shell);
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
	if (write_fd)
		close(write_fd);
}
