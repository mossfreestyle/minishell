/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_and_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 12:01:02 by mfernand          #+#    #+#             */
/*   Updated: 2025/06/24 22:17:08 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_and_free_all(t_shell *shell)
{
	close_all_pipes(shell);
	free_shell(shell);
}

void	close_all_pipes(t_shell *shell)
{
	int	i;

	i = -1;
	while (++i < shell->pipeline.n_pipes)
	{
		if (shell->pipeline.pipefd[i][0] >= 0)
			close(shell->pipeline.pipefd[i][0]);
		if (shell->pipeline.pipefd[i][1] >= 0)
			close(shell->pipeline.pipefd[i][1]);
	}
}
