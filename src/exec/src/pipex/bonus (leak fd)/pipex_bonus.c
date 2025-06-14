/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 10:44:46 by mfernand          #+#    #+#             */
/*   Updated: 2025/06/02 16:24:24 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex;
	int		start_cmd;

	if (ac < 5)
		return (bonus_check_errors(-1, -1, ac, 0));
	pipex.av = av;
	pipex.envp = envp;
	if (ft_strncmp(av[1], "here_doc", 8) == 0)
	{
		if (ac < 6)
			return (bonus_check_errors(-1, -1, ac, 0));
		handle_here_doc(av, &pipex.fd_in, &pipex.fd_out, &start_cmd);
	}
	else
		handle_files(av, &pipex.fd_in, &pipex.fd_out, &start_cmd);
	if (pipex.fd_in < 0 || pipex.fd_out < 0)
	{
		ft_putstr_fd("An error occured when opening files\n", 2);
		exit(EXIT_FAILURE);
	}
	execute_pipeline(&pipex, start_cmd, ac - 2);
	close(pipex.fd_in);
	close(pipex.fd_out);
	return (0);
}
