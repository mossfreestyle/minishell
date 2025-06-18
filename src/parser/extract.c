/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwassim <rwassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:17:32 by rwassim           #+#    #+#             */
/*   Updated: 2025/06/18 09:48:21 by rwassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * extract_var - Extrait et remplace une variable d'environnement dans une ligne.
 * Gère aussi le cas spécial de $?.
 */
static char	*extract_var(char *line, int *i, t_shell *shell)
{
	char	*var_name;
	char	*var_value;
	int		start;

	(*i)++;
	if (line[*i] == '?')
	{
		(*i)++;
		return (ft_itoa(shell->exit_status));
	}
	start = *i;
	while (line[*i] && (ft_isalnum(line[*i]) || line[*i] == '_'))
		(*i)++;
	if (start == *i)
		return (ft_strdup("$"));
	var_name = ft_substr(line, start, *i - start);
	if (!var_name)
		return (NULL);
	var_value = getenv_lst(var_name, shell->env_vars);
	free(var_name);
	if (var_value)
		return (ft_strdup(var_value));
	else
		return (ft_strdup(""));
}

/**
 * expand_var - Ajoute la valeur d'une variable d'environnement à une chaîne.
 * Retourne la nouvelle chaîne ou NULL en cas d'erreur.
 */
char	*expand_var(char *line, int *i, t_shell *shell, char *value)
{
	char	*var_value;
	char	*new_value;

	var_value = extract_var(line, i, shell);
	if (!var_value)
		return (NULL);
	new_value = ft_strjoin(value, var_value);
	free(var_value);
	free(value);
	if (!new_value)
		return (NULL);
	return (new_value);
}

/**
 * get_unquoted - Extrait une portion de texte non-quotée et non-métacaractère.
 */
static char	*get_unquoted(char *line, int *i)
{
	int	start;

	start = *i;
	while (line[*i] && !ft_isspace(line[*i]) && !is_meta(line[*i])
		&& line[*i] != '\'' && line[*i] != '"' && line[*i] != '$')
		(*i)++;
	return (ft_substr(line, start, *i - start));
}

/**
 * extract_word - Extrait un mot complet (en gérant quotes et variables) depuis une ligne.
 * Retourne la chaîne extraite ou NULL en cas d'erreur.
 */
char	*extract_word(char *line, int *i, t_shell *shell)
{
	char	*value;
	char	*chunk;
	char	*tmp;

	value = ft_strdup("");
	while (line[*i] && !ft_isspace(line[*i]) && !is_meta(line[*i]))
	{
		chunk = NULL;
		if (line[*i] == '\'' || line[*i] == '"')
			chunk = quotes(line, i, shell);
		else if (line[*i] == '$')
			chunk = extract_var(line, i, shell);
		else
			chunk = get_unquoted(line, i);
		tmp = ft_strjoin(value, chunk);
		free(value);
		free(chunk);
		if (!tmp)
			return (NULL);
		value = tmp;
	}
	return (value);
}
