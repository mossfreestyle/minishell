/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwassim <rwassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 22:31:47 by mfernand          #+#    #+#             */
/*   Updated: 2025/06/21 14:49:02 by rwassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	present_var(t_env **envp, char *var);
static char	*copy_to_equal(char *str);
static void	handle_export_arg(char *arg, t_env **envp);
static int	print_unset_error(const char *name);

int	ft_export(char **args, t_env **envp)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	if (!args[1])
		return (print_env((*envp)));
	while (args[++i])
	{
		if (!check_error(args[i]))
			status = print_unset_error(args[i]);
		else
			handle_export_arg(args[i], envp);
	}
	return (status);
}

static int	present_var(t_env **envp, char *var)
{
	t_env	*curr_var;

	if (!var)
		return (0);
	curr_var = *envp;
	while (curr_var)
	{
		if (!ft_strcmp(curr_var->name, var))
			return (1);
		curr_var = curr_var->next;
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

static void	handle_export_arg(char *arg, t_env **envp)
{
	char	*var;

	var = NULL;
	if (ft_strchr(arg, '='))
		var = copy_to_equal(arg);
	else
		var = ft_strdup(arg);
	if (present_var(envp, var))
	{
		if (ft_strchr(arg, '='))
			env_update(envp, arg);
		else
			set_exported_flag(envp, var);
	}
	else
		env_addback(envp, arg);
	if (var)
		free(var);
}

static int	print_unset_error(const char *name)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(name, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (1);
}

// // Si l’argument ne contient pas de =,
// 	il faut juste marquer la variable comme exportée
//(si tu gères un flag d’export dans ta struct).
//
// Si tu veux gérer le cas où une variable existe déjà mais n’a pas de valeur,
// 	il faut un champ dans ta struct pour savoir si elle est exportée ou non.
// // a gerer   ^
// //			|
