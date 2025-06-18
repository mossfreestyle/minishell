/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwassim <rwassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 14:30:03 by rwassim           #+#    #+#             */
/*   Updated: 2025/06/18 10:30:31 by rwassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * init_command - Alloue et initialise une nouvelle structure de commande.
 * Remplit tous les champs avec des valeurs par défaut (NULL ou -1).
 * Retourne un pointeur vers la nouvelle commande, ou NULL en cas d'échec d'allocation
 * (et met à jour le statut de sortie du shell).
 */
t_command	*init_command(t_shell *shell)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (set_status(shell, 1));
	cmd->name = NULL;
	cmd->args = NULL;
	cmd->redirects = NULL;
	cmd->heredoc_fd = -1;
	cmd->next = NULL;
	return (cmd);
}

/**
 * is_redirect - Vérifie si un type de token est une redirection.
 * Retourne true si c'est une redirection, false sinon.
 */
bool	is_redirect(t_token_type type)
{
	return (type == R_OUTPUT || type == R_INPUT || type == R_APPEND
		|| type == R_HEREDOC);
}

/**
 * is_meta - Vérifie si un caractère est un métacaractère du shell.
 * Retourne true si c'est un métacaractère, false sinon.
 */
bool	is_meta(char c)
{
	return (c == '|' || c == '<' || c == '>');
}
