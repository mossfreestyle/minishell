/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_built_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwassim <rwassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 23:16:53 by mfernand          #+#    #+#             */
/*   Updated: 2025/06/20 14:06:32 by rwassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(t_command *cmd)
{
	if (!cmd->name)
		return (0);
	return (!ft_strcmp(cmd->name, "echo") || !ft_strcmp(cmd->name, "cd")
		|| !ft_strcmp(cmd->name, "pwd") || !ft_strcmp(cmd->name, "export")
		|| !ft_strcmp(cmd->name, "unset") || !ft_strcmp(cmd->name, "env")
		|| !ft_strcmp(cmd->name, "exit"));
}

int	exec_built_in(t_shell *shell)
{
	int	exit_code;

	exit_code = 0;
	if (!ft_strcmp(shell->cmd_list->name, "cd"))
		return (ft_cd(shell->cmd_list->args, shell));
	else if (!ft_strcmp(shell->cmd_list->name, "echo"))
		return (ft_echo(shell->cmd_list->args), 0);
	else if (!ft_strcmp(shell->cmd_list->name, "env"))
		return (ft_env(shell->env_vars), 0);
	else if (!ft_strcmp(shell->cmd_list->name, "exit"))
	{
		exit_code = ft_exit(shell->cmd_list->args);
		if (exit_code == 1)
			return (exit_code);
		free_shell(shell);
		exit(exit_code);
	}
	else if (!ft_strcmp(shell->cmd_list->name, "export"))
		return (ft_export(shell->cmd_list->args, &(shell->env_vars)));
	else if (!ft_strcmp(shell->cmd_list->name, "pwd"))
		return (ft_pwd(shell));
	else if (!ft_strcmp(shell->cmd_list->name, "unset"))
		return (ft_unset(shell->cmd_list->args, &(shell->env_vars)));
	return (0);
}
