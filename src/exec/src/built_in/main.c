/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 12:05:35 by mfernand          #+#    #+#             */
/*   Updated: 2025/06/15 11:23:32 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"

int main(int ac, char **av, char **envp)
{
    t_shell info;
    (void)ac;
    (void)envp;
    // ft_pwd(&info);
    // ft_env(envp);
    ft_cd(av, &info);
    // ft_echo(av);
    // return ft_exit(av);
    // return (0);
}

//TODO
//cd, unset, export
