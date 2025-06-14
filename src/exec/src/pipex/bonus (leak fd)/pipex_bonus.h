/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 02:32:43 by mfernand          #+#    #+#             */
/*   Updated: 2025/05/31 00:35:50 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../libft/gnl/get_next_line.h"
# include "../libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_pipex
{
	int		fd_in;
	int		fd_out;
	char	**av;
	char	**envp;
}			t_pipex;

// errros
int			bonus_check_errors(int fd_in, int fd_out, int ac, int pipe_res);

// find_paths
char		*find_path(char *cmd, char **envp);

// process
int			clean_exec(char **cmd_args, char *path);

// here doc
void		set_here_doc(char *keyword, int fd, int start_cmd, char **av);
void		handle_here_doc(char **av, int *fd_in, int *fd_out, int *start_cmd);

// utils
int			open_file(char *av, int i);
void		handle_files(char **av, int *fd_in, int *fd_out, int *start_cmd);
int			len(char **av);

void		execute_pipeline(t_pipex *pipex, int cmd_index, int last_cmd_index);
#endif