/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 19:59:49 by mfernand          #+#    #+#             */
/*   Updated: 2025/05/31 00:35:38 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	open_file(char *av, int i)
{
	int	file;

	file = 0;
	if (i == 0)
		file = open(av, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (i == 1)
		file = open(av, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (i == 2)
		file = open(av, O_RDONLY);
	if (file == -1)
	{
		ft_putstr_fd(av, 2);
		exit(EXIT_FAILURE);
	}
	return (file);
}

void	handle_files(char **av, int *fd_in, int *fd_out, int *start_cmd)
{
	*fd_in = open(av[1], O_RDONLY);
	if (*fd_in < 0)
	{
		ft_putstr_fd("Missing input file", 2);
		*fd_in = open("/dev/null", O_RDONLY);
		if (*fd_in < 0)
		{
			ft_putstr_fd("/dev/null", 2);
			exit(EXIT_FAILURE);
		}
	}
	*fd_out = open_file(av[len(av)], 1);
	*start_cmd = 2;
}

int	len(char **av)
{
	int	i;

	i = 0;
	while (av[i])
		i++;
	i--;
	return (i);
}
