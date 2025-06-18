/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:56:15 by mfernand          #+#    #+#             */
/*   Updated: 2025/06/18 17:11:50 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_built_in(char **args, t_shell *shell)
{
	if (!ft_strcmp(args[0], "cd"))
		return (ft_cd(args, shell));
	else if (!ft_strcmp(args[0], "echo"))
		return (ft_echo(args), 0);
	else if (!ft_strcmp(args[0], "env"))
		return (ft_env(shell->env_vars), 0);
	else if (!ft_strcmp(args[0], "exit"))
		return (ft_exit(args, shell));
	else if (!ft_strcmp(args[0], "export"))
		return (ft_export(args, shell)); //besoin de passer t_env **envp 
	else if (!ft_strcmp(args[0], "pwd"))
		return (ft_pwd(shell));
	else if (!ft_strcmp(args[0], "unset"))
		return (ft_unset(args, shell)); //besoin de passer t_env **envp 
	return (1);
}
