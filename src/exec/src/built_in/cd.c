/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 22:31:43 by mfernand          #+#    #+#             */
/*   Updated: 2025/06/15 10:15:21 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"

static char	*get_env_value(t_env *env, const char *name);
static void	update_pwd(t_shell *shell, char *oldpwd);
// gerer cd -, cd ~, cd .., cd, cd /

int	ft_cd(char **args, t_shell *shell)
{
	char	*path;
	char	oldpwd[PATH_MAX];

	if (args[2])
		return (ft_putstr_fd("cd: too many arguments\n", 2), 1);
	getcwd(oldpwd, sizeof(oldpwd));
	if (!args[1][0] || !ft_strcmp(args[1], "~")
		|| !ft_strcmp(args[1], "--"))
	{
		path = get_env_value(shell->env_vars, "HOME");
		if (!path)
			return (ft_putstr_fd("cd: HOME not set\n", 2), 1);
	}
	else if (!ft_strcmp(args[1], "-"))
	{
		path = get_env_value(shell->env_vars, "OLDPWD");
		if (!path)
			return (ft_putstr_fd("cd: OLDPWD not set\n", 2), 1);
	}
	else
		path = args[1];
	if (!path || access(path, X_OK) || chdir(path))
		return (perror("cd"), 1);
	update_pwd(shell, oldpwd);
	if (!ft_strcmp(args[1], "-"))
		printf("%s\n", path);
	return (0);
}

static char	*get_env_value(t_env *env, const char *name)
{
	while (env)
	{
		if (!ft_strcmp(env->name, name))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

static void	update_pwd(t_shell *shell, char *oldpwd)
{
	set_env_value(shell->env_vars, "OLDPWD", shell->pwd);
	free(shell->pwd);
	shell->pwd = ft_strdup(getcwd(NULL, 0));
	set_env_value(shell->env_vars, "PWD", shell->pwd);
}