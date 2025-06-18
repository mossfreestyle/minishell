/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 12:05:35 by mfernand          #+#    #+#             */
/*   Updated: 2025/06/18 17:21:41 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"

// int	main(int ac, char **av, char **envp)
// {
// 	t_shell	info;

// 	(void)ac;
// 	(void)envp;
// 	// info.env_vars = init env()//
// 	// ft_pwd(&info);
// 	// ft_env(envp);
// 	// ft_cd(av, &info);
// 	ft_echo(av);
// 	// return (ft_exit(av));
// 	// return (0);
// }

// return exit status dans la struct

t_env	*init_env(char **envp)
{
	t_env	*head;
	t_env	*last;
	t_env	*node;
	int		i;
	char	*eq;

	head = NULL;
	last = NULL;
	i = -1;
	while (envp && envp[++i])
	{
		eq = ft_strchr(envp[i], '=');
		node = malloc(sizeof(t_env));
		if (!node)
			return (NULL);
		node->name = ft_substr(envp[i], 0, eq - envp[i]);
		node->value = ft_strdup(eq + 1);
		node->next = NULL;
		if (!head)
			head = node;
		else
			last->next = node;
		last = node;
	}
	return (head);
}
