/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_built_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwassim <rwassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 23:16:53 by mfernand          #+#    #+#             */
/*   Updated: 2025/06/24 15:09:11 by rwassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *name)
{
	if (!name)
		return (0);
	return (!ft_strcmp(name, "echo") || !ft_strcmp(name, "cd")
		|| !ft_strcmp(name, "pwd") || !ft_strcmp(name, "export")
		|| !ft_strcmp(name, "unset") || !ft_strcmp(name, "env")
		|| !ft_strcmp(name, "exit"));
}

int	exec_built_in(t_command *cmd, t_shell *shell)
{
	int	exit_code;

	exit_code = 0;
	if (!ft_strcmp(cmd->name, "cd"))
		return (ft_cd(cmd->args, shell));
	else if (!ft_strcmp(cmd->name, "echo"))
		return (ft_echo(cmd->args), 0);
	else if (!ft_strcmp(cmd->name, "env"))
		return (ft_env(shell->env_vars), 0);
	else if (!ft_strcmp(cmd->name, "exit"))
	{
		exit_code = ft_exit(cmd->args);
		if (exit_code == 1000)
			return (exit_code);
		free_shell(shell);
		exit(exit_code);
	}
	else if (!ft_strcmp(cmd->name, "export"))
		return (ft_export(cmd->args, &(shell->env_vars)));
	else if (!ft_strcmp(cmd->name, "pwd"))
		return (ft_pwd(shell, cmd));
	else if (!ft_strcmp(cmd->name, "unset"))
		return (ft_unset(cmd->args, &(shell->env_vars)));
	return (0);
}
