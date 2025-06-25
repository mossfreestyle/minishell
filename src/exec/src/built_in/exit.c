/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 21:39:09 by mfernand          #+#    #+#             */
/*   Updated: 2025/06/25 13:39:16 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_valid(char **args);
static void	printf_error(char *arg);

int	ft_exit(char **args, t_shell *shell)
{
	int	valid;

	if (!args[1] || args[1][0] == '\0')
	{
		printf("exit\n");
		return (shell->exit_status);
	}
	valid = check_valid(args);
	if (valid == 500)
		return (2);
	if (args[2])
	{
		printf("exit\n");
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1000);
	}
	printf("exit\n");
	return ((unsigned char)valid);
}

static int	check_valid(char **args)
{
	int		i;
	int		out_of_range;
	long	result;

	i = 0;
	if (args[1][i] == '+' || args[1][i] == '-')
		i++;
	if (args[1][i] == '\0')
		return (printf_error(args[1]), 500);
	while (args[1][i])
	{
		if (!ft_isdigit(args[1][i]))
			return (printf_error(args[1]), 500);
		i++;
	}
	result = ft_atol(args[1], &out_of_range);
	if (out_of_range)
		return (printf_error(args[1]), 500);
	return (result);
}

static void	printf_error(char *arg)
{
	printf("exit\n");
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
}
