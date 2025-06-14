/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwassim <rwassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 09:57:51 by rwassim           #+#    #+#             */
/*   Updated: 2025/06/13 14:25:28 by rwassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINIHSELL_H

# include "../libft/include/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef enum e_token_type
{
	TOKEN_WORD = 0,
	TOKEN_PIPE = 1,
	TOKEN_REDIRECT_IN = 2,
	TOKEN_REDIRECT_OUT = 3,
	TOKEN_REDIRECT_APPEND = 4,
	TOKEN_INFILE = 5,
	TOKEN_HERE_DOC = 6,
	TOKEN_EOF = 7
}					t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*content;
	int				quoted;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

t_token				*tokenize(char *input);
void				print_tokens(t_token *tokens);
void				free_token(t_token *tokens);
t_token				*new_token(t_token_type type, char *value);
void				add_token(t_token **tokens, t_token *new);
int					handle_quotes(char *input, int *i, char **word);
int					handle_word(char *input, int *i, char **word);

#endif