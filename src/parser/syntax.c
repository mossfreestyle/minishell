/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:16:36 by rwassim           #+#    #+#             */
/*   Updated: 2025/06/22 11:51:10 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * parse_args - Ajoute un argument à la commande courante.
 * Si le nom de la commande n'est pas encore défini,
	il l'initialise avec le contenu du token courant.
 * Sinon, il ajoute le contenu du token courant à la liste des arguments.
 * Avance le pointeur de token.
 */
void	parse_args(t_token **tokens, t_command *cmd)
{
	if (!tokens || !*tokens || !(*tokens)->content || !cmd)
		return ;
	// if ((*tokens)->content && (*tokens)->content[0] == '\0')
	// {
	// 	(*tokens) = (*tokens)->next;
	// 	return ;
	// }
	if (!cmd->name)
	{
		cmd->name = ft_strdup((*tokens)->content);
		cmd->args = append_to_array(NULL, cmd->name);
	}
	else
		cmd->args = append_to_array(cmd->args, (*tokens)->content);
	(*tokens) = (*tokens)->next;
}

/**
 * init_redirect - Alloue et initialise une nouvelle structure de redirection.
 * Copie le nom du fichier cible depuis le token suivant.
 * Définit le type de redirection selon le token courant.
 * Retourne la nouvelle redirection ou NULL en cas d'erreur.
 */
static t_redirect	*init_redirect(t_token *token)
{
	t_redirect	*new_redirect;

	new_redirect = malloc(sizeof(t_redirect));
	if (!new_redirect)
		return (NULL);
	new_redirect->filename = ft_strdup(token->next->content);
	if (!new_redirect->filename)
	{
		free(new_redirect);
		return (NULL);
	}
	if (token->type == R_OUTPUT)
		new_redirect->type = R_OUTPUT;
	else if (token->type == R_APPEND)
		new_redirect->type = R_APPEND;
	else if (token->type == R_INPUT)
		new_redirect->type = R_INPUT;
	else if (token->type == R_HEREDOC)
		new_redirect->type = R_HEREDOC;
	new_redirect->next = NULL;
	return (new_redirect);
}

/**
 * parse_redirects - Ajoute une redirection à la commande courante.

	* Vérifie la validité syntaxique (présence d'un mot après le token de redirection).
 * Alloue et ajoute la redirection à la liste de la commande.
 * Avance le pointeur de token de deux positions.
 * Retourne true en cas de succès, false sinon.
 */
bool	parse_redirects(t_token **tokens, t_command *cmd, t_shell *shell)
{
	t_redirect	*new_redirect;
	t_redirect	*last;

	if (!(*tokens)->next || (*tokens)->next->type != WORD)
	{
		err_msg(NULL, "syntax error near unexpected token `newline'", shell, 2);
		return (false);
	}
	new_redirect = init_redirect(*tokens);
	if (!new_redirect)
		return (false);
	if (!cmd->redirects)
		cmd->redirects = new_redirect;
	else
	{
		last = cmd->redirects;
		while (last->next)
			last = last->next;
		last->next = new_redirect;
	}
	(*tokens) = (*tokens)->next->next;
	return (true);
}

/**
 * parse_pipe
	- Gère la création d'une nouvelle commande lors de la rencontre d'un pipe '|'.
 * Vérifie la validité syntaxique (commande précédente et token suivant).
 * Crée une nouvelle commande et avance les pointeurs.
 * Traite immédiatement une éventuelle redirection ou un argument après le pipe.
 * Retourne false (utilisé pour le contrôle de flux dans le parsing).
 */
bool	parse_pipe(t_token **tokens, t_command **cmd, t_shell *shell)
{
	if (!(*cmd) || !(*tokens)->next)
	{
		err_msg(NULL, "syntax error near unexpected token '|'", shell, 2);
		return (false);
	}
	(*cmd)->next = init_command(shell);
	if (!(*cmd)->next)
		return (false);
	*cmd = (*cmd)->next;
	*tokens = (*tokens)->next;
	if (is_redirect((*tokens)->type))
	{
		if (!parse_redirects(tokens, *cmd, shell))
			return (false);
	}
	else if ((*tokens)->type == WORD)
		parse_args(tokens, *cmd);
	return (true);
}
