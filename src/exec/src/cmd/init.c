/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwassim <rwassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 23:17:38 by mfernand          #+#    #+#             */
/*   Updated: 2025/06/27 22:18:10 by rwassim          ###   ########.fr       */
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
			return (perror("pipe"));
	}
}

void	handle_redirs_if_needed(t_command *cmd, t_shell *shell)
{
	if (handle_redirections(cmd, shell) == -1)
		shell->exit_status = 1;
}

int	process_heredocs(t_command *cmd, t_redirect *redir, t_shell *shell)
{
	while (redir)
	{
		if (redir->type == R_HEREDOC)
		{
			if (exec_here_doc(cmd, redir, shell) == -1)
				return (-1);
		}
		redir = redir->next;
	}
	return (0);
}

void	free_envp_path(char **envp, char *path)
{
	if (envp)
		free_array(envp);
	if (path)
		free(path);
}
