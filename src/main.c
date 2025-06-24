/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 10:26:06 by rwassim           #+#    #+#             */
/*   Updated: 2025/06/24 14:21:27 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static char	*generate_prompt(t_env *env_list)
// {
// 	char	*user;
// 	char	*cwd;
// 	char	*prompt;
// 	size_t	len_prompt;

// 	user = getenv_lst("USER", env_list);
// 	if (!user)
// 		user = "user";
// 	cwd = getcwd(NULL, 0);
// 	if (!cwd)
// 		cwd = ft_strdup(".");
// 	len_prompt = ft_strlen(user) + ft_strlen(cwd) + 14;
// 	prompt = malloc(len_prompt);
// 	if (!prompt)
// 	{
// 		free(cwd);
// 		return (NULL);
// 	}
// 	ft_strlcpy(prompt, user, len_prompt);
// 	ft_strlcat(prompt, "@minishell:", len_prompt);
// 	ft_strlcat(prompt, cwd, len_prompt);
// 	ft_strlcat(prompt, "$ ", len_prompt);
// 	free(cwd);
// 	return (prompt);
// }

static void	set_up_redir(t_command *cmd, t_redirect *redir, t_shell *shell)
{
	if (!cmd->next && !cmd->name && cmd->redirects)
	{
		while (redir)
		{
			if (redir->type == R_HEREDOC)
			{
				if (exec_here_doc(cmd, redir, shell) == -1)
					break ;
			}
			redir = redir->next;
		}
		handle_redirections(cmd);
	}
}
static int	res_readline(int res, t_command *cmd, t_shell *shell)
{
	if (res == -1)
	{
		free_commands(cmd);
		shell->cmd_list = NULL;
		return (-1);
	}
	return (0);
}

static char	*generate_prompt(t_env *env_list)
{
	(void)env_list;
	return (ft_strdup("minishell$ "));
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
	// printf("a%s\n",cmd->name);
	if (!cmd)
		return ;
	shell->cmd_list = cmd;
	redir = cmd->redirects;
	if (!cmd->next && is_builtin(cmd->name))
		shell->exit_status = exec_built_in(cmd, shell);
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
