/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwassim <rwassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 11:23:51 by mfernand          #+#    #+#             */
/*   Updated: 2025/06/24 11:43:28 by rwassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_err(char *cmd, char *arg, char *msg, int err_num)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	if (arg)
	{
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(msg, 2);
	return (err_num);
}

void	*set_status(t_shell *shell, int status)
{
	shell->exit_status = status;
	return (NULL);
}

void	*err_msg(char *cmd, char *msg, t_shell *shell, int exit_status)
{
	ft_putstr_fd("minishell: ", 2);
	if (cmd)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(msg, 2);
	return (set_status(shell, exit_status));
}

int	exec_error(char *cmd)
{
	if (errno == EACCES)
		return (cmd_err(cmd, NULL, "Permission denied", 126));
	else if (errno == ENOENT)
		return (cmd_err(cmd, NULL, "No such file or directory", 127));
	else if (errno == ENOTDIR)
		return (cmd_err(cmd, NULL, "Not a directory", 127));
	else
		return (cmd_err(cmd, NULL, strerror(errno), 1));
}
