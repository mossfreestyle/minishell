/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwassim <rwassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:36:28 by rwassim           #+#    #+#             */
/*   Updated: 2025/06/24 11:43:28 by rwassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setenv_lst(const char *name, const char *value, t_env **env_vars)
{
	t_env	*current;
	t_env	*new_node;

	current = *env_vars;
	while (current)
	{
		if (ft_strcmp(current->name, name) == 0)
		{
			free(current->value);
			current->value = ft_strdup(value);
			return ;
		}
		current = current->next;
	}
	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return ;
	new_node->name = ft_strdup(name);
	new_node->value = ft_strdup(value);
	new_node->next = *env_vars;
	*env_vars = new_node;
}

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

void	free_env(t_env *lst)
{
	t_env	*tmp;

	if (!lst)
		return ;
	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		free(tmp->name);
		free(tmp->value);
		free(tmp);
	}
}

static int	append_node(t_env **list, const char *env_entry)
{
	t_env	*new_node;
	t_env	*current;
	char	*equals_sign;

	equals_sign = ft_strchr(env_entry, '=');
	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (1);
	new_node->name = ft_substr(env_entry, 0, equals_sign - env_entry);
	new_node->value = ft_strdup(equals_sign + 1);
	new_node->exported = 1;
	new_node->next = NULL;
	if (*list == NULL)
		*list = new_node;
	else
	{
		current = *list;
		while (current->next)
			current = current->next;
		current->next = new_node;
	}
	return (0);
}

t_env	*init_env(char **envp)
{
	int		i;
	t_env	*env_list;

	i = 0;
	env_list = NULL;
	if (!envp || !*envp)
		return (NULL);
	while (envp[i])
	{
		if (append_node(&env_list, envp[i]) != 0)
		{
			free_env(env_list);
			return (NULL);
		}
		i++;
	}
	return (env_list);
}
