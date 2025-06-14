/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 00:06:09 by mfernand          #+#    #+#             */
/*   Updated: 2025/06/02 11:51:09 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child1_process(char *av, char **envp, t_fds *fds, t_cmdinfo *info)
{
	setup_cmd(av, info, envp, fds);
	if (dup2(fds->fd_in, STDIN_FILENO) == -1)
		exit(clean_exec(info, fds));
	if (dup2(fds->fd[1], STDOUT_FILENO) == -1)
		exit(clean_exec(info, fds));
	close_all(fds);
	execve(info->path, info->cmd_args, envp);
	exit(clean_exec(info, fds));
}

void	child2_process(char *av, char **envp, t_fds *fds, t_cmdinfo *info)
{
	setup_cmd(av, info, envp, fds);
	if (dup2(fds->fd[0], STDIN_FILENO) == -1)
		exit(clean_exec(info, fds));
	if (dup2(fds->fd_out, STDOUT_FILENO) == -1)
		exit(clean_exec(info, fds));
	close_all(fds);
	execve(info->path, info->cmd_args, envp);
	exit(clean_exec(info, fds));
}

int	clean_exec(t_cmdinfo *info, t_fds *fds)
{
	if (info->cmd_args)
		free_tab(info->cmd_args);
	if (info->path)
		free(info->path);
	close_all(fds);
	return (1);
}

void	setup_cmd(char *av, t_cmdinfo *info, char **envp, t_fds *fds)
{
	info->cmd = av;
	if (!info->cmd || !*info->cmd)
	{
		close_all(fds);
		exit(EXIT_FAILURE);
	}
	info->cmd_args = ft_split(info->cmd, ' ');
	if (!info->cmd_args || !(info->cmd_args[0]))
	{
		close_all(fds);
		exit(clean_exec(info, fds));
	}
	info->path = find_path(info->cmd_args[0], envp);
	if (!info->path)
	{
		ft_putstr_fd("pipex : ", 2);
		ft_putstr_fd(info->cmd, 2);
		ft_putendl_fd(" : command not found", 2);
		close_all(fds);
		clean_exec(info, fds);
		exit(127);
	}
}
