/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwassim <rwassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 11:46:45 by mfernand          #+#    #+#             */
/*   Updated: 2025/06/21 10:29:09 by rwassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_shell *shell, t_command *cmd)
{
	char	tab[PATH_MAX];

	if ((cmd->args && cmd->args[1]))
		return (ft_putendl_fd("minishell: pwd: too many arguments", 2), 1);
	if (getcwd(tab, sizeof(tab)) != NULL)
	{
		free(shell->pwd);
		shell->pwd = ft_strdup(tab);
		printf("%s\n", shell->pwd);
		return (0);
	}
	else
		perror("minishell: pwd");
	return (1);
}
