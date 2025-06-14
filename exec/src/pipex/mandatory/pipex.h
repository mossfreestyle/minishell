/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 14:28:46 by mfernand          #+#    #+#             */
/*   Updated: 2025/06/01 19:42:31 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include "../libft/printf/ft_printf.h"
# include <fcntl.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_fds
{
	int		fd_in;
	int		fd_out;
	int		fd[2];
}			t_fds;

typedef struct s_cmdinfo
{
	char	**cmd_args;
	char	*path;
	char	*cmd;
}			t_cmdinfo;

// errros
int			check_errors(t_fds *fds, int pipe_res, char **av);
void		free_tab(char **tab);

int			check_arg(int ac);

// find_paths
char		*find_path(char *cmd, char **envp);
char		*link_path(char **path_lst, char *path_cmd, char *cmd);

// process
void		child1_process(char *av, char **envp, t_fds *fds, t_cmdinfo *info);
void		child2_process(char *av, char **envp, t_fds *fds, t_cmdinfo *info);
int			clean_exec(t_cmdinfo *info, t_fds *fds);
void		setup_cmd(char *av, t_cmdinfo *info, char **envp, t_fds *fds);

void		init_pid(int pid, t_fds *fds);
int			close_fd(t_fds *fds, int pid[]);

int			open_fd(char *av, int i);

void		close_all(t_fds *fds);
#endif