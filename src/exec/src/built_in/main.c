/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 12:05:35 by mfernand          #+#    #+#             */
/*   Updated: 2025/06/14 22:33:26 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"

int main(int ac, char **av, char **envp)
{
    // t_shell info;
    (void)ac;
    (void)envp;
    // ft_pwd(&info);
    // ft_env(envp);
    // ft_echo(av);
    return ft_exit(av);
    // return (0);
}

//cc env.c main.c ../../../../include/minishell.h ../../../../libft/include/libft.h ../../../../libft/src/str/*.c




//cc exit.c main.c ../../../../include/minishell.h ../../../../libft/include/libft.h ../../../../libft/src/put/ft_putstr_fd.c ../../../../libft/src/convert/ft_atoi.c ../../../../libft/src/check/ft_isdigit.c

//mfernand@f4r10s15:~/c/minishell/src/exec/src/built_in$ exit | cat -e
// mfernand@f4r10s15:~/c/minishell/src/exec/src/built_in$ ./a.out | cat -e
// exit$
// mfernand@f4r10s15:~/c/minishell/src/exec/src/built_in$ 





//TODO
//cd, unset, export





// ../../../../libft/src/str/ft_split.c:13:10: fatal error: 'libft.h' file not found
// #include "libft.h"
//          ^~~~~~~~~
// 1 error generated.
// ../../../../libft/src/str/ft_strchr.c:13:10: fatal error: 'libft.h' file not found
// #include "libft.h"
//          ^~~~~~~~~
// 1 error generated.
// ../../../../libft/src/str/ft_strdup.c:13:10: fatal error: 'libft.h' file not found
// #include "libft.h"
//          ^~~~~~~~~
// 1 error generated.
// ../../../../libft/src/str/ft_striteri.c:13:10: fatal error: 'libft.h' file not found
// #include "libft.h"
//          ^~~~~~~~~
// 1 error generated.
// ../../../../libft/src/str/ft_strjoin.c:13:10: fatal error: 'libft.h' file not found
// #include "libft.h"
//          ^~~~~~~~~
// 1 error generated.
// ../../../../libft/src/str/ft_strlcat.c:13:10: fatal error: 'libft.h' file not found
// #include "libft.h"
//          ^~~~~~~~~
// 1 error generated.
// ../../../../libft/src/str/ft_strlcpy.c:13:10: fatal error: 'libft.h' file not found
// #include "libft.h"
//          ^~~~~~~~~
// 1 error generated.
// ../../../../libft/src/str/ft_strlen.c:13:10: fatal error: 'libft.h' file not found
// #include "libft.h"
//          ^~~~~~~~~
// 1 error generated.
// ../../../../libft/src/str/ft_strmapi.c:13:10: fatal error: 'libft.h' file not found
// #include "libft.h"
//          ^~~~~~~~~
// 1 error generated.
// ../../../../libft/src/str/ft_strncmp.c:13:10: fatal error: 'libft.h' file not found
// #include "libft.h"
//          ^~~~~~~~~
// 1 error generated.
// ../../../../libft/src/str/ft_strnstr.c:13:10: fatal error: 'libft.h' file not found
// #include "libft.h"
//          ^~~~~~~~~
// 1 error generated.
// ../../../../libft/src/str/ft_strrchr.c:13:10: fatal error: 'libft.h' file not found
// #include "libft.h"
//          ^~~~~~~~~
// 1 error generated.
// ../../../../libft/src/str/ft_strtrim.c:13:10: fatal error: 'libft.h' file not found
// #include "libft.h"
//          ^~~~~~~~~
// 1 error generated.
// ../../../../libft/src/str/ft_substr.c:13:10: fatal error: 'libft.h' file not found

//../../../../libft/src/check/ft_strcmp.c:13:10: fatal error: 'libft.h' file not found

//exit.c:(.text+0x6e): undefined reference to `ft_putstr_fd'

// /../../../libft/src/check/ft_isdigit.c:13:10: fatal error: 'libft.h' file not found