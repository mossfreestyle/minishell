/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 22:31:43 by mfernand          #+#    #+#             */
/*   Updated: 2025/06/25 22:28:59 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"

static char	*get_env_value(t_env *env, const char *name);
static int	update_pwd(t_shell *shell, char *oldpwd, char **args);
static void	set_env_value(t_env **env, const char *name, const char *value);
static void	printf_error(char *name);

int	ft_cd(char **args, t_shell *shell)
{
	char	*path;
	char	oldpwd[PATH_MAX];

	if (!getcwd(oldpwd, sizeof(oldpwd)))
		oldpwd[0] = '\0';
	if (args[1] && args[2])
		return (ft_putstr_fd("minishell: cd: too many arguments\n", 2), 1);
	if (!args[1] || !args[1][0] || !ft_strcmp(args[1], "~")
		|| !ft_strcmp(args[1], "--"))
	{
		path = get_env_value(shell->env_vars, "HOME");
		if (!path)
			return (ft_putstr_fd("minishell: cd: HOME not set\n", 2), 1);
	}
	else if (!ft_strcmp(args[1], "-"))
	{
		path = get_env_value(shell->env_vars, "OLDPWD");
		if (!path)
			return (ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2), 1);
	}
	else
		path = args[1];
	if (!path || access(path, X_OK) || chdir(path))
		return (printf_error(path), 1);
	return (update_pwd(shell, oldpwd, args));
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

static int	update_pwd(t_shell *shell, char *oldpwd, char **args)
{
	char	*newpwd;

	set_env_value(&shell->env_vars, "OLDPWD", oldpwd);
	newpwd = getcwd(NULL, 0);
	if (newpwd)
	{
		free(shell->pwd);
		shell->pwd = ft_strdup(newpwd);
		set_env_value(&shell->env_vars, "PWD", newpwd);
		free(newpwd);
		if (args[1] && !ft_strcmp(args[1], "-"))
			printf("%s\n", shell->pwd);
		return (0);
	}
	else
		return (ft_putstr_fd("minishell: cd: ..: No such file or directory\n",
				2), 1);
}

static void	set_env_value(t_env **env, const char *name, const char *value)
{
	t_env	*new;
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, name))
		{
			free(tmp->value);
			tmp->value = ft_strdup(value);
			return ;
		}
		if (!tmp->next)
			break ;
		tmp = tmp->next;
	}
	new = malloc(sizeof(t_env));
	if (!new)
		return ;
	*new = (t_env){.name = ft_strdup(name), .value = ft_strdup(value),
		.next = NULL};
	if (!*env)
		*env = new;
	else
		tmp->next = new;
}

static void	printf_error(char *name)
{
	struct stat	st;

	ft_putstr_fd("minishell: cd: ", 2);
	if (name && name[0])
		ft_putstr_fd(name, 2);
	else
		ft_putstr_fd("unknown", 2);
	if (!name || stat(name, &st) == -1)
		ft_putstr_fd(": No such file or directory\n", 2);
	else if (!S_ISDIR(st.st_mode))
		ft_putstr_fd(": Not a directory\n", 2);
	else
		ft_putstr_fd(": Permission denied\n", 2);
}

/*
	Test :

	mkdir a
$> mkdir a/b
$> cd a/b
$> rm -r ../../a
$> cd ..

	Message attendu : chdir: error retrieving current directory:
	getcwd: cannot access parent directories: No such file or directory

a fix mais normalement bon



*/