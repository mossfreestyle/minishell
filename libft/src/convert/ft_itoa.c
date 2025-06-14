/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwassim <rwassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 16:07:31 by rwassim           #+#    #+#             */
/*   Updated: 2025/04/28 13:23:54 by rwassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_countlen(long int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*ft_strcpy(char *dst, const char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

static char	*ft_pos(char *str, long int n)
{
	int	len;
	int	temp_len;

	len = ft_countlen(n);
	temp_len = len;
	str = malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	while (len > 0)
	{
		str[len - 1] = n % 10 + '0';
		n = n / 10;
		len--;
	}
	str[temp_len] = '\0';
	return (str);
}

static char	*ft_neg(char *str, long int n)
{
	int	len;
	int	temp_len;

	if (n == -2147483648)
	{
		str = malloc(sizeof(char) * 12);
		if (str == NULL)
			return (NULL);
		return (ft_strcpy(str, "-2147483648"), str);
	}
	n *= -1;
	len = ft_countlen(n);
	temp_len = len;
	str = malloc(sizeof(char) * (len + 2));
	if (str == NULL)
		return (NULL);
	str[0] = '-';
	while (len > 0)
	{
		str[len] = n % 10 + '0';
		n = n / 10;
		len--;
	}
	str[temp_len + 1] = '\0';
	return (str);
}

char	*ft_itoa(int n)
{
	char			*str;
	long long int	nb;

	nb = n;
	str = NULL;
	if (nb == 0)
	{
		str = malloc(sizeof(char) * 2);
		if (str == NULL)
			return (NULL);
		str[0] = '0';
		str[1] = '\0';
		return (str);
	}
	if (n < 0)
		str = ft_neg(str, nb);
	else
		str = ft_pos(str, nb);
	return (str);
}

/*#include <stdio.h>
int	main(int argc, char **argv)
{
	char	*str;

	if (argc == 2)
	{
		str = ft_itoa(atoi(argv[1]));
		printf("%s\n", str);
		free(str);
	}
	return (0);
}
valgrind --leak-check=full ./a.out 0 
cc -g -Wall -Wextra -Werror ft_itoa.c*/
