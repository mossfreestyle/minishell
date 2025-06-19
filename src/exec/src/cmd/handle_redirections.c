/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 11:52:12 by mfernand          #+#    #+#             */
/*   Updated: 2025/06/19 14:10:55 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	r_input(int fd, t_shell *shell);
static void	r_output(int fd, t_shell *shell);
static void	r_append(int fd, t_shell *shell);
static void	r_heredoc(int fd, t_shell *shell);

void	handle_redirections(t_shell *shell)
{
	int			fd;
    t_redirect *redir = shell->cmd_list->redirects;

    
	while (redir)
	{
		if (redir->type == R_INPUT)
            r_input(fd, shell);
		else if (redir->type == R_OUTPUT)
            r_output(fd, shell);
		else if (redir->type == R_APPEND)
            r_append(fd, shell);
		else if (redir->type == R_HEREDOC)
            r_heredoc(fd, shell);
		redir = redir->next;
	}
}

static void	r_input(int fd, t_shell *shell)
{
	fd = open(shell->cmd_list->redirects->filename, O_RDONLY);
	if (fd < 0)
		perror(shell->cmd_list->redirects->filename);
	dup2(fd, STDIN_FILENO);
	close(fd);
}

static void	r_output(int fd, t_shell *shell)
{
	fd = open(shell->cmd_list->redirects->filename,
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		perror(shell->cmd_list->redirects->filename);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

static void	r_append(int fd, t_shell *shell)
{
	fd = open(shell->cmd_list->redirects->filename,
			O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		perror(shell->cmd_list->redirects->filename);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

static void	r_heredoc(int fd, t_shell *shell)
{
	dup2(shell->cmd_list->heredoc_fd, STDIN_FILENO);
	close(shell->cmd_list->heredoc_fd);
}