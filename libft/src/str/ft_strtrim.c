/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwassim <rwassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 16:11:46 by rwassim           #+#    #+#             */
/*   Updated: 2025/04/27 16:11:47 by rwassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_set(char c, const char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	int		len;
	int		start;
	int		end;
	char	*strmalloc;

	if (!s1 || !set)
		return (NULL);
	len = ft_strlen(s1);
	start = 0;
	end = len - 1;
	while (start < len && is_set(s1[start], set) == 1)
		start++;
	if (start == len)
		return (ft_strdup(""));
	while (end > start && is_set(s1[end], set) == 1)
		end--;
	strmalloc = ft_substr(s1, start, end - start + 1);
	return (strmalloc);
}

/*
#include <stdio.h>
int	main(int argc, char **argv)
{
	char	*i;

	if (argc == 3)
	{
		i = ft_strtrim(argv[1], argv[2]);
		printf("%s\n", i);
	}
	return (0);
}
*/
