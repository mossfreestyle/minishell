/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 23:17:38 by mfernand          #+#    #+#             */
/*   Updated: 2025/06/19 13:12:12 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*init_env(char **envp)
{
	t_env	*head;
	t_env	*last;
	t_env	*curr_node;
	int		i;
	char	*eq;

	head = NULL;
	last = NULL;
	i = -1;
	while (envp && envp[++i])
	{
		eq = ft_strchr(envp[i], '=');
		curr_node = malloc(sizeof(t_env));
		if (!curr_node)
			return (NULL);
		curr_node->name = ft_substr(envp[i], 0, eq - envp[i]);
		curr_node->value = ft_strdup(eq + 1);
		curr_node->exported = 1;
		curr_node->next = NULL;
		if (!head)
			head = curr_node;
		else
			last->next = curr_node;
		last = curr_node;
	}
	return (head);
}

int	count_cmds(t_command *cmd)
{
	int	n;

	n = 0;
	while (cmd)
	{
		n++;
		cmd = cmd->next;
	}
	return (n);
}

void	init_pipes(t_shell *shell)
{
	int	i;
	int	n_cmds;

	i = -1;
	n_cmds = count_cmds(shell->cmd_list);
	shell->pipeline.n_pipes = n_cmds - 1;
	while (++i < shell->pipeline.n_pipes)
	{
		if (pipe(shell->pipeline.pipefd[i]) == -1)
			perror("pipe");
	}
}
