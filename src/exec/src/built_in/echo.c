/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 11:46:50 by mfernand          #+#    #+#             */
/*   Updated: 2025/06/14 22:32:19 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"

static void	with_nl(char **args);
static void	without_nl(char **args);

void	ft_echo(char **args)
{
	int	i;

	i = 0;
	if (!args[1] || args[1][0] == '\0')
	{
		printf("\n");
		return ;
	}
	if (!ft_strcmp(args[1], "-n"))
		without_nl(args);
	else
		with_nl(args);
}

static void	with_nl(char **args)
{
	int	i;

	i = 1;
	while (args[i])
	{
		if (!args[i + 1] || args[i + 1][0] == '\0')
			printf("%s\n", args[i++]);
		else
			printf("%s ", args[i++]);
	}
}

static void	without_nl(char **args)
{
	int	i;

	i = 2;
	while (args[i])
	{
		if (!args[i + 1] || args[i + 1][0] == '\0')
			printf("%s", args[i++]);
		else
			printf("%s ", args[i++]);
	}
}
