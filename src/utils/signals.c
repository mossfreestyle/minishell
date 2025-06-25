/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwassim <rwassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 11:10:20 by rwassim           #+#    #+#             */
/*   Updated: 2025/06/25 14:32:57 by rwassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal = 0;

void	handle_signal(t_shell *shell)
{
	if (g_signal == SIGINT)
	{
		shell->exit_status = 130;
		g_signal = 0;
	}
	else if (g_signal == SIGQUIT)
	{
		shell->exit_status = 131;
		g_signal = 0;
	}
}

void	exec_signals(int sig)
{
	if (sig == SIGQUIT)
		write(2, "Quit (core dumped)\n", 19);
	if (sig == SIGINT)
		write(2, "\n", 1);
}

static void	handle_sigint(int sig)
{
	g_signal = sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_eof(t_shell *shell)
{
	ft_putendl_fd("exit", 1);
	exit(free_shell(shell));
}

void	setup_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}
