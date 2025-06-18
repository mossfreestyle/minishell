/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwassim <rwassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:36:28 by rwassim           #+#    #+#             */
/*   Updated: 2025/06/18 09:49:18 by rwassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * getenv_lst - Cherche la valeur d'une variable d'environnement dans une liste chaînée.
 * Retourne la valeur si trouvée, NULL sinon.
 */
char	*getenv_lst(const char *name, t_env *env_list)
{
	t_env	*current;

	current = env_list;
	while (current)
	{
		if (ft_strcmp(current->name, name) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}
