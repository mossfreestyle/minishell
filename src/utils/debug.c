/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 09:57:30 by rwassim           #+#    #+#             */
/*   Updated: 2025/06/23 10:06:26 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

const char	*redirect_type_to_string(t_token_type type)
{
	switch (type)
	{
	case R_INPUT:
		return ("Input (<)");
	case R_OUTPUT:
		return ("Output (>)");
	case R_APPEND:
		return ("Append (>>)");
	case R_HEREDOC:
		return ("Heredoc (<<)");
	default:
		return ("Unknown");
	}
}

void	print_command(t_command *cmd)
{
	int i;
	if (!cmd)
	{
		printf("Command is NULL\n");
		return ;
	}
	printf("Command name: %s\n", cmd->name ? cmd->name : "NULL");
	printf("Argument:\n")
}