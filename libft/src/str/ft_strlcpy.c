/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwassim <rwassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 16:11:20 by rwassim           #+#    #+#             */
/*   Updated: 2025/04/27 16:11:21 by rwassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size == 0)
		return (ft_strlen(src));
	while (src[i] != '\0' && i < size - 1)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (ft_strlen(src));
}

/*
#include <bsd/string.h>
#include <stdio.h>
int	main(int argc, char **argv)
{
	int	j;
	int	i;

	if (argc == 4)
	{
		j = strlcpy(argv[1], argv[2], atoi(argv[3]));
		i = ft_strlcpu(argv[1], atoi(argv[3]));
		printf("Real : %d\n", j);
		printf("Mienne : %d\n", i);
	}
	return (0);
}
*/
