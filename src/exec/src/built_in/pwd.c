/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 11:46:45 by mfernand          #+#    #+#             */
/*   Updated: 2025/06/22 17:10:08 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_shell *shell, t_command *cmd)
{
	char	tab[PATH_MAX];

	if (cmd->args[1] && cmd->args[1][0] == '-' && cmd->args[1][1] != '\0')
		return (ft_putendl_fd("minishell: pwd: no option is allowed", 2), 1);
	if (getcwd(tab, sizeof(tab)) != NULL)
	{
		free(shell->pwd);
		shell->pwd = ft_strdup(tab);
		printf("%s\n", shell->pwd);
		return (0);
	}
	else
		ft_putstr_fd("pwd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n",
			2);
	return (1);
}
