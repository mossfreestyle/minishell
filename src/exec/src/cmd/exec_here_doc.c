/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_here_doc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 11:14:03 by mfernand          #+#    #+#             */
/*   Updated: 2025/06/19 13:11:36 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_here_doc(char *name)
{
	if (!name)
		return (0);
	return (!ft_strcmp(name, "<<"));
}

int	exec_here_doc(t_shell *shell)
{
	int		heredoc_pipe[2];
	char	*line;

	if (pipe(heredoc_pipe) == -1)
		return (perror("pipe"), -1);
	line = NULL;
	while (1)
	{
		line = readline("> ");
		if (!line || !ft_strcmp(line, shell->cmd_list->redirects->filename))
			break ;
		write(heredoc_pipe[1], line, ft_strlen(line));
		write(heredoc_pipe[1], "\n", 1);
		free(line);
	}
	free(line);
	close(heredoc_pipe[1]);
	shell->cmd_list->heredoc_fd = heredoc_pipe[0];
		// À utiliser dans handle_redirections
	return (0);
}
