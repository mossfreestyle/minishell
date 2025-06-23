/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwassim <rwassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 10:31:06 by rwassim           #+#    #+#             */
/*   Updated: 2025/06/23 11:54:49 by rwassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_command	*parse_command(t_token **tokens, t_shell *shell,
		t_command **current)
{
	if (!*current)
	{
		*current = init_command(shell);
		if (!*current)
			return (NULL);
	}
	if (is_redirect((*tokens)->type))
	{
		if (!parse_redirects(tokens, *current, shell))
			return (NULL);
	}
	else if ((*tokens)->type == WORD)
		parse_args(tokens, *current);
	return (*current);
}

static t_command	*build_command(t_token *tokens, t_shell *shell)
{
	t_command	*head;
	t_command	*current;

	head = NULL;
	current = NULL;
	while (tokens)
	{
		if (tokens->type == PIPE)
		{
			if (!parse_pipe(&tokens, &current, shell))
				return (free_commands(head), NULL);
		}
		else
		{
			if (!current)
			{
				current = init_command(shell);
				if (!current)
					return (free_commands(head), NULL);
				if (!head)
					head = current;
			}
			if (!parse_command(&tokens, shell, &current))
				return (free_commands(head), NULL);
		}
	}
	return (head);
}

t_command	*parser(char *line, t_shell *shell)
{
	t_token		*tokens;
	t_command	*head;
	char		*trimmed;

	trimmed = ft_strtrim(line, " \t");
	if (!trimmed)
		return (NULL);
	if (ft_strcmp(trimmed, "!") == 0)
	{
		free(trimmed);
		return (NULL);
	}
	if (ft_strcmp(trimmed, ":") == 0)
	{
		free(trimmed);
		shell->exit_status = 0;
		return (NULL);
	}
	free(trimmed);
	tokens = lexer(line, shell);
	if (!tokens)
		return (NULL);
	head = build_command(tokens, shell);
	free_tokens(tokens);
	return (head);
}
