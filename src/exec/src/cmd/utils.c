/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwassim <rwassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 12:30:07 by mfernand          #+#    #+#             */
/*   Updated: 2025/06/20 11:32:50 by rwassim          ###   ########.fr       */
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

void	free_array(char **ptr)
{
	int	i;

	i = 0;
	if (!ptr)
		return ;
	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
}