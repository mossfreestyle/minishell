/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwassim <rwassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 09:57:25 by rwassim           #+#    #+#             */
/*   Updated: 2025/06/18 09:47:06 by rwassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * add_token - Ajoute un token à la liste chaînée des tokens.
 */
static t_token	*add_token(t_token *tokens, char *value, t_token_type type)
{
	t_token	*new;
	t_token	*temp;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->type = type;
	new->content = value;
	new->next = NULL;
	if (!tokens)
		return (new);
	temp = tokens;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
	return (tokens);
}

/**
 * meta_token - Crée un token pour un métacaractère (|, <, >, etc.).
 */
t_token	*meta_token(t_token *tokens, char *line, int *i)
{
	if (line[*i] == '|')
		tokens = add_token(tokens, ft_strdup("|"), PIPE);
	else if (line[*i] == '>' && line[*i + 1] == '>')
	{
		tokens = add_token(tokens, ft_strdup(">>"), R_APPEND);
		(*i)++;
	}
	else if (line[*i] == '>')
		tokens = add_token(tokens, ft_strdup(">"), R_OUTPUT);
	else if (line[*i] == '<' && line[*i + 1] == '<')
	{
		tokens = add_token(tokens, ft_strdup("<<"), R_HEREDOC);
		(*i)++;
	}
	else if (line[*i] == '<')
		tokens = add_token(tokens, ft_strdup("<"), R_INPUT);
	(*i)++;
	return (tokens);
}

/**
 * word_token - Crée un token pour un mot (commande ou argument).
 */
t_token	*word_token(char *line, int *i, t_shell *shell, t_token *tokens)
{
	char	*value;

	value = extract_word(line, i, shell);
	if (value)
		tokens = add_token(tokens, value, WORD);
	return (tokens);
}
