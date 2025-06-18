/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 21:39:09 by mfernand          #+#    #+#             */
/*   Updated: 2025/06/18 16:23:12 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_valid(char **args, t_shell *shell);

int	ft_exit(char **args, t_shell *shell)
{
	if (!args[1] || args[1][0] == '\0')
	{
		printf("exit\n");
		exit(0);
	}
	check_valid(args, shell);
	if (args[2])
	{
		printf("exit\n");
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		shell->exit_status = 1;
		return (shell->exit_status);
	}
	if (args[1])
		shell->exit_status = ft_atoi(args[1]);
	exit(shell->exit_status);
}

static void	check_valid(char **args, t_shell *shell)
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
			shell->exit_status = 2;
			exit(shell->exit_status);
		}
		i++;
	}
}
