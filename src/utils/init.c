/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwassim <rwassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 10:30:43 by rwassim           #+#    #+#             */
/*   Updated: 2025/06/27 14:37:24 by rwassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_args(int ac, char **av, char **envp)
{
	(void)av;
	if (ac != 1)
		ft_putendl_fd("minishell: warning: argument ignored", 2);
	if (!envp || !*envp)
	{
		ft_putstr_fd("minishell: warning: ", 2);
		ft_putendl_fd("no environment variable set", 2);
	}
}

static char	*init_pwd(t_env **env_vars)
{
	char	*pwd;
	char	*cwd;

	pwd = getenv_lst("PWD", *env_vars);
	if (!pwd)
	{
		cwd = getcwd(NULL, 0);
		if (!cwd)
			return (ft_strdup("."));
		setenv_lst("PWD", cwd, env_vars);
		pwd = ft_strdup(cwd);
		free(cwd);
	}
	else
		pwd = ft_strdup(pwd);
	return (pwd);
}

static void	init__shlvl(t_env **env_vars)
{
	char	*shlvl_str;
	char	*new_shlvl;
	int		shlvl;

	shlvl = 0;
	shlvl_str = getenv_lst("SHLVL", *env_vars);
	if (shlvl_str)
		shlvl = ft_atoi(shlvl_str);
	if (shlvl < 0)
		shlvl = 0;
	else
		shlvl++;
	new_shlvl = ft_itoa(shlvl);
	setenv_lst("SHLVL", new_shlvl, env_vars);
	free(new_shlvl);
}

t_shell	*init_shell(int ac, char **av, char **envp)
{
	t_shell	*shell;

	check_args(ac, av, envp);
	shell = malloc(sizeof(t_shell));
	if (!shell)
		return (NULL);
	shell->exit_status = 0;
	shell->env_vars = init_env(envp);
	shell->pwd = init_pwd(&shell->env_vars);
	shell->av = av;
	shell->cmd_list = NULL;
	shell->saved_stdin = -1;
	shell->saved_stdout = -1;
	init_pipes(shell);
	init__shlvl(&shell->env_vars);
	return (shell);
}

void	check_exit(t_shell *shell, t_command *cmd, int saved_stdout,
		int saved_stdin)
{
	int	exit_code;

	if (handle_redirections(cmd, shell) != -1)
	{
		exit_code = ft_exit(cmd->args, shell);
		if (exit_code != 1000)
		{
			close(saved_stdout);
			close(saved_stdin);
			free_shell(shell);
			exit(exit_code);
		}
	}
	shell->exit_status = 1;
}
