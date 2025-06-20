/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_here_doc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwassim <rwassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 11:14:03 by mfernand          #+#    #+#             */
/*   Updated: 2025/06/20 15:27:52 by rwassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_here_doc(char *name)
{
	if (!name)
		return (0);
	return (!ft_strcmp(name, "<<"));
}

int	exec_here_doc(t_command *cmd, t_redirect *redir)
{
	int		heredoc_pipe[2];
	char	*line;

	if (pipe(heredoc_pipe) == -1)
		return (perror("pipe"), -1);
	line = NULL;
	while (1)
	{
		line = readline("> ");
		if (!line || !ft_strcmp(line, redir->filename))
			break ;
		write(heredoc_pipe[1], line, ft_strlen(line));
		write(heredoc_pipe[1], "\n", 1);
		free(line);
	}
	free(line);
	close(heredoc_pipe[1]);
	cmd->heredoc_fd = heredoc_pipe[0];
	return (0);
}
