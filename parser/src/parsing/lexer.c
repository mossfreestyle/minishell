/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwassim <rwassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 09:57:25 by rwassim           #+#    #+#             */
/*   Updated: 2025/06/13 14:22:34 by rwassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token	*new_token(t_token_type type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->content = ft_strdup(value);
	token->next = NULL;
	return (token);
}

void	add_token(t_token **tokens, t_token *new)
{
	t_token	*current;

	if (!*tokens)
	{
		*tokens = new;
		return ;
	}
	current = *tokens;
	while (current->next)
		current = current->next;
	current->next = new;
}

t_token	*tokenize(char *input)
{
	t_token	*tokens;
	char	*word;
	int		i;

	tokens = NULL;
	i = 0;
	while (input[i])
	{
		while (input[i] && input[i] == ' ')
			i++;
		if (!input[i])
			break ;
		if (input[i] == '|')
		{
			add_token(&tokens, new_token(TOKEN_PIPE, "|"));
			i++;
		}
		else if (input[i] == '>')
		{
			if (input[i + 1] == '>')
			{
				add_token(&tokens, new_token(TOKEN_REDIRECT_APPEND, ">>"));
				i += 2;
			}
			else
			{
				add_token(&tokens, new_token(TOKEN_REDIRECT_OUT, ">"));
				i++;
			}
		}
		else if (input[i] == '<')
		{
			if (input[i + 1] == '<')
			{
				add_token(&tokens, new_token(TOKEN_HERE_DOC, "<<"));
				i += 2;
			}
			else
			{
				add_token(&tokens, new_token(TOKEN_REDIRECT_IN, "<"));
				i++;
			}
		}
		else if (input[i] == '"' || input[i] == '\'')
		{
			if (handle_quotes(input, &i, &word) == -1)
			{
				printf("Error: unclosed quote\n");
				free_token(tokens);
				return (NULL);
			}
			add_token(&tokens, new_token(TOKEN_WORD, word));
			free(word);
		}
		else
		{
			handle_word(input, &i, &word);
			add_token(&tokens, new_token(TOKEN_WORD, word));
			free(word);
		}
	}
	return (tokens);
}

void	print_tokens(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	printf("===== TOKENS =====\n");
	while (current)
	{
		printf("Type: %d, Value: '%s'\n", current->type, current->content);
		current = current->next;
	}
	printf("======================\n");
}

void	free_token(t_token *tokens)
{
	t_token	*tmp;

	while (tokens)
	{
		tmp = tokens;
		tokens = tokens->next;
		free(tmp->content);
		free(tmp);
	}
}
