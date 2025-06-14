/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwassim <rwassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 16:11:49 by rwassim           #+#    #+#             */
/*   Updated: 2025/04/27 16:11:50 by rwassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*strmalloc;

	i = 0;
	if (start >= ft_strlen(s))
	{
		strmalloc = malloc(sizeof(char) * 1);
		if (strmalloc == NULL)
			return (NULL);
		strmalloc[0] = '\0';
		return (strmalloc);
	}
	if (len > ft_strlen(&s[start]))
		len = ft_strlen(&s[start]);
	strmalloc = malloc(sizeof(char) * (len + 1));
	if (strmalloc == NULL)
		return (NULL);
	while (i < len)
	{
		strmalloc[i] = s[start];
		i++;
		start++;
	}
	strmalloc[i] = '\0';
	return (strmalloc);
}

/*
#include <stdio.h>
int	main(int argc, char **argv)
{
	char	*i;

	if (argc == 4)
	{
		i = ft_substr(argv[1], atoi(argv[2]), atoi(argv[3]));
		printf("%s\n", i);
	}
	return (0);
}
*/
