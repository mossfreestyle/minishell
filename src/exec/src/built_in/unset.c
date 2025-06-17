/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 22:31:19 by mfernand          #+#    #+#             */
/*   Updated: 2025/06/17 21:54:10 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 1VAR -> inexistant export, unset -> erreur

// 95 ascii de l underscore

static int	check_error(char *arg)
{
	int	i;

	i = 0;
	if (arg[0] == '\0')
		return (0);
	if (!(ft_isalpha(arg[0]) || arg[0] == 95))
		return (0);
	while (arg[i])
		if (!(ft_isalnum(arg[i]) || arg[i] == 95))
			return (0);
	return (1);
}
static void	free_env_node(t_env *node)
{
	free(node->name);
	free(node->value);
	free(node);
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
		if (find_env_var(*envp, args[i]))
			remove_env_var(&envp, args[i]);
	}
	return (0);
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