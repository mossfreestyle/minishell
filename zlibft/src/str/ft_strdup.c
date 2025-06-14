/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwassim <rwassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 16:10:34 by rwassim           #+#    #+#             */
/*   Updated: 2025/04/27 16:10:50 by rwassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*dup;
	int		size;
	int		i;

	i = 0;
	size = 0;
	while (s[size])
		size++;
	dup = (char *)malloc(sizeof(char) * (size + 1));
	if (dup == NULL)
		return (NULL);
	while (s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

/*
#include <stdio.h>
#include <string.h>
int	main(int argc, char **argv)
{
	char	*i;
	char	*j;

	if (argc == 2)
	{
		i = ft_strdup(argv[1]);
		j = strdup(argv[1]);
		printf("Mine : %s\nReal : %s\n", i, j);
	}
	return (0);
}
*/
