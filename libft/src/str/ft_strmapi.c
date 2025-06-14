/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwassim <rwassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 16:11:29 by rwassim           #+#    #+#             */
/*   Updated: 2025/04/27 16:11:30 by rwassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	int				len;
	char			*strmalloc;

	i = 0;
	len = 0;
	while (s[len])
		len++;
	strmalloc = malloc(sizeof(char) * (len + 1));
	if (strmalloc == NULL)
		return (NULL);
	while (s[i])
	{
		strmalloc[i] = f(i, s[i]);
		i++;
	}
	strmalloc[i] = '\0';
	return (strmalloc);
}

/*
#include <stdio.h>
char	f(unsigned int, char c)
{
	char	str;

	str = c - 32;
	return (str);
}
int	main(int argc, char **argv)
{
	char	*str2;

	if (argc == 2)
	{
		str2 = ft_strmapi(argv[1], *f);
		printf("%s\n", str2);
	}
	return (0);
}
*/
