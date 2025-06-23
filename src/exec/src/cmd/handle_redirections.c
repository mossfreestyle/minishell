/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 11:52:12 by mfernand          #+#    #+#             */
/*   Updated: 2025/06/23 21:59:10 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	r_input(t_redirect *redir);
static int	r_output(t_redirect *redir);
static int	r_append(t_redirect *redir);
static void	r_heredoc(t_command *cmd);

int	handle_redirections(t_command *cmd)
{
	t_redirect	*redir;
	t_redirect	*last_heredoc;
	int			res;

	if (!cmd || !cmd->name)
		return (-1);
	redir = cmd->redirects;
	last_heredoc = NULL;
	res = 0;
	while (redir)
	{
		if (redir->type == R_INPUT)
			res = r_input(redir);
		else if (redir->type == R_OUTPUT)
			res = r_output(redir);
		else if (redir->type == R_APPEND)
			res = r_append(redir);
		else if (redir->type == R_HEREDOC)
			last_heredoc = redir;
		redir = redir->next;
		if (res == -1)
			return (-1);
	}
	if (last_heredoc)
		r_heredoc(cmd);
	return (0);
}

static int	r_input(t_redirect *redir)
{
	int	fd;

	fd = open(redir->filename, O_RDONLY);
	if (fd < 0)
	{
		perror(redir->filename);
		return (-1);
	}
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
	return (0);
}

static int	r_output(t_redirect *redir)
{
	int	fd;

	fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror(redir->filename);
		return (-1);
	}
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
	return (0);
}

static int	r_append(t_redirect *redir)
{
	int	fd;

	fd = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		perror(redir->filename);
		return (-1);
	}
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
	return (0);
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
