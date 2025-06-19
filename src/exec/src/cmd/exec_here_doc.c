/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_here_doc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 11:14:03 by mfernand          #+#    #+#             */
/*   Updated: 2025/06/19 11:26:19 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_here_doc(char *name)
{
    if (!name)
		return (0);
    return (!ft_strcmp(name, "<<"));
}
int exec_here_doc(t_shell *shell)
{
    
}