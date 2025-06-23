/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_here_doc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwassim <rwassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 11:14:03 by mfernand          #+#    #+#             */
/*   Updated: 2025/06/23 16:00:40 by rwassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	handle_here_doc_sig(t_shell *shell, int	heredoc_pipe[2], char *line);

bool has_quotes(char *delimiter)
{
    return (ft_strchr(delimiter, '"') || ft_strchr(delimiter, '\''));
}

char *expand_heredoc_line(char *line, t_shell *shell)
{
    char *result = ft_strdup("");
    int i = 0;
    
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

int exec_here_doc(t_command *cmd, t_redirect *redir, t_shell *shell)
{
    int heredoc_pipe[2];
    char *line;
    char *processed_line;
    bool should_expand;

    should_expand = !has_quotes(redir->filename);
    if (cmd->heredoc_fd != -1)
        close(cmd->heredoc_fd);
    if (pipe(heredoc_pipe) == -1)
        return (perror("pipe"), -1);
    while (1)
    {
        line = readline("> ");
		// handle_here_doc_sig(shell, heredoc_pipe, line);
        if (!line || !ft_strcmp(line, redir->filename))
            break;
        if (should_expand)
        {
            processed_line = expand_heredoc_line(line, shell);
            write(heredoc_pipe[1], processed_line, ft_strlen(processed_line));
            free(processed_line);
        }
        else
            write(heredoc_pipe[1], line, ft_strlen(line));
        write(heredoc_pipe[1], "\n", 1);
        free(line);
    }
    free(line);
    close(heredoc_pipe[1]);
    cmd->heredoc_fd = heredoc_pipe[0];
    return (0);
}

void	handle_here_doc_sig(t_shell *shell, int	heredoc_pipe[2], char *line)
{
	if (g_signal == SIGINT)
	{
		write(1, "\n", 1);
		shell->exit_status = 130;
	}
	free(line);
	close(heredoc_pipe[1]);
	close(heredoc_pipe[0]);
	if (g_signal == SIGQUIT)
	{
		ft_putstr_fd("minishell: warning: here-document at line 13 delimited by end-of-file (wanted `", 2);
		ft_putstr_fd(line, 2);
		ft_putstr_fd("\n')", 2);
	}
}
