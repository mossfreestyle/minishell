/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwassim <rwassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 10:26:06 by rwassim           #+#    #+#             */
/*   Updated: 2025/06/18 15:26:40 by rwassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	t_shell	shell;
	t_token	*tokens;
	char	*input;
	t_token	*tmp;

	shell.exit_status = 0;
	shell.pwd = NULL;
	shell.env_vars = NULL; // À remplir si besoin
	// (void)ac;
	while (1)
	{
		input = readline("\001\033[1;34m\002minishell$ \001\033[0m\002");
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
		tokens = lexer(input, &shell);
		if (tokens)
		{
			tmp = tokens;
			while (tmp)
			{
				// exec_built_in(av, &shell);
				printf("Token: type=%d, content=%s\n", tmp->type, tmp->content);
				tmp = tmp->next;
			}
			free_tokens(tokens);
		}
		free(input);
	}
	return (shell.exit_status);
}
