/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwassim <rwassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 10:26:06 by rwassim           #+#    #+#             */
/*   Updated: 2025/06/27 21:59:37 by rwassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_up_redir(t_command *cmd, t_redirect *redir, t_shell *shell)
{
	int	result;

	shell->saved_stdout = dup(STDOUT_FILENO);
	if (shell->saved_stdout == -1)
		return (perror("dup"), shell->exit_status = 1, (void)0);
	shell->saved_stdin = dup(STDIN_FILENO);
	if (shell->saved_stdin == -1)
	{
		perror("dup");
		if (shell->saved_stdout)
			close(shell->saved_stdout);
		shell->exit_status = 1;
		return ;
	}
	if (!cmd->next && !cmd->name && cmd->redirects->type == R_HEREDOC)
	{
		result = process_heredocs(cmd, redir, shell);
		if (result != -1)
			handle_redirs_if_needed(cmd, shell);
	}
	else if (!cmd->next && !cmd->name && cmd->redirects)
		handle_redirs_if_needed(cmd, shell);
	end_safe_redir(shell);
}

static char	*generate_prompt(t_env *env_list)
{
	(void)env_list;
	return (ft_strdup("\001\033[1;34m\002minishell$ \001\033[0m\002"));
}

static char	*get_input(t_shell *shell)
{
	char	*prompt;
	char	*input;

	prompt = generate_prompt(shell->env_vars);
	if (!prompt)
		prompt = ft_strdup("\001\033[1;34m\002minishell$ \001\033[0m\002");
	input = readline(prompt);
	free(prompt);
	if (!input)
	{
		ft_putendl_fd("exit", 1);
		return (NULL);
	}
	return (input);
}

static void	minishell(char *line, t_shell *shell)
{
	t_command	*cmd;
	int			res;
	t_redirect	*redir;

	res = 0;
	cmd = parser(line, shell);
	if (!cmd)
		return ;
	if (check_nb_pipe(shell, cmd))
		return ;
	shell->cmd_list = cmd;
	redir = cmd->redirects;
	if (!cmd->next && is_builtin(cmd->name))
		only_one_builtin(shell, cmd);
	else if (!cmd->next && !cmd->name && cmd->redirects)
		set_up_redir(cmd, redir, shell);
	else
	{
		res = exec_readline(shell);
		if (res_readline(res, cmd, shell) == -1)
			return ;
	}
	free_commands(cmd);
	shell->cmd_list = NULL;
}

int	main(int ac, char **av, char **envp)
{
	char	*input;
	t_shell	*shell;

	shell = init_shell(ac, av, envp);
	if (!shell)
		return (EXIT_FAILURE);
	while (1)
	{
		setup_signals();
		input = get_input(shell);
		if (!input)
			break ;
		if (input[0] != '\0')
			add_history(input);
		handle_signal(shell);
		minishell(input, shell);
		free(input);
	}
	return (free_shell(shell));
}
