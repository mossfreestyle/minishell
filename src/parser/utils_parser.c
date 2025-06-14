/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwassim <rwassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 14:30:03 by rwassim           #+#    #+#             */
/*   Updated: 2025/06/14 14:36:53 by rwassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_redirect(t_token_type type)
{
	return (type == R_OUTPUT || type == R_INPUT || type == R_APPEND
		|| type == R_HEREDOC);
}

bool	is_meta(char c)
{
	return (c == '|' || c == '<' || c == '>');
}
