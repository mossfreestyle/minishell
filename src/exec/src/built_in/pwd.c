/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 11:46:45 by mfernand          #+#    #+#             */
/*   Updated: 2025/06/14 12:14:39 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

int	ft_pwd(void)
{
	char tab[PATH_MAX];

	if (getcwd(tab, sizeof(tab)) != NULL)
		printf("%s\n", tab);
	else
		perror("pwd");
	return (0);
}