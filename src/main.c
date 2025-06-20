/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwassim <rwassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 10:26:06 by rwassim           #+#    #+#             */
/*   Updated: 2025/06/20 14:06:32 by rwassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*generate_prompt(t_env *env_list)
{
	char	*user;
	char	*cwd;
	char	*prompt;
	size_t	len_prompt;

	user = getenv_lst("USER", env_list);
	if (!user)
		user = "user";
	cwd = getcwd(NULL, 0);
	if (!cwd)
		cwd = ft_strdup(".");
	len_prompt = ft_strlen(user) + ft_strlen(cwd) + 14;
	prompt = malloc(len_prompt);
	if (!prompt)
	{
		free(cwd);
		return (NULL);
	}
	ft_strlcpy(prompt, user, len_prompt);
	ft_strlcat(prompt, "@minishell:", len_prompt);
	ft_strlcat(prompt, cwd, len_prompt);
	ft_strlcat(prompt, "$ ", len_prompt);
	free(cwd);
	return (prompt);
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
		handle_eof(shell);
	return (input);
}

static void minishell(char *line, t_shell *shell)
{
	t_command *cmd;

	cmd = parser(line, shell);
	if (!cmd)
		return ;
	if (!cmd->next && is_builtin(cmd))
}