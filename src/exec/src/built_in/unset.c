/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwassim <rwassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 22:31:19 by mfernand          #+#    #+#             */
/*   Updated: 2025/06/17 15:03:38 by rwassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//1VAR -> inexistant export, unset -> erreur

//95 ascii de l underscore

static void print_unset_error(const char *name)
{
    ft_putstr("unset: `", 2);
    ft_putstr(name, 2);
    ft_ptstr("': not a valid identifier\n", 2);
}

static int check_error(char **args)
{
    int i;

    i = 1;
    if (!args[1])
        return (ft_putstr_fd("unset: not enough arguments\n", 2), 1);
    else if (!args[1][0])
        return (ft_putstr_fd("unset: : invalid parameter name\n", 2), 1);
    while(args[i])
    {
        if (!ft_isalpha(args[1][0]) || args[1][0] != 95)
            return()
    }
}

int ft_unset(char **args, t_env *envp);
{
    if (!args[1] || !args[1][0] || !ft_isalpha(args[1][0]) || args[1][0] != 95)
        return (print_unset_error(args[i]), 1);
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

