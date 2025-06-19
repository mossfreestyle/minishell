/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 11:52:12 by mfernand          #+#    #+#             */
/*   Updated: 2025/06/19 14:52:40 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	r_input(t_redirect *redir);
static void	r_output(t_redirect *redir);
static void	r_append(t_redirect *redir);
static void	r_heredoc(t_command *cmd);

void	handle_redirections(t_command *cmd)
{
	t_redirect	*redir;

	redir = cmd->redirects;
	while (redir)
	{
		if (redir->type == R_INPUT)
			r_input(redir);
		else if (redir->type == R_OUTPUT)
			r_output(redir);
		else if (redir->type == R_APPEND)
			r_append(redir);
		else if (redir->type == R_HEREDOC)
			r_heredoc(cmd);
		redir = redir->next;
	}
}

static void	r_input(t_redirect *redir)
{
	int	fd;

	fd = open(redir->filename, O_RDONLY);
	if (fd < 0)
		perror(redir->filename);
	else
	{
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			perror("dup2");
			close(fd);
			exit(1);
		}
		close(fd);
	}
}

static void	r_output(t_redirect *redir)
{
	int	fd;

	fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		perror(redir->filename);
	else
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			perror("dup2");
			close(fd);
			exit(1);
		}
		close(fd);
	}
}

static void	r_append(t_redirect *redir)
{
	int	fd;

	fd = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		perror(redir->filename);
	else
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			perror("dup2");
			close(fd);
			exit(1);
		}
		close(fd);
	}
}

static void	r_heredoc(t_command *cmd)
{
	if (dup2(cmd->heredoc_fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		close(cmd->heredoc_fd);
		exit(1);
	}
	close(cmd->heredoc_fd);
}
