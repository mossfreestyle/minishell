/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_here_doc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 11:14:03 by mfernand          #+#    #+#             */
/*   Updated: 2025/06/23 17:16:26 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void heredoc_sig_handler(int signo)
{
    (void)signo;
    write(1, "\n", 1);
    exit(130);
}

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

// int exec_here_doc(t_command *cmd, t_redirect *redir, t_shell *shell)
// {
//     int heredoc_pipe[2];
//     char *line;
//     char *processed_line;
//     bool should_expand;

//     should_expand = !has_quotes(redir->filename);
//     if (cmd->heredoc_fd != -1)
//         close(cmd->heredoc_fd);
//     if (pipe(heredoc_pipe) == -1)
//         return (perror("pipe"), -1);
//     signal(SIGINT, SIG_DFL);
//     g_signal = 0;
//     while (1)
//     {
//         line = readline("> ");
// 		if(!line)
//         {
//             write(1, "\n", 1);
//             shell->exit_status = 130;
//             free(line);
//             close(heredoc_pipe[1]);
//             close(heredoc_pipe[0]);
//             signal(SIGINT, heredoc_sig_handler);
//             return (-1);
//         }
//         if (!ft_strcmp(line, redir->filename))
//             break ;
//         if (should_expand)
//         {
//             processed_line = expand_heredoc_line(line, shell);
//             write(heredoc_pipe[1], processed_line,
// ft_strlen(processed_line));
//             free(processed_line);
//         }
//         else
//             write(heredoc_pipe[1], line, ft_strlen(line));
//         write(heredoc_pipe[1], "\n", 1);
//         free(line);
//     }
//     free(line);
//     close(heredoc_pipe[1]);
//     cmd->heredoc_fd = heredoc_pipe[0];
//     signal(SIGINT, heredoc_sig_handler);
//     return (0);
// }

static void	msg_ctrl_d(int write_fd, t_redirect *redir, char *line)
{
	if (!line)
	{
		ft_putstr_fd("minishell: warning: here-document delimited by end-of-file (wanted `",
			2);
		ft_putstr_fd(redir->filename, 2);
		ft_putstr_fd("')\n", 2);
		close(write_fd);
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
		msg_ctrl_d(write_fd, redir, line);
		if (!ft_strcmp(line, redir->filename))
			break ;
		if (should_expand)
		{
			processed_line = expand_heredoc_line(line, shell);
			write(write_fd, processed_line, ft_strlen(processed_line));
			free(processed_line);
		}
		else
			write(write_fd, line, ft_strlen(line));
		write(write_fd, "\n", 1);
		free(line);
	}
	free(line);
	close(write_fd);
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
		signal(SIGINT, heredoc_sig_handler);
		if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
		{
			close(heredoc_pipe[0]);
			shell->exit_status = 130;
			return (-1);
		}
		cmd->heredoc_fd = heredoc_pipe[0];
		return (0);
	}
	else
	{
		perror("fork");
		close(heredoc_pipe[0]);
		close(heredoc_pipe[1]);
		return (-1);
	}
	return (0);
}

int	exec_here_doc(t_command *cmd, t_redirect *redir, t_shell *shell)
{
	int	heredoc_pipe[2];

	if (cmd->heredoc_fd != -1)
		close(cmd->heredoc_fd);
	if (pipe(heredoc_pipe) == -1)
		return (perror("pipe"), -1);
	return (heredoc_fork(cmd, redir, shell, heredoc_pipe));
}
