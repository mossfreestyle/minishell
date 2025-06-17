/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwassim <rwassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 22:31:47 by mfernand          #+#    #+#             */
/*   Updated: 2025/06/17 16:51:37 by rwassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	print_unset_error(const char *name)
{
	ft_putstr_fd("minishell: unset: `", 2);
	ft_putstr_fd(name, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (1);
}
