/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 19:28:38 by mfernand          #+#    #+#             */
/*   Updated: 2025/05/31 00:31:42 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	set_here_doc(char *keyword, int fd, int start_cmd, char **av)
{
	char	*line;
	int		count;

	count = 0;
	while (1)
	{
		while (count++ < len(av) - start_cmd - 1)
			ft_putstr_fd("pipe ", 1);
		count = 0;
		ft_putstr_fd("heredoc> ", 1);
		line = get_next_line(0);
		if (!line)
			break ;
		if (ft_strncmp(line, keyword, ft_strlen(keyword)) == 0
			&& line[ft_strlen(keyword)] == '\n'
			&& ft_strlen(line) == ft_strlen(keyword) + 1)
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, fd);
		free(line);
	}
}

void	handle_here_doc(char **av, int *fd_in, int *fd_out, int *start_cmd)
{
	int	tmp_pipe[2];

	if (pipe(tmp_pipe) == -1)
	{
		ft_putstr_fd("Pipe error\n", 2);
		exit(EXIT_FAILURE);
	}
	set_here_doc(av[2], tmp_pipe[1], *start_cmd, av);
	close(tmp_pipe[1]);
	*fd_in = tmp_pipe[0];
	*fd_out = open_file(av[len(av)], 0);
	*start_cmd = 3;
}
