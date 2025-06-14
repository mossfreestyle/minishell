/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwassim <rwassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 16:07:21 by rwassim           #+#    #+#             */
/*   Updated: 2025/04/27 16:07:22 by rwassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
/*
#include <ctype.h>
#include <stdio.h>
int	main(int argc, char **argv)
{
	int	i;
	int	j;

	if (argc == 2)
	{
		i = ft_isdigit(argv[1][0]);
		j = isdigit(argv[1][0]);
		printf("Mine : %d\nReal : %d\n", i, j);
	}
	return (0);
}
*/
