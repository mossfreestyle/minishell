/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwassim <rwassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 16:11:10 by rwassim           #+#    #+#             */
/*   Updated: 2025/04/27 16:11:11 by rwassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	int		i;
	int		j;
	char	*strmalloc;
	int		len;

	i = 0;
	j = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	strmalloc = malloc(sizeof(char) * (len + 1));
	if (strmalloc == NULL)
		return (NULL);
	while (s1[i])
	{
		strmalloc[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		strmalloc[i + j] = s2[j];
		j++;
	}
	strmalloc[i + j] = '\0';
	return (strmalloc);
}

/*
#include <stdio.h>
int	main(int argc, char **argv)
{
	char	*str;

	if (argc == 3)
	{
		str = ft_strjoin(argv[1], argv[2]);
		printf("%s", str);
	}
	return (0);
}
*/
