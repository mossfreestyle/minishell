/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 21:39:09 by mfernand          #+#    #+#             */
/*   Updated: 2025/06/21 16:32:32 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_valid(char **args);

int	ft_exit(char **args)
{
	int	status;

	status = 0;
	if (!args[1] || args[1][0] == '\0')
	{
		printf("exit\n");
		return (status);
	}
	if (check_valid(args))
		return (2);
	if (args[2])
	{
		printf("exit\n");
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		status = 1;
		return (status);
	}
	if (args[1])
		status = ft_atoi(args[1]);
	return (status);
}

static int	check_valid(char **args)
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
	return (0);
}
// static int	check_valid(char **args)
// {
//     int		i;
//     int		out_of_range;
//     long	result;

//     i = 0;
//     // Gérer les signes + et -
//     if (args[1][i] == '+' || args[1][i] == '-')
//         i++;
//     if (args[1][i] == '\0') // Juste un signe
//     {
//         printf("exit\n");
//         ft_putstr_fd("minishell: exit: ", 2);
//         ft_putstr_fd(args[1], 2);
//         ft_putstr_fd(": numeric argument required\n", 2);
//         return (255);
//     }
//     while (args[1][i])
//     {
//         if (!ft_isdigit(args[1][i]))
//         {
//             printf("exit\n");
//             ft_putstr_fd("minishell: exit: ", 2);
//             ft_putstr_fd(args[1], 2);
//             ft_putstr_fd(": numeric argument required\n", 2);
//             return (255);
//         }
//         i++;
//     }
//     result = ft_atol(args[1], &out_of_range);
//     if (out_of_range)
//     {
//         printf("exit\n");
//         ft_putstr_fd("minishell: exit: ", 2);
//         ft_putstr_fd(args[1], 2);
//         ft_putstr_fd(": numeric argument required\n", 2);
//         return (255);
//     }
//     return (0);
// }