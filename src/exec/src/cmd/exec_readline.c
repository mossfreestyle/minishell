/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_readline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 10:53:55 by mfernand          #+#    #+#             */
/*   Updated: 2025/06/19 11:23:14 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_readline(t_shell *shell)
{
    while(shell->cmd_list)
    {
        if (!shell->cmd_list->next)
            shell->exit_status = exec_last_command(shell);
        if (is_here_doc(shell->cmd_list->name))
        {
            shell->exit_status = exec_here_doc(shell);
        }
        else if (is_builtin(shell->cmd_list->name))
        {
            shell->exit_status = exec_built_in(shell);
            //gestion d exit
        }
        else
        {
            shell->exit_status = exec_commands(shell);
        }
    }
}
