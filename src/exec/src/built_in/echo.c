/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 11:46:50 by mfernand          #+#    #+#             */
/*   Updated: 2025/06/23 22:24:55 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"

// ./a.out -n -n -n -> a gerer

static int	is_n_option(const char *str);

int	ft_echo(char **args)
{
	int	i;
	int	nl;
	int	res;

	i = 0;
	nl = 1;
	res = 0;
	while (args[++i] && is_n_option(args[i]))
		nl = 0;
	while (args[i])
	{
		if (printf("%s", args[i]) < 0)
			res = 1;
		if (args[i + 1])
			if (printf(" ") < 0)
				res = 1;
		i++;
	}
	if (nl)
		if (printf("\n") < 0)
			res = 1;
	if (res)
		perror("echo");
	return (res);
}

// int	ft_echo(char **args)
// {
// 	int	i;
// 	int	nl;

// 	i = 1;
// 	nl = 1;
// 	while (args[i] && is_n_option(args[i]))
// 	{
// 		nl = 0;		--> sans verif de printf
// 		i++;
// 	}
// 	while (args[i])
// 	{
// 		printf("%s", args[i]);
// 		if (args[i + 1])
// 			printf(" ");
// 		i++;
// 	}
// 	if (nl)
// 		printf("\n");
// 	return (0);
// }

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
