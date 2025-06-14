/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwassim <rwassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 16:05:59 by rwassim           #+#    #+#             */
/*   Updated: 2025/04/27 16:06:00 by rwassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t len)
{
	ft_memset(s, 0, len);
}

/*
#include <strings.h>
#include <stdio.h>
int	main(void)
{
	char	tab[5] = {'1', '2', '3', '4', '5'};
	char	tab2[5] = {'1', '2', '3', '4', '5'};
	int	i;

	i = 0;
	ft_bzero(tab, 5);
	bzero(tab2, 5);
	printf("Mine : ");
	while (i <= 4)
	{
		printf("%i", tab[i]);
		i++;
	}
	i = 0;
	printf("\nReal : ");
	while (i <= 4)
	{
		printf("%i", tab2[i]);
		i++;
	}
	printf("\n");
}
*/
