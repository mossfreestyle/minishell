/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_here_doc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwassim <rwassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 11:14:03 by mfernand          #+#    #+#             */
/*   Updated: 2025/06/25 14:16:17 by rwassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	heredoc_fork(t_command *cmd, t_redirect *redir, t_shell *shell,
				int *heredoc_pipe);
static void	heredoc_child(int write_fd, t_redirect *redir, t_shell *shell);
static void	msg_ctrl_d(int write_fd, t_redirect *redir, char *line,
				t_shell *shell);
static void	heredoc_sig_handler(int signo);

int	exec_here_doc(t_command *cmd, t_redirect *redir, t_shell *shell)
{
	int	heredoc_pipe[2];

	if (cmd->heredoc_fd != -1)
		close(cmd->heredoc_fd);
	if (pipe(heredoc_pipe) == -1)
		return (close(cmd->heredoc_fd), perror("pipe"), -1);
	return (heredoc_fork(cmd, redir, shell, heredoc_pipe));
}

static void	heredoc_sig_handler(int signo)
{
	(void)signo;
	write(1, "\n", 1);
	exit(130);
}

static void	msg_ctrl_d(int write_fd, t_redirect *redir, char *line,
		t_shell *shell)
{
	if (!line)
	{
		ft_putstr_fd("minishell: warning: here-document delimited ", 2);
		ft_putstr_fd("by end-of-file (wanted `", 2);
		ft_putstr_fd(redir->filename, 2);
		ft_putstr_fd("')\n", 2);
		close(write_fd);
		free_shell(shell);
		exit(0);
	}
}

static void	heredoc_child(int write_fd, t_redirect *redir, t_shell *shell)
{
	char	*line;
	char	*processed_line;
	bool	should_expand;

	should_expand = !has_quotes(redir->filename);
	signal(SIGINT, heredoc_sig_handler);
	while (1)
	{
		line = readline("> ");
		msg_ctrl_d(write_fd, redir, line, shell);
		if (!ft_strcmp(line, redir->filename))
			break ;
		if (should_expand)
		{
			processed_line = expand_heredoc_line(line, shell);
			ft_putendl_fd(processed_line, write_fd);
			free(processed_line);
		}
		else
			ft_putendl_fd(line, write_fd);
		free(line);
	}
	close_write_fd_and_free_line(write_fd, line);
	free_shell(shell);
	exit(0);
}

static int	heredoc_fork(t_command *cmd, t_redirect *redir, t_shell *shell,
		int *heredoc_pipe)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		close(heredoc_pipe[0]);
		heredoc_child(heredoc_pipe[1], redir, shell);
	}
	else if (pid > 0)
	{
		close(heredoc_pipe[1]);
		waitpid(pid, &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
			return (close(heredoc_pipe[0]), shell->exit_status = 130, -1);
		cmd->heredoc_fd = heredoc_pipe[0];
		return (0);
	}
	else
	{
		perror("fork");
		return (close(heredoc_pipe[0]), close(heredoc_pipe[1]), -1);
	}
	return (0);
}
