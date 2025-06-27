/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_readline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwassim <rwassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 10:53:55 by mfernand          #+#    #+#             */
/*   Updated: 2025/06/27 22:14:50 by rwassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_one_command(t_command *cmd, t_shell *shell);
static int	exec_one_builtin(t_shell *shell, t_command *cmd);
static int	exec_one_cmd(t_shell *shell, t_command *cmd);

int	exec_readline(t_shell *shell)
{
	t_command	*cmd;
	t_redirect	*redir;

	if (!shell->cmd_list)
		return (0);
	cmd = shell->cmd_list;
	while (cmd)
	{
		redir = cmd->redirects;
		while (redir)
		{
			if (redir->type == R_HEREDOC)
				if (exec_here_doc(cmd, redir, shell) == -1)
					return (shell->cmd_list = NULL, -1);
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	close_unused_heredoc_fds(shell->cmd_list);
	if (!shell->cmd_list->next)
		shell->exit_status = exec_one_command(shell->cmd_list, shell);
	else
		shell->exit_status = exec_commands(shell);
	return (shell->exit_status);
}

static int	exec_one_command(t_command *cmd, t_shell *shell)
{
	while (cmd && cmd->next)
		cmd = cmd->next;
	if (!cmd)
		return (1);
	if (is_builtin(cmd->name))
		return (exec_one_builtin(shell, cmd));
	else
		return (exec_one_cmd(shell, cmd));
}

static int	exec_one_builtin(t_shell *shell, t_command *cmd)
{
	int	status;
	int	saved_stdout;
	int	saved_stdin;

	saved_stdout = dup(STDOUT_FILENO);
	saved_stdin = dup(STDIN_FILENO);
	if (handle_redirections(cmd, shell) == -1)
	{
		dup2(saved_stdout, STDOUT_FILENO);
		dup2(saved_stdin, STDIN_FILENO);
		close(saved_stdout);
		close(saved_stdin);
		return (1);
	}
	status = exec_built_in(cmd, shell, NULL, NULL);
	dup2(saved_stdout, STDOUT_FILENO);
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdout);
	close(saved_stdin);
	shell->exit_status = status;
	return (status);
}

static int	exec_one_cmd(t_shell *shell, t_command *cmd)
{
	pid_t	pid;
	int		status;
	char	**envp;
	char	*path;

	pid = fork();
	if (pid < 0)
		return (perror("fork"), 1);
	if (pid == 0)
	{
		envp = env_list_to_array(shell->env_vars);
		path = find_path(cmd->name, envp);
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		finish_exec(cmd, path, envp, shell);
	}
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	setup_signals();
	check_sig(status, shell);
	return (shell->exit_status);
}

void	print_error(char *name)
{
	ft_putstr_fd("minishell: ", 2);
	if (name && name[0])
		ft_putstr_fd(name, 2);
	else
		ft_putstr_fd("unknown", 2);
	ft_putstr_fd(": command not found\n", 2);
}
