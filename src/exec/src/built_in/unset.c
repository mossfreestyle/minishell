/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwassim <rwassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 22:31:19 by mfernand          #+#    #+#             */
/*   Updated: 2025/06/17 17:04:07 by rwassim          ###   ########.fr       */
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
	if (!(ft_isalpha(args[0]) || args[0] == 95))
		return (0);
	while (args[i])
		if (!(ft_isalnum(args[i]) || args[i] == 95))
			return (0);
	return (1);
}

int	ft_unset(char **args, t_env *envp)
{
	int	i;

	i = 0;
	if (!args[1])
		return (0);
	while (args[++i])
	{
		if (!check_error(args[i]))
			continue ;
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