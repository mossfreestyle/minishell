/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 10:46:17 by mfernand          #+#    #+#             */
/*   Updated: 2025/06/19 13:16:04 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_last_command(t_shell *shell);
static int	exec_first_command(t_shell *shell);
static void	close_and_wait(t_shell *shell, int status);
static void	error(char **envp, char *full_path, t_shell *shell);

int	exec_commands(t_shell *shell)
{
	int		status;
	pid_t	pid;
	int		i;

	exec_first_command(shell);
	while (shell->cmd_list->next)
	{
		shell->cmd_list = shell->cmd_list->next;
	}
	exec_last_command(shell);
	return (close_and_wait(shell, status), shell->exit_status);
}

static int	exec_first_command(t_shell *shell)
{
	pid_t	pid;
	char	**envp;
	char	*full_path;

	envp = env_list_to_array(shell->env_vars);
	if ((full_path == find_path(shell->cmd_list->name, envp)) == NULL)
		cmd_not_found(envp, shell);
	pid = fork();
	check_pid(pid, shell);
	if (pid == 0)
	{
		if (shell->pipeline.n_pipes > 0)
			dup2(shell->pipeline.pipefd[0][1], STDOUT_FILENO);
		// besoin de gerer le cas d erreur
		close_all_pipes(shell);
		handle_redirections(shell->cmd_list);
		if (is_builtin(shell->cmd_list->name))
			exit(exec_built_in(shell));
		else
			execve(full_path, shell->cmd_list->args, envp);
		error(envp, full_path, shell);
	}
	free(envp);
	free(full_path);
	close(shell->pipeline.pipefd[0][1]);
	return (0);
}

static int	exec_last_command(t_shell *shell)
{
	int		last;
	pid_t	pid;
	char	**envp;
	char	*full_path;

	last = shell->pipeline.n_pipes - 1;
	envp = env_list_to_array(shell->env_vars);
	if ((full_path == find_path(shell->cmd_list->name, envp)) == NULL)
		cmd_not_found(envp, shell);
	pid = fork();
	check_pid(pid, shell);
	if (pid == 0)
	{
		if (shell->pipeline.n_pipes > 0)
			dup2(shell->pipeline.pipefd[last][0], STDIN_FILENO);
		// besoin de gerer le cas d erreur
		close_all_pipes(shell);
		handle_redirections(shell->cmd_list);
		if (is_builtin(shell->cmd_list->name))
			exit(exec_built_in(shell));
		else
			execve(full_path, shell->cmd_list->args, envp);
		error(envp, full_path, shell);
	}
	free(envp);
	free(full_path);
	close(shell->pipeline.pipefd[last][0]);
	return (0);
}

static void	close_and_wait(t_shell *shell, int status)
{
	close_and_free_all(shell);
	while (wait(&status) > 0)
		if (WIFEXITED(status))
			shell->exit_status = WEXITSTATUS(status);
}

static void	error(char **envp, char *full_path, t_shell *shell)
{
	if (envp)
		free(envp);
	if (full_path)
		free(full_path);
	// close(fd)  qqchose
	perror("minishell");
	exit(127);
}
