/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 11:54:01 by mfernand          #+#    #+#             */
/*   Updated: 2025/06/14 12:25:45 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H

# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef PATH_MAX
#  define PATH_MAX 4096
/*4096 est une valeur courante utilisée comme taille maximale pour un chemin absolu sur la plupart des systèmes UNIX/Linux.*/
# endif

int	ft_pwd(void);
int	ft_env(char **envp);

#endif