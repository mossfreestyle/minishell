/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwassim <rwassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 11:52:12 by mfernand          #+#    #+#             */
/*   Updated: 2025/06/27 22:37:03 by rwassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		r_input(t_redirect *redir, t_shell *shell);
int		r_output(t_redirect *redir, t_shell *shell);
int		r_append(t_redirect *redir, t_shell *shell);
void	r_heredoc(t_command *cmd, t_shell *shell);

int	handle_redirections(t_command *cmd, t_shell *shell)
{
	t_redirect	*redir;
	t_redirect	*last_heredoc;
	int			res;

	if (!cmd)
		return (-1);
	redir = cmd->redirects;
	last_heredoc = NULL;
	while (redir)
	{
		res = process_redirect(redir, shell, &last_heredoc);
		if (res == -1)
			return (-1);
		redir = redir->next;
	}
	if (last_heredoc)
		r_heredoc(cmd, shell);
	return (0);
}

int	r_input(t_redirect *redir, t_shell *shell)
{
	int	fd;

	fd = open(redir->filename, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(redir->filename, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (-1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		free_shell(shell);
		exit(1);
	}
	close(fd);
	return (0);
}

int	r_output(t_redirect *redir, t_shell *shell)
{
	int	fd;

	fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror(redir->filename);
		shell->exit_status = 1;
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		free_shell(shell);
		shell->exit_status = 1;
		return (-1);
	}
	close(fd);
	return (0);
}

int	r_append(t_redirect *redir, t_shell *shell)
{
	int	fd;

	fd = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		perror(redir->filename);
		shell->exit_status = 1;
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		free_shell(shell);
		shell->exit_status = 1;
		return (-1);
	}
	close(fd);
	return (0);
}

void	r_heredoc(t_command *cmd, t_shell *shell)
{
	if (dup2(cmd->heredoc_fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		close(cmd->heredoc_fd);
		free_shell(shell);
		exit(1);
	}
	close(cmd->heredoc_fd);
}
