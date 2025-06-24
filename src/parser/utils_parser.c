/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwassim <rwassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 14:30:03 by rwassim           #+#    #+#             */
/*   Updated: 2025/06/24 11:43:28 by rwassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*init_command(t_shell *shell)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (set_status(shell, 1));
	cmd->name = NULL;
	cmd->args = NULL;
	cmd->redirects = NULL;
	cmd->heredoc_fd = -1;
	cmd->next = NULL;
	return (cmd);
}

bool	is_redirect(t_token_type type)
{
	return (type == R_OUTPUT || type == R_INPUT || type == R_APPEND
		|| type == R_HEREDOC);
}

bool	is_meta(char c)
{
	return (c == '|' || c == '<' || c == '>');
}
