/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ptr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwassim <rwassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 10:30:46 by rwassim           #+#    #+#             */
/*   Updated: 2025/05/15 11:19:01 by rwassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_ptr(unsigned long nb)
{
	int	len;

	len = 0;
	if (nb >= 16)
		len += ft_ptr(nb / 16);
	if (nb % 16 <= 9)
		len += ft_putchar ((nb % 16) + '0');
	else
		len += ft_putchar((nb % 16) + 87);
	return (len);
}
