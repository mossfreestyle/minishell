/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwassim <rwassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 16:09:51 by rwassim           #+#    #+#             */
/*   Updated: 2025/04/28 14:50:23 by rwassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_mot(const char *s, char c)
{
	int		count;
	int		mot;
	size_t	i;

	count = 0;
	mot = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && mot == 0)
		{
			mot = 1;
			count++;
		}
		else if (s[i] == c)
			mot = 0;
		i++;
	}
	return (count);
}

static void	ft_tab(int *tab, const char *s, char c)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	len = 0;
	while (s[i])
	{
		if (i == 0 && s[i] != c)
			tab[j] = i;
		else if (i > 0 && s[i] != c && s[i - 1] == c)
			tab[j] = i;
		while (s[i] != c && s[i] != '\0')
		{
			i++;
			len++;
			tab[j + 1] = len;
		}
		len = 0;
		if (i != 0 && s[i] == c && s[i - 1] != c && s[i] != '\0')
			j += 2;
		if (s[i] != '\0')
			i++;
	}
}

static void	ft_free(char **strmalloc, int i, int *tab)
{
	if (strmalloc != NULL)
	{
		while (i >= 0)
		{
			if (strmalloc[i] != NULL)
				free(strmalloc[i]);
			i--;
		}
		free(strmalloc);
	}
	if (tab != NULL)
		free(tab);
}

static char	*ft_strsplit(const char *s, int start, int len)
{
	char	*str;
	int		i;

	i = 0;
	str = malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	while (i < len)
	{
		str[i] = s[start];
		i++;
		start++;
	}
	str[i] = '\0';
	return (str);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	int		*tab;
	char	**strmalloc;

	i = 0;
	j = 0;
	strmalloc = malloc(sizeof(char *) * (ft_mot(s, c) + 1));
	if (strmalloc == NULL)
		return (NULL);
	tab = malloc(sizeof(int) * (ft_mot(s, c) * 2));
	if (tab == NULL)
		return ((free(strmalloc)), NULL);
	ft_tab(tab, s, c);
	while (i < ft_mot(s, c))
	{
		strmalloc[i] = ft_strsplit(s, tab[j], tab[j + 1]);
		if (!strmalloc[i])
			return (ft_free(strmalloc, i - 1, tab), NULL);
		i++;
		j += 2;
	}
	strmalloc[i] = NULL;
	return (free(tab), strmalloc);
}

/*#include <stdio.h>
int	main(int argc, char **argv)
{
	int		i;
	char	**strs;

	if (argc == 3)
	{
		i = 0;
		strs = ft_split(argv[1], argv[2][0]);
		while (strs[i])
		{
			printf("strs[%d] = %s\n", i, strs[i]);
			free(strs[i]);
			i++;
		}
		free(strs);
	}
	return (0);
}*/
