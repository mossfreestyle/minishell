/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwassim <rwassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 13:31:38 by rwassim           #+#    #+#             */
/*   Updated: 2025/06/24 11:43:27 by rwassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*quotes(char *line, int *i, void *shell)
{
	if (line[*i] == '\'')
		return (single_quote(line, i));
	else
		return (double_quote(line, i, shell));
}
