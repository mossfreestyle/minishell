/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwassim <rwassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 14:40:47 by rwassim           #+#    #+#             */
/*   Updated: 2025/06/24 11:43:28 by rwassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
