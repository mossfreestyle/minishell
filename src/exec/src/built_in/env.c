/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 12:17:51 by mfernand          #+#    #+#             */
/*   Updated: 2025/06/15 10:53:58 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		printf_env(t_env *env);
static t_env	*set_up_env(char *line);
static void		free_env(t_env *env);

int	ft_env(char **envp)
{
	t_env	*env;
	t_env	*head;
	t_env	*last;
	t_env	*res;
	int		i;

	i = 0;
	head = NULL;
	last = NULL;
	while (envp && envp[i])
	{
		env = set_up_env(envp[i++]);
		if (!env)
			break ;
		if (!head)
			head = env;
		else
			last->next = env;
		last = env;
	}
	res = head;
	printf_env(res);
	free_env(res);
	return (0);
}

static t_env	*set_up_env(char *line)
{
	t_env	*env;
	size_t	len_name;
	char	*res;

	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	res = ft_strchr(line, '=');
	env->value = NULL;
	if (!res)
		env->name = ft_strdup(line);
	else
	{
		len_name = ft_strlen(line) - ft_strlen(res);
		env->name = malloc(len_name + 1);
		if (!env->name)
			env->name = NULL;
		else
		{
			ft_strlcpy(env->name, line, len_name + 1);
			env->value = ft_strdup(res + 1);
		}
	}
	env->next = NULL;
	return (env);
}

static void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		free(env->name);
		free(env->value);
		free(env);
		env = tmp;
	}
}

static void	printf_env(t_env *env)
{
	while (env)
	{
		if (env->value)
			printf("%s=%s\n", env->name, env->value);
		else
			printf("%s\n", env->name);
		env = env->next;
	}
}
