/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwassim <rwassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 14:40:47 by rwassim           #+#    #+#             */
/*   Updated: 2025/06/18 09:46:35 by rwassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * unclosed_quotes - Vérifie s'il y a des quotes non fermées dans une ligne.
 * Retourne true si une quote est non fermée, false sinon.
 */
static bool	unclosed_quotes(char *line)
{
	bool	single_q;
	bool	double_q;
	int		i;

	i = 0;
	single_q = false;
	double_q = false;
	while (line[i])
	{
		if (line[i] == '\'' && !double_q)
			single_q = !single_q;
		else if (line[i] == '"' && !single_q)
			double_q = !double_q;
		i++;
	}
	return (single_q || double_q);
}

/**
 * lexer - Découpe une ligne en tokens (lexing), gère les erreurs de quotes.
 * Retourne la liste des tokens ou NULL en cas d'erreur.
 */
t_token	*lexer(char *line, t_shell *shell)
{
	int		i;
	t_token	*tokens;

	i = 0;
	tokens = NULL;
	if (unclosed_quotes(line))
		return (err_msg(NULL, "syntax error: unmatched or unclosed quotes",
				shell, 2));
	while (line[i])
	{
		if (ft_isspace(line[i]))
			i++;
		else if (is_meta(line[i]))
			tokens = meta_token(tokens, line, &i);
		else
			tokens = word_token(line, &i, shell, tokens);
	}
	return (tokens);
}
