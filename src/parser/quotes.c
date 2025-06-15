/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwassim <rwassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 13:31:38 by rwassim           #+#    #+#             */
/*   Updated: 2025/06/15 15:48:42 by rwassim          ###   ########.fr       */
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

static char *double_quote(char *line, int *i, t_shell *shell)
{
	
}

char *

char	*quotes(char *line, int *i, void *shell)
{
	if (line[*i] == '\'')
		return (single_quote(line, i));
	else
		return (double_quote(line, i, shell));
}
