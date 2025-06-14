/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 23:58:18 by mfernand          #+#    #+#             */
/*   Updated: 2025/06/02 11:46:19 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_path(char *cmd, char **envp)
{
	char	**path_lst;
	char	*path_env;
	char	*path_cmd;
	int		i;

	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	path_env = NULL;
	path_cmd = NULL;
	i = 0;
	while (envp[i])
		if (!ft_strncmp(envp[i++], "PATH=", 5))
			path_env = envp[i - 1] + 5;
	if (!path_env)
		return (NULL);
	path_lst = ft_split(path_env, ':');
	if (!path_lst)
		return (NULL);
	i = 0;
	return (link_path(path_lst, path_cmd, cmd));
}

char	*link_path(char **path_lst, char *path_cmd, char *cmd)
{
	int		i;
	char	*tmp;

	i = 0;
	if (!path_lst || !cmd)
		return (NULL);
	while (path_lst[i])
	{
		tmp = ft_strjoin(path_lst[i++], "/");
		path_cmd = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(path_cmd, X_OK) == 0)
			return (free_tab(path_lst), path_cmd);
		free(path_cmd);
	}
	return (free_tab(path_lst), NULL);
}
