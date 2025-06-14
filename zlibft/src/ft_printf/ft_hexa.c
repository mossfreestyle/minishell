/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwassim <rwassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 09:58:00 by rwassim           #+#    #+#             */
/*   Updated: 2025/05/15 11:18:44 by rwassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_hexa(unsigned int nb, char c)
{
	int	len;

	len = 0;
	if (nb >= 16)
		len += ft_hexa(nb / 16, c);
	if (nb % 16 <= 9)
		len += ft_putchar((nb % 16) + '0');
	else
	{
		if (c == 'X')
			len += ft_putchar((nb % 16) + 55);
		else
			len += ft_putchar((nb % 16) + 87);
	}
	return (len);
}
