/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwassim <rwassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 10:26:06 by rwassim           #+#    #+#             */
/*   Updated: 2025/06/14 14:44:46 by rwassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
    char	*input;
    t_token	*tokens;

    while (1)
    {
        input = readline("minishell> ");
        if (!input)
        {
            printf("exit\n");
            break ;
        }
        if (*input == '\0')
        {
            free(input);
            continue ;
        }
        add_history(input);
        
        if (ft_strcmp(input, "exit") == 0)
        {
            free(input);
            break ;
        }
        tokens = new_token(WORD, input);
        if (tokens)
        {
            printf("Token créé: type=%d, content='%s'\n", tokens->type, tokens->content);
            free_tokens(tokens);
        }
        free(input);
    }
    return (0);
}
