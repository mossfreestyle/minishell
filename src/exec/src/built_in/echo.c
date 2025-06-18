/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 11:46:50 by mfernand          #+#    #+#             */
/*   Updated: 2025/06/18 16:24:14 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"

// ./a.out -n -n -n -> a gerer

static int	is_n_option(const char *str)
{
	int	i;

	i = 0;
	if (str[i] != '-' || str[i + 1] != 'n')
		return (0);
	i += 2;
	while (str[i] == 'n')
		i++;
	return (str[i] == '\0');
}

int	ft_echo(char **args)
{
	int	i;
	int	nl;

	i = 1;
	nl = 1;
	while (args[i] && is_n_option(args[i]))
	{
		nl = 0;
		i++;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (nl)
		printf("\n");
	return (0);
}
