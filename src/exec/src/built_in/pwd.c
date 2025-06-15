/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 11:46:45 by mfernand          #+#    #+#             */
/*   Updated: 2025/06/15 10:55:11 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_shell *info)
{
	char	tab[PATH_MAX];

	if (getcwd(tab, sizeof(tab)) != NULL)
	{
		free(info->pwd);
		info->pwd = ft_strdup(tab);
		printf("%s\n", info->pwd);
	}
	else
		perror("pwd");
	return (0);
}
