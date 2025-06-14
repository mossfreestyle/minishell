/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 21:19:06 by mfernand          #+#    #+#             */
/*   Updated: 2025/05/31 00:31:44 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	bonus_check_errors(int fd_in, int fd_out, int ac, int pipe_res)
{
	if (ac < 5)
	{
		ft_putstr_fd("Wrong number of arguments\n", 2);
		return (EXIT_FAILURE);
	}
	if (fd_in < 0 || fd_out < 0)
	{
		ft_putstr_fd("An error occured when opening files\n", 2);
		return (EXIT_FAILURE);
	}
	if (pipe_res == -1)
	{
		ft_putstr_fd("Pipe error\n", 2);
		return (EXIT_FAILURE);
	}
	return (0);
}
