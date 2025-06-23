/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_readline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 10:53:55 by mfernand          #+#    #+#             */
/*   Updated: 2025/06/23 10:07:14 by mfernand         ###   ########.fr       */
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

	if (!shell->cmd_list || !shell->cmd_list->name)
		return (0);
	cmd = shell->cmd_list;
	while (cmd)
	{
		redir = cmd->redirects;
		while (redir)
		{
			if (redir->type == R_HEREDOC)
				exec_here_doc(cmd, redir);
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	if (!shell->cmd_list)
		return (0);
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
	if (is_builtin(shell->av[0]))
		return (exec_one_builtin(shell, cmd));
	else
		return (exec_one_cmd(shell, cmd));
}

static int	exec_one_builtin(t_shell *shell, t_command *cmd)
{
	int	status;

	handle_redirections(cmd);
	status = exec_built_in(cmd, shell);
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
	envp = env_list_to_array(shell->env_vars);
	path = find_path(cmd->name, envp);
	if (pid == 0)
	{
		handle_redirections(cmd);
		execve(path, cmd->args, envp);
		print_error(cmd->name);
		exit(127);
	}
	free_array(envp);
	free(path);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		shell->exit_status = WEXITSTATUS(status);
	else
		shell->exit_status = 1;
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
