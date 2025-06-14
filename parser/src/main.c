/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwassim <rwassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 10:26:06 by rwassim           #+#    #+#             */
/*   Updated: 2025/06/13 11:57:30 by rwassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(void)
{
	char *input;
	t_token *tokens;

	while (1)
	{
		input = readline("minishell>");
		if (!input)
			break ;
		if (*input)
			add_history(input);
		tokens = tokenize(input);
		print_tokens(tokens);

		free_token(tokens);
		free(input);
	}
	printf("exit\n");
	return (0);
}