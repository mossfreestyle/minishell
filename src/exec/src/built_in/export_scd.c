/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_scd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwassim <rwassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 11:18:51 by mfernand          #+#    #+#             */
/*   Updated: 2025/06/21 14:49:20 by rwassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_update(t_env **envp, char *arg)
{
	t_env	*curr;
	size_t	name_len;
	char	*eq;

	eq = ft_strchr(arg, '=');
	if (!eq)
		return ;
	name_len = eq - arg;
	curr = *envp;
	while (curr)
	{
		if (!ft_strncmp(curr->name, arg, name_len)
			&& curr->name[name_len] == '\0')
		{
			free(curr->value);
			curr->value = ft_strdup(eq + 1);
			curr->exported = 1;
			return ;
		}
		curr = curr->next;
	}
}

static t_env	*env_new_node(char *arg)
{
	t_env	*new;
	char	*eq;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	eq = ft_strchr(arg, '=');
	if (eq)
	{
		new->name = ft_substr(arg, 0, eq - arg);
		new->value = ft_strdup(eq + 1);
	}
	else
	{
		new->name = ft_strdup(arg);
		new->value = NULL;
	}
	new->exported = 1;
	new->next = NULL;
	return (new);
}

void	env_addback(t_env **envp, char *arg)
{
	t_env	*new;
	t_env	*last;

	new = env_new_node(arg);
	if (!new)
		return ;
	if (!*envp)
		*envp = new;
	else
	{
		last = *envp;
		while (last->next)
			last = last->next;
		last->next = new;
	}
}

void	set_exported_flag(t_env **envp, char *var)
{
	t_env	*curr;

	curr = *envp;
	while (curr)
	{
		if (!ft_strcmp(curr->name, var))
		{
			curr->exported = 1;
			return ;
		}
		curr = curr->next;
	}
}

int	print_env(t_env *envp)
{
	t_env	*curr;

	curr = envp;
	while (curr)
	{
		if (curr->exported)
		{
			ft_putstr_fd("export ", 1);
			ft_putstr_fd(curr->name, 1);
			if (curr->value)
			{
				ft_putstr_fd("=\"", 1);
				ft_putstr_fd(curr->value, 1);
				ft_putstr_fd("\"", 1);
			}
			ft_putstr_fd("\n", 1);
		}
		curr = curr->next;
	}
	return (0);
}
