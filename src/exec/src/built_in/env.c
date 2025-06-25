/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 12:17:51 by mfernand          #+#    #+#             */
/*   Updated: 2025/06/25 22:32:36 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// besoin d initialiser t_env **envp a char **envp des le debut;
int	ft_env(t_env *env, t_command *cmd)
{
	if (cmd->args[1])
		return (ft_putstr_fd("minishell: warning: env: argument forbidden\n",
				2), 1);
	while (env)
	{
		if (env->value)
			printf("%s=%s\n", env->name, env->value);
		env = env->next;
	}
	return (0);
}
