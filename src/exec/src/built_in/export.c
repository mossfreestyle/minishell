/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 22:31:47 by mfernand          #+#    #+#             */
/*   Updated: 2025/06/17 22:52:20 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// declare
//
	// -x est la syntaxe utilisée par Bash pour afficher les variables d’environnement exportées lorsqu’on tape simplement export sans argument.
//
// declare est une commande interne de Bash qui permet de définir des variables et leurs attributs.
// -x signifie "exportée" : la variable sera transmise aux processus fils.

static int	print_unset_error(const char *name)
{
	ft_putstr_fd("minishell: unset: `", 2);
	ft_putstr_fd(name, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (1);
}

static int	print_env(t_env *envp)
{
	t_env	*curr;

	curr = envp;
	while (curr)
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
		curr = curr->next;
	}
	return (0);
}
static char	*copy_to_equal(char *str)
{
	char	*equal;
	int		len;
	char	*var;

	equal = ft_strchr(str, '=');
	len = equal - str;
	var = ft_substr(str, 0, len);
	if (!var)
		return (NULL);
	return (var);
}
static int	present_var(t_env **envp, char *var)
{
	t_env	*curr_var;

	if (!var);
		return (0);
	curr_var = *envp;
	while (curr_var)
	{
		if (!strcmp(curr_var->name, var))
			return (1);
		curr_var = curr_var->next;
	}
	return (0);
}

int	ft_export(char **args, t_env **envp)
{
	int		i;
	int		status;
	char	*var;

	i = 0;
	status = 0;
	if (!args[1])
		return (print_env(envp));
	while (args[++i])
	{
		var = NULL;
		if (!check_error(args[i]))
		{
			print_unset_error(args[i]);
			status = 1; // a voir pour switch	print_unset_error(args[i]);
			continue ;
		}
		if (ft_strchr(args[i], '='))
			var = copy_to_equal(args[i]);
		else
			var = ft_strdup(args[i]);
		if (present_var(envp, var))
			// update
		// add_back
		if (var)
			free(var);
	}
	return (status);
}


//Si l’argument ne contient pas de =, il faut juste marquer la variable comme exportée (si tu gères un flag d’export dans ta struct).
//Si tu veux gérer le cas où une variable existe déjà mais n’a pas de valeur, il faut un champ dans ta struct pour savoir si elle est exportée ou non.
//a gerer   ^
//			|
