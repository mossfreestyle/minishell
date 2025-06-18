/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwassim <rwassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 13:51:39 by rwassim           #+#    #+#             */
/*   Updated: 2025/06/18 09:50:47 by rwassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

long	ft_atol(char *str, int *out_of_range)
{
	long	res;
	long	sign;

	*out_of_range = 0;
	res = 0;
	sign = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		if ((res > (LONG_MAX / 10)) || (res == (LONG_MAX / 10) && (*str
					- '0') > (LONG_MAX % 10)))
		{
			*out_of_range = 1;
			return (0);
		}
		res = res * 10 + (*str - '0');
		str++;
	}
	return (res * sign);
}

/**
 * append_to_array - Ajoute une nouvelle chaîne à un tableau de chaînes (char **).
 * Alloue un nouveau tableau, copie les anciennes valeurs, ajoute la nouvelle, puis libère l'ancien tableau.
 */
char	**append_to_array(char **array, const char *new_elem)
{
	int		i;
	int		size;
	char	**new_array;

	size = 0;
	while (array && array[size])
		size++;
	new_array = malloc(sizeof(char *) * (size + 2));
	if (!new_array)
		return (NULL);
	i = 0;
	while (array && array[i])
	{
		new_array[i] = ft_strdup(array[i]);
		if (!new_array[i])
		{
			free_array(new_array);
			return (NULL);
		}
		i++;
	}
	new_array[i] = ft_strdup(new_elem);
	new_array[i + 1] = NULL;
	free_array(array);
	return (new_array);
}

/**
 * ft_strjoin_char - Crée une nouvelle chaîne en ajoutant un caractère à la fin d'une chaîne existante.
 */
char	*ft_strjoin_char(char *str, char c)
{
	size_t	len;
	char	*new_str;

	len = ft_strlen(str);
	new_str = malloc(len + 2);
	if (!new_str)
		return (NULL);
	ft_memcpy(new_str, str, len);
	new_str[len] = c;
	new_str[len + 1] = '\0';
	return (new_str);
}

/**
 * add_char - Ajoute le caractère courant de la ligne à la valeur, avance l'index.
 * Retourne la nouvelle chaîne ou NULL en cas d'erreur d'allocation.
 */
char	*add_char(char *line, int *i, char *value)
{
	char	*new_value;

	new_value = ft_strjoin_char(value, line[*i]);
	if (!new_value)
	{
		free(value);
		return (NULL);
	}
	free(value);
	(*i)++;
	return (new_value);
}

/**
 * is_empty_line - Vérifie si une ligne ne contient que des espaces (ligne vide).
 * Retourne true si la ligne est vide, false sinon.
 */
bool	is_empty_line(const char *line)
{
	while (*line)
	{
		if (!ft_isspace(*line))
			return (false);
		line++;
	}
	return (true);
}
