/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_scd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwassim <rwassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 11:18:51 by mfernand          #+#    #+#             */
/*   Updated: 2025/06/18 15:09:06 by rwassim          ###   ########.fr       */
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

void	env_addback(t_env **envp, char *arg)
{
	char	*eq;
	t_env	*new;
	t_env	*last;

	eq = ft_strchr(arg, '=');
	last = *envp;
	new = malloc(sizeof(t_env));
	if (!new)
		return ;
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
	if (!*envp)
		*envp = new;
	else
	{
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
