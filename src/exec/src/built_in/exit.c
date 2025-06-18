/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 21:39:09 by mfernand          #+#    #+#             */
/*   Updated: 2025/06/18 21:57:43 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_valid(char **args);

int	ft_exit(char **args)
{
	int	status;

	status = 0;
	if (!args[1] || args[1][0] == '\0')
	{
		printf("exit\n");
		return(status);
	}
	check_valid(args);
	if (args[2])
	{
		printf("exit\n");
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		status = 1;
		return (status); //le seul cas qui ne fais pas exit reelement
	}
	if (args[1])
		status = ft_atoi(args[1]);
	return(status);
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
			ft_putstr_fd("minishell: exit: ", 2);
			printf("%s", args[1]);
			ft_putstr_fd(": numeric argument required\n", 2);
			return (2);
		}
		i++;
	}
}
