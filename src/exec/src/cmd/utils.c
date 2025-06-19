/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 12:30:07 by mfernand          #+#    #+#             */
/*   Updated: 2025/06/19 13:17:34 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_not_found(char **envp, t_shell *shell)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(shell->cmd_list->name, 2);
	ft_putstr_fd(": command not found\n", 2);
	free_array(envp);
	exit(127);
}

int	open_fd(char *av, int i) //unused
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

void	check_pid(int pid, t_shell *shell)
{
	if (pid == -1)
	{
		close_all(shell); // a fix
		ft_putstr_fd("An error occured when creating PID\n", 2);
		exit(EXIT_FAILURE);
	}
}

static int	env_list_size(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		if (env->name && env->value)
			count++;
		env = env->next;
	}
	return (count);
}

char	**env_list_to_array(t_env *env)
{
	int		size;
	char	**array;
	int		i;
	char	*tmp;

	i = 0;
	i = 0;
	size = env_list_size(env);
	array = malloc(sizeof(char *) * (size + 1));
	if (!array)
		return (NULL);
	while (env)
	{
		if (env->name && env->value)
		{
			tmp = ft_strjoin(env->name, "=");
			array[i] = ft_strjoin(tmp, env->value);
			free(tmp);
			i++;
		}
		env = env->next;
	}
	array[i] = NULL;
	return (array);
}
