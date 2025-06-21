/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwassim <rwassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 13:46:14 by rwassim           #+#    #+#             */
/*   Updated: 2025/06/21 11:38:32 by rwassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(t_token *tokens)
{
	t_token	*temp;

	while (tokens)
	{
		temp = tokens;
		tokens = tokens->next;
		if (temp->content)
			free(temp->content);
		free(temp);
	}
}

void	free_redirects(t_redirect *redirects)
{
	t_redirect	*current;
	t_redirect	*next;

	current = redirects;
	while (current)
	{
		next = current->next;
		if (current->filename)
			free(current->filename);
		free(current);
		current = next;
	}
}

int	free_shell(t_shell *shell)
{
	int	exit_status;

	if (!shell)
		return (EXIT_FAILURE);
	exit_status = shell->exit_status;
	if (shell->pwd)
		free(shell->pwd);
	free_env(shell->env_vars);
	close_all_pipes(shell);
	free_commands(shell->cmd_list);
	rl_clear_history();
	free(shell);
	return (exit_status);
}

void	free_command(t_command *cmd)
{
	if (!cmd)
		return ;
	if (cmd->name)
		free(cmd->name);
	if (cmd->args)
		free_array(cmd->args);
	if (cmd->redirects)
		free_redirects(cmd->redirects);
	if (cmd->heredoc_fd != -1)
		close(cmd->heredoc_fd);
	free(cmd);
}

void	free_commands(t_command *cmd)
{
    t_command	*tmp;

    if (!cmd)
        return;
    while (cmd)
    {
        tmp = cmd;
        cmd = cmd->next;
        free_command(tmp);
    }
}
