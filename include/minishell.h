/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 09:57:51 by rwassim           #+#    #+#             */
/*   Updated: 2025/06/14 22:12:24 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/include/libft.h"
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define MAX_PIPES 1024
# ifndef PATH_MAX
#  define PATH_MAX 4096
/*4096 est une valeur courante utilisée comme taille maximale pour un chemin absolu sur la plupart des systèmes UNIX/Linux.*/
# endif

typedef enum e_token_type
{
	WORD,
	PIPE,
	R_INPUT,
	R_OUTPUT,
	R_APPEND,
	R_HEREDOC
}						t_token_type;

typedef struct s_token
{
	t_token_type		type;
	char				*content;
	struct s_token		*next;
}						t_token;

typedef struct s_redirect
{
	t_token_type		type;
	char				*filename;
	struct s_redirect	*next;
}						t_redirect;

typedef struct s_command
{
	char				*name;
	char				**args;
	t_redirect			*redirects;
	int					heredoc_fd;
	struct s_command	*next;
}						t_command;

typedef struct s_env
{
	char				*name;
	char				*value;
	struct s_env		*next;
}						t_env;

typedef struct s_pipe
{
	int					n_pipes;
	int					pipefd[MAX_PIPES][2];
}						t_pipe;

typedef struct s_shell
{
	int					exit_status;
	char				*pwd;
	t_env				*env_vars;
	t_pipe				pipeline;
}						t_shell;
////////////Parsing//////////////////////
t_token					*new_token(t_token_type type, char *value);
t_token					*meta_token(t_token *tokens, char *line, int *i);
bool					is_redirect(t_token_type type);
bool					is_meta(char c);
void					free_tokens(t_token *tokens);
void					free_redirects(t_redirect *redirects);
void					free_array(char **ptr);
void					free_command(t_command *cmd);
void					free_commands(t_command *cmd);

//////////Exec/////////////////////////

int						ft_pwd(t_shell *info);
int						ft_env(char **envp);
void					ft_echo(char **args);
int					ft_exit(char **args);

#endif