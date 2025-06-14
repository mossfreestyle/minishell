/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 23:33:18 by mfernand          #+#    #+#             */
/*   Updated: 2025/06/02 11:06:32 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	check_errors(t_fds *fds, int pipe_res, char **av)
{
	(void)av;
	if (fds->fd_in < 0)
		return (close_all(fds), 1);
	if (fds->fd_out < 0)
		return (close_all(fds), 1);
	if (pipe_res == -1)
	{
		if (fds->fd_in >= 0)
			close(fds->fd_in);
		if (fds->fd_out >= 0)
			close(fds->fd_out);
		ft_putstr_fd("Terminated\n", 2);
		return (EXIT_FAILURE);
	}
	return (0);
}

int	check_arg(int ac)
{
	if (ac != 5)
	{
		ft_putstr_fd("Wrong number of arguments\n", 2);
		exit(EXIT_FAILURE);
	}
	return (0);
}

void	close_all(t_fds *fds)
{
	if (fds->fd_in >= 0)
		close(fds->fd_in);
	if (fds->fd_out >= 0)
		close(fds->fd_out);
	if (fds->fd[0] >= 0)
		close(fds->fd[0]);
	if (fds->fd[1] >= 0)
		close(fds->fd[1]);
}
