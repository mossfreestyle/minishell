/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwassim <rwassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 13:51:39 by rwassim           #+#    #+#             */
/*   Updated: 2025/06/16 18:11:28 by rwassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*add_char(char *line, int *i, char *value)
{
	char	*new_value;

	new_value = ft_strjoin_char(value, line[*i]);
	if (!new_value)
	{
		free(value);
		return (NULL);
	}
	free(value);
	(*i)++;
	return (new_value);
}