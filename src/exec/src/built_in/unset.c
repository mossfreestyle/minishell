/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 22:31:19 by mfernand          #+#    #+#             */
/*   Updated: 2025/06/21 21:11:36 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 1VAR -> inexistant export, unset -> erreur

// 95 ascii de l underscore
static t_env	*find_env_var(t_env *envp, const char *name);
static void		remove_env_var(t_env **envp, const char *name);
static void		free_env_node(t_env *node);

int	ft_unset(char **args, t_env **envp)
{
	int	i;

	i = 0;
	if (!args[1])
		return (0);
	while (args[++i])
	{
		if (!check_error(args[i]))
			continue ;
		else if (find_env_var(*envp, args[i]))
			remove_env_var(envp, args[i]);
	}
	return (0);
}

int	check_error(char *arg)
{
	int		i;
	char	*var_name;
	char	*equal;

	if (ft_strchr(arg, '='))
	{
		equal = ft_strchr(arg, '=');
		var_name = ft_substr(arg, 0, equal - arg);
	}
	else
		var_name = arg;
	i = 0;
	if (!var_name || var_name[0] == '\0')
		return (0);
	if (!(ft_isalpha(var_name[0]) || var_name[0] == '_'))
		return (0);
	while (var_name[i])
	{
		if (!(ft_isalnum(var_name[i]) || var_name[i] == '_'))
			return (0);
		i++;
	}
	if (var_name != arg)
		free(var_name);
	return (1);
}

static t_env	*find_env_var(t_env *envp, const char *name)
{
	while (envp)
	{
		if (!ft_strncmp(envp->name, name, ft_strlen(name)))
			return (envp);
		envp = envp->next;
	}
	return (NULL);
}

static void	remove_env_var(t_env **envp, const char *name)
{
	t_env	*curr;
	t_env	*tmp;

	curr = *envp;
	if (curr && !ft_strcmp(curr->name, name))
	{
		tmp = curr;
		*envp = curr->next;
		free_env_node(tmp);
		return ;
	}
	while (curr && curr->next)
	{
		if (!ft_strcmp(curr->next->name, name))
		{
			tmp = curr->next;
			curr->next = curr->next->next;
			free_env_node(tmp);
			return ;
		}
		curr = curr->next;
	}
}

static void	free_env_node(t_env *node)
{
	if (node->name)
		free(node->name);
	if (node->value)
		free(node->value);
	free(node);
}

// VAR=42
// bash -c 'echo $VAR'   # n'affiche rien

// export VAR=42
// bash -c 'echo $VAR'   # affiche 42

// Pour les caractères spéciaux, tu dois refuser tout caractère qui n’est pas :

// une lettre (a-z, A-Z)
// un chiffre (0-9) (mais pas en première position)
// un underscore (_)
// Donc, tu dois refuser :

// tiret (-)
// dollar ($)
// espace, tabulation
// point (.)
// guillemets (", ')
// tout autre caractère non alphanumérique ou non underscore

// gerer si il faut un message d erreur ou pas en fonction de bash

// Tu dois afficher un message d’erreur et retourner 1 si l’identifiant
// est invalide (ex : unset 1VAR).
// a verifier