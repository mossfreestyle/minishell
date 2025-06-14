/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 17:48:03 by mfernand          #+#    #+#             */
/*   Updated: 2025/05/31 00:31:46 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	execute_last_cmd(int fd_in, int fd_out, char *cmd, char **envp)
{
	char	**cmd_args;
	char	*path;

	dup2(fd_in, STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	close(fd_in);
	close(fd_out);
	cmd_args = ft_split(cmd, ' ');
	path = find_path(cmd_args[0], envp);
	if (!cmd_args || !path)
	{
		clean_exec(cmd_args, path);
		exit(127);
	}
	if (execve(path, cmd_args, envp) == -1)
	{
		clean_exec(cmd_args, path);
		exit(127);
	}
}

static void	execute_cmd(int fd_in, int fd_out, char *cmd, char **envp)
{
	char	**cmd_args;
	char	*path;

	dup2(fd_in, STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	close(fd_in);
	close(fd_out);
	cmd_args = ft_split(cmd, ' ');
	path = find_path(cmd_args[0], envp);
	if (!cmd_args || !path)
	{
		clean_exec(cmd_args, path);
		exit(127);
	}
	if (execve(path, cmd_args, envp) == -1)
	{
		clean_exec(cmd_args, path);
		exit(127);
	}
}

void	execute_pipeline(t_pipex *pipex, int cmd_index, int last_cmd_index)
{
	int	fd[2];
	int	pid;

	if (cmd_index == last_cmd_index)
	{
		execute_last_cmd(pipex->fd_in, pipex->fd_out, pipex->av[cmd_index],
			pipex->envp);
	}
	if (pipe(fd) == -1)
		exit(EXIT_FAILURE);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		execute_cmd(pipex->fd_in, fd[1], pipex->av[cmd_index], pipex->envp);
	}
	else
	{
		close(fd[1]);
		pipex->fd_in = fd[0];
		execute_pipeline(pipex, cmd_index + 1, last_cmd_index);
		close(fd[0]);
		waitpid(pid, NULL, 0);
	}
}
