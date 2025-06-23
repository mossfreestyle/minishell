/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 11:46:45 by mfernand          #+#    #+#             */
/*   Updated: 2025/06/23 20:54:37 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_shell *shell, t_command *cmd)
{
	char	tab[PATH_MAX];

	if (cmd->args[1] && cmd->args[1][0] == '-' && !(cmd->args[1][1] == '\0'
			|| (cmd->args[1][1] == '-' && cmd->args[1][2] == '\0')))
	{
		ft_putstr_fd("minishell: pwd: ", 2);
		ft_putchar_fd(cmd->args[1][0], 2);
		ft_putchar_fd(cmd->args[1][1], 2);
		ft_putstr_fd(": invalid option\npwd: usage: pwd [-LP]\n", 2);
		return (2);
	}
	if (getcwd(tab, sizeof(tab)) != NULL)
	{
		free(shell->pwd);
		shell->pwd = ft_strdup(tab);
		printf("%s\n", shell->pwd);
		return (0);
	}
	else
	{
		ft_putstr_fd("pwd: error retrieving current directory: getcwd: can", 2);
		ft_putstr_fd("not access", 2);
		ft_putstr_fd(" parent directories: No such file or directory\n", 2);
	}
	return (1);
}
