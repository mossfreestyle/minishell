/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 14:47:07 by mfernand          #+#    #+#             */
/*   Updated: 2025/06/02 11:01:18 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **envp)
{
	t_fds		fds;
	t_cmdinfo	info;
	int			pid[2];

	if (ac != 5)
		return (check_arg(ac));
	fds.fd_out = open_fd(av[4], 1);
	fds.fd_in = open_fd(av[1], 2);
	if (check_errors(&fds, pipe(fds.fd), av))
		return (1);
	pid[0] = fork();
	init_pid(pid[0], &fds);
	if (!pid[0])
		child1_process(av[2], envp, &fds, &info);
	pid[1] = fork();
	init_pid(pid[1], &fds);
	if (!pid[1])
		child2_process(av[3], envp, &fds, &info);
	return (close_fd(&fds, pid));
}

void	init_pid(int pid, t_fds *fds)
{
	if (pid == -1)
	{
		close_all(fds);
		ft_putstr_fd("An error occured when creating PID\n", 2);
		exit(EXIT_FAILURE);
	}
}

int	close_fd(t_fds *fds, int pid[])
{
	int	status;
	int	i;

	i = 0;
	close_all(fds);
	while (i < 2)
	{
		waitpid(pid[i], &status, 0);
		i++;
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (0);
}

int	open_fd(char *av, int i)
{
	int	file;

	file = 0;
	if (i == 0)
		file = open(av, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (i == 1)
	{
		file = open(av, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	else if (i == 2)
	{
		file = open(av, O_RDONLY);
	}
	if (file < 0)
		perror(av);
	return (file);
}
