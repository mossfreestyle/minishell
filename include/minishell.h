/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 09:57:51 by rwassim           #+#    #+#             */
/*   Updated: 2025/06/18 17:01:25 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/include/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
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
	int					exported;
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
t_token					*meta_token(t_token *tokens, char *line, int *i);
t_token					*word_token(char *line, int *i, t_shell *shell,
							t_token *tokens);
t_token					*lexer(char *line, t_shell *shell);
bool					is_redirect(t_token_type type);
bool					is_meta(char c);
char					*quotes(char *line, int *i, void *shell);
void					parse_args(t_token **tokens, t_command *cmd);
bool					parse_redirects(t_token **tokens, t_command *cmd,
							t_shell *shell);
bool					parse_pipe(t_token **tokens, t_command **cmd,
							t_shell *shell);
t_command				*init_command(t_shell *shell);
t_command				*parser(char *line, t_shell *shell);

//////////Exec/////////////////////////

/////////BUILT_IN/////////////////////
int						ft_cd(char **args, t_shell *shell);
int						ft_echo(char **args);
int						ft_env(t_env *env);
int						ft_exit(char **args, t_shell *shell);
int						ft_export(char **args, t_env **envp);
int						ft_pwd(t_shell *shell);
int						ft_unset(char **args, t_env **envp);

/////////UTILS//////////////////////////
int						exec_built_in(char **args, t_shell *shell);
int						check_error(char *arg);
void					env_update(t_env **envp, char *arg);
void					env_addback(t_env **envp, char *arg);
void					set_exported_flag(t_env **envp, char *var);
int						print_env(t_env *envp);

//////////utils/////////////////////////

int						cmd_err(char *cmd, char *arg, char *msg, int err_num);
void					*set_status(t_shell *shell, int status);
void					*err_msg(char *cmd, char *msg, t_shell *shell,
							int exit_status);
int						exec_error(char *cmd);
void					free_tokens(t_token *tokens);
void					free_redirects(t_redirect *redirects);
void					free_array(char **ptr);
void					free_command(t_command *cmd);
void					free_commands(t_command *cmd);
char					*add_char(char *line, int *i, char *value);
char					*getenv_lst(const char *name, t_env *env_list);
char					*extract_word(char *line, int *i, t_shell *shell);
char					*expand_var(char *line, int *i, t_shell *shell,
							char *value);
char					**append_to_array(char **array, const char *new_elem);
long					ft_atol(char *str, int *out_of_range);
char					*ft_strjoin_char(char *str, char c);
bool					is_empty_line(const char *line);

#endif