/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwassim <rwassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 13:31:38 by rwassim           #+#    #+#             */
/*   Updated: 2025/06/13 14:25:18 by rwassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	handle_quotes(char *input, int *i, char **word)
{
	char	quote_char;
	int		start;
	int		len;

	quote_char = input[*i];
	(*i)++;
	start = *i;
	while (input[*i] && input[*i] != quote_char)
		(*i)++;
	if (!input[*i])
		return (-1);
	len = *i - start;
	*word = ft_substr(input, start, len);
	(*i)++;
	return (0);
}

int	handle_word(char *input, int *i, char **word)
{
	int	start;
	int	len;

	start = *i;
	while (input[*i] && input[*i] != ' ' && input[*i] != '|' && input[*i] != '>'
		&& input[*i] != '<' && input[*i] != '"' && input[*i] != '\'')
		(*i)++;
	len = *i - start;
	*word = ft_substr(input, start, len);
	return (0);
}
