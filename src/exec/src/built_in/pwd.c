/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 11:46:45 by mfernand          #+#    #+#             */
/*   Updated: 2025/06/18 22:12:05 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_shell *shell)
{
	char	tab[PATH_MAX];

	if (getcwd(tab, sizeof(tab)) != NULL)
	{
		free(shell->pwd);
		shell->pwd = ft_strdup(tab);
		printf("%s\n", shell->pwd);
		return (0);
	}
	else
		perror("minishell: pwd");
	return (1);
}
