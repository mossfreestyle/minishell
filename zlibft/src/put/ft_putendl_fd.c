/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwassim <rwassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 16:09:42 by rwassim           #+#    #+#             */
/*   Updated: 2025/04/27 16:09:43 by rwassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	if (s != NULL)
	{
		ft_putstr_fd(s, fd);
		ft_putchar_fd('\n', fd);
	}
}

/*
int	main(int argc, char **argv)
{
	if (argc == 3)
	{
		ft_putendl_fd(argv[1], atoi(argv[2]));
	}
	return (0);
}
*/
