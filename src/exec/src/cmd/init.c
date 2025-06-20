/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 23:17:38 by mfernand          #+#    #+#             */
/*   Updated: 2025/06/20 11:39:30 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
