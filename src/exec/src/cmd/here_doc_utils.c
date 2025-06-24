/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwassim <rwassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 20:46:40 by mfernand          #+#    #+#             */
/*   Updated: 2025/06/24 15:58:46 by rwassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	has_quotes(char *delimiter)
{
	return (ft_strchr(delimiter, '"') || ft_strchr(delimiter, '\''));
}

char	*expand_heredoc_line(char *line, t_shell *shell)
{
	char	*result;
	int		i;

	result = ft_strdup("");
	i = 0;
	while (line[i])
	{
		if (line[i] == '$')
			result = expand_var(line, &i, shell, result);
		else
			result = add_char(line, &i, result);
	}
	return (result);
}

int	is_here_doc(char *name)
{
	if (!name)
		return (0);
	return (!ft_strcmp(name, "<<"));
}

void	finish_exec(t_command *cmd, char *path, char **envp, t_shell *shell)
{
	if (handle_redirections(cmd, shell) == -1)
	{
		free_array(envp);
		free(path);
		free_shell(shell);
		exit(1);
	}
	if (!path)
	{
		print_error(cmd->name);
		free_array(envp);
		free_shell(shell);
		exit(127);
	}
	execve(path, cmd->args, envp);
	print_error(cmd->name);
	free_array(envp);
	free(path);
	free_shell(shell);
	exit(127);
}
