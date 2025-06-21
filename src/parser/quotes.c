/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 13:31:38 by rwassim           #+#    #+#             */
/*   Updated: 2025/06/21 20:01:33 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * single_quote - Extrait le texte entre quotes simples, sans interprétation.
 */
static char	*single_quote(char *line, int *i)
{
	int		start;
	char	*value;

	start = ++(*i);
	while (line[*i] && line[*i] != '\'')
		(*i)++;
	value = ft_substr(line, start, *i - start);
	if (line[*i] == '\'')
		(*i)++;
	return (value);
}

/**
 * double_quote - Extrait le texte entre quotes doubles,
	interprète les variables.
 */
static char	*double_quote(char *line, int *i, t_shell *shell)
{
	char	*value;

	++(*i);
	value = ft_strdup("");
	while (line[*i] && line[*i] != '"')
	{
		if (line[*i] == '$')
			value = expand_var(line, i, shell, value);
		else
			value = add_char(line, i, value);
		if (!value)
			return (NULL);
	}
	if (line[*i] == '"')
		(*i)++;
	return (value);
}

/**
 * quotes - Redirige vers la fonction adaptée selon le type de quote.
 */
char	*quotes(char *line, int *i, void *shell)
{
	if (line[*i] == '\'')
		return (single_quote(line, i));
	else
		return (double_quote(line, i, shell));
}
