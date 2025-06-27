/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwassim <rwassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 21:57:16 by rwassim           #+#    #+#             */
/*   Updated: 2025/06/27 22:37:16 by rwassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_nb_pipe(t_shell *shell, t_command *cmd)
{
	if (count_cmds(cmd) > 5)
	{
		ft_putendl_fd("minishell: too many pipes", 2);
		shell->exit_status = 1;
		free_commands(cmd);
		return (1);
	}
	return (0);
}

void	put_heredoc(int should_expand, char *line, t_shell *shell, int write_fd)
{
	char	*processed_line;

	if (should_expand)
	{
		processed_line = expand_heredoc_line(line, shell);
		ft_putendl_fd(processed_line, write_fd);
		free(processed_line);
	}
	else
		ft_putendl_fd(line, write_fd);
}

void	close_unused_heredoc_fds(t_command *cmd)
{
	t_redirect	*redir;
	int			last_fd;

	while (cmd)
	{
		last_fd = -1;
		redir = cmd->redirects;
		while (redir)
		{
			if (redir->type == R_HEREDOC && cmd->heredoc_fd != -1)
				last_fd = cmd->heredoc_fd;
			redir = redir->next;
		}
		if (last_fd != -1 && cmd->heredoc_fd != -1
			&& cmd->heredoc_fd != last_fd)
		{
			close(cmd->heredoc_fd);
			cmd->heredoc_fd = -1;
		}
		cmd = cmd->next;
	}
}

void	check_sig(int status, t_shell *shell)
{
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
		{
			shell->exit_status = 130;
			ft_putchar_fd('\n', STDERR_FILENO);
		}
		else if (WTERMSIG(status) == SIGQUIT)
		{
			shell->exit_status = 131;
			ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
		}
	}
	else if (WIFEXITED(status))
		shell->exit_status = WEXITSTATUS(status);
	else
		shell->exit_status = 1;
}
