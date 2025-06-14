/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwassim <rwassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 16:11:36 by rwassim           #+#    #+#             */
/*   Updated: 2025/04/27 16:12:49 by rwassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (little[i] == '\0')
		return ((char *)big);
	while (big[i] && i < len)
	{
		j = 0;
		while (big[i + j] == little[j] && little[j] != '\0' && (i + j) < len)
		{
			j++;
			if (little[j] == '\0')
				return ((char *)&big[i]);
		}
		i++;
	}
	return (NULL);
}

/*int main(int argc, char **argv)
{
    if (argc == 4)
	{
		const char *big = argv[1];
    	const char *little = argv[2];
    	size_t len = atoi(argv[3]);

    	char *result = ft_strnstr(big, little, len);

    	if (result)
        	printf("Sous-chaîne trouvée : \"%s\"\n", result);
		else
        	printf("Sous-chaîne non trouvée\n");
	}
    return (0);
}*/
