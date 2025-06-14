/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwassim <rwassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 16:06:06 by rwassim           #+#    #+#             */
/*   Updated: 2025/04/27 16:07:00 by rwassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*tab;

	if (size != 0 && nmemb > 4294967295 / size)
		return (NULL);
	tab = (void *)malloc(size * nmemb);
	if (tab == NULL)
		return (NULL);
	ft_bzero(tab, size * nmemb);
	return (tab);
}

/*
#include <stdio.h>
int	main(void)
{
	int	*tab;
	tab = ft_calloc(0, 0);
	free(tab);
}
*/
