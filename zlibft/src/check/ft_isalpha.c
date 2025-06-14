/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwassim <rwassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 16:07:14 by rwassim           #+#    #+#             */
/*   Updated: 2025/04/27 16:07:15 by rwassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
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
		i = ft_isalpha(argv[1][0]);
		j = isalpha(argv[1][0]);
		printf("Mine : %d\nReal : %d\n", i, j);
	}
	return (0);
}
*/
