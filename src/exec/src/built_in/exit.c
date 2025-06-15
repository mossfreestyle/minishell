/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 21:39:09 by mfernand          #+#    #+#             */
/*   Updated: 2025/06/15 10:55:20 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

static void	check_valid(char **args);

int	ft_exit(char **args)
{
	int	status;
	int	j;

	status = 0;
	j = 0;
	if (!args[1] || args[1][0] == '\0')
	{
		printf("exit\n");
		exit(status);
	}
	check_valid(args);
	if (args[2])
	{
		printf("exit\n");
		ft_putstr_fd("exit: too many arguments\n", 2);
		return (1);
	}
	if (args[1])
		status = ft_atoi(args[1]);
	exit(status);
}

static void	check_valid(char **args)
{
	int	i;

	i = 0;
	while (args[1][i])
	{
		if (!ft_isdigit(args[1][i]))
		{
			printf("exit\n");
			ft_putstr_fd("exit: a: numeric argument required\n", 2);
			exit(2);
		}
		i++;
	}
}
