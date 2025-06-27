/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwassim <rwassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 09:57:51 by rwassim           #+#    #+#             */
/*   Updated: 2025/06/27 22:10:42 by rwassim          ###   ########.fr       */
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
# include <stdbool.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define MAX_PIPES 1024
# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

extern volatile sig_atomic_t	g_signal;

typedef enum e_token_type
{
	WORD,
	PIPE,
	R_INPUT,
	R_OUTPUT,
	R_APPEND,
	R_HEREDOC
}								t_token_type;

typedef struct s_token
{
	t_token_type				type;
	char						*content;
	struct s_token				*next;
}								t_token;

typedef struct s_redirect
{
	t_token_type				type;
	char						*filename;
	struct s_redirect			*next;
}								t_redirect;

typedef struct s_command
{
	char						*name;
	char						**args;
	t_redirect					*redirects;
	int							heredoc_fd;
	struct s_command			*next;
}								t_command;

typedef struct s_env
{
	char						*name;
	char						*value;
	int							exported;
	struct s_env				*next;
}								t_env;

typedef struct s_pipe
{
	int							n_pipes;
	int							pipefd[MAX_PIPES][2];
}								t_pipe;

typedef struct s_shell
{
	int							exit_status;
	char						*pwd;
	char						**av;
	t_env						*env_vars;
	t_pipe						pipeline;
	t_command					*cmd_list;
	int							saved_stdin;
	int							saved_stdout;
}								t_shell;

/* ========== PARSING ========== */
t_token							*lexer(char *line, t_shell *shell);
t_token							*meta_token(t_token *tokens, char *line,
									int *i);
t_token							*word_token(char *line, int *i, t_shell *shell,
									t_token *tokens);

t_command						*parser(char *line, t_shell *shell);
void							parse_args(t_token **tokens, t_command *cmd);
bool							parse_redirects(t_token **tokens,
									t_command *cmd, t_shell *shell);
bool							parse_pipe(t_token **tokens, t_command **cmd,
									t_shell *shell);

t_command						*init_command(t_shell *shell);
bool							is_redirect(t_token_type type);
bool							is_meta(char c);

char							*quotes(char *line, int *i, void *shell);
char							*extract_word(char *line, int *i,
									t_shell *shell);
char							*expand_var(char *line, int *i, t_shell *shell,
									char *value);
char							*add_char(char *line, int *i, char *value);

/* ========== EXECUTION ========== */
int								exec_readline(t_shell *shell);
int								exec_commands(t_shell *shell);
void							print_error(char *name);

int								is_builtin(char *name);
int								exec_built_in(t_command *cmd, t_shell *shell,
									char **envp, char *path);
int								ft_cd(char **args, t_shell *shell);
int								ft_echo(char **args);
int								ft_env(t_env *env, t_command *cmd);
int								ft_exit(char **args, t_shell *shell);
int								ft_export(char **args, t_env **envp);
int								ft_pwd(t_shell *shell, t_command *cmd);
int								ft_unset(char **args, t_env **envp);

int								check_error(char *arg);
void							env_update(t_env **envp, char *arg);
void							env_addback(t_env **envp, char *arg);
void							set_exported_flag(t_env **envp, char *var);
int								print_env(t_env *envp);

char							*find_path(char *cmd, char **envp);
char							*link_path(char **path_lst, char *path_cmd,
									char *cmd);
void							cmd_not_found(char **envp, t_shell *shell);
void							check_pid(int pid, t_shell *shell);

int								handle_redirections(t_command *cmd,
									t_shell *shell);
int								r_input(t_redirect *redir, t_shell *shell);
int								r_output(t_redirect *redir, t_shell *shell);
int								r_append(t_redirect *redir, t_shell *shell);
void							r_heredoc(t_command *cmd, t_shell *shell);

int								is_here_doc(char *name);
int								exec_here_doc(t_command *cmd, t_redirect *redir,
									t_shell *shell);

/* ========== UTILS ========== */
int								cmd_err(char *cmd, char *arg, char *msg,
									int err_num);
void							*set_status(t_shell *shell, int status);
void							*err_msg(char *cmd, char *msg, t_shell *shell,
									int exit_status);
int								exec_error(char *cmd);

void							handle_redirs_if_needed(t_command *cmd,
									t_shell *shell);
int								process_heredocs(t_command *cmd,
									t_redirect *redir, t_shell *shell);
char							**append_to_array(char **array,
									const char *new_elem);
long							ft_atol(char *str, int *out_of_range);
char							*ft_strjoin_char(char *str, char c);
bool							is_empty_line(const char *line);

t_env							*init_env(char **envp);
void							setenv_lst(const char *name, const char *value,
									t_env **env_vars);
char							*getenv_lst(const char *name, t_env *env_list);
char							**env_list_to_array(t_env *env);

int								count_cmds(t_command *cmd);
void							init_pipes(t_shell *shell);
void							close_all_pipes(t_shell *shell);

void							free_tokens(t_token *tokens);
void							free_redirects(t_redirect *redirects);
void							free_array(char **ptr);
void							free_command(t_command *cmd);
void							free_commands(t_command *cmd);
void							free_env(t_env *lst);
int								free_shell(t_shell *shell);
void							close_and_free_all(t_shell *shell);

t_shell							*init_shell(int ac, char **av, char **envp);

/* ========== SIGNALS ========== */
void							handle_signal(t_shell *shell);
void							exec_signals(int sig);
void							handle_eof(t_shell *shell);
void							setup_signals(void);

/* ========== DEBUG ========== */
void							print_tokens(t_token *tokens);
void							print_command(t_command *cmd);

/* ========== HEREDOC UTILS ========== */
bool							has_quotes(char *delimiter);
char							*expand_heredoc_line(char *line,
									t_shell *shell);
void							finish_exec(t_command *cmd, char *path,
									char **envp, t_shell *shell);
int								process_redirect(t_redirect *redir,
									t_shell *shell, t_redirect **last);

/* ========== UTILS MAIN ========== */
int								res_readline(int res, t_command *cmd,
									t_shell *shell);
void							end_safe_redir(t_shell *shell);
void							only_one_builtin(t_shell *shell,
									t_command *cmd);
void							reset_sig(void);
void							close_write_fd_and_free_line(int write_fd,
									char *line);

void							check_exit(t_shell *shell, t_command *cmd,
									int saved_stdout, int saved_stdin);
void							free_envp_path(char **envp, char *path);
void							close_unused_heredoc_fds(t_command *cmd);
int								check_nb_pipe(t_shell *shell, t_command *cmd);
void							put_heredoc(int should_expand, char *line,
									t_shell *shell, int write_fd);
void							check_sig(int status, t_shell *shell);

#endif