/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 20:46:40 by mfernand          #+#    #+#             */
/*   Updated: 2025/06/24 14:03:24 by mfernand         ###   ########.fr       */
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

void	finish_exec(t_command *cmd, char *path, char **envp)
{
	if (handle_redirections(cmd) == -1)
	{
		free_array(envp);
		free(path);
		exit(1);
	}
	execve(path, cmd->args, envp);
	print_error(cmd->name);
	free_array(envp);
	free(path);
	exit(127);
}
