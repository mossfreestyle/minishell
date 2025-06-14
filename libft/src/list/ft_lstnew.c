/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwassim <rwassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 16:08:02 by rwassim           #+#    #+#             */
/*   Updated: 2025/04/28 11:38:27 by rwassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (new == NULL)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}

/*#include <stdio.h>
int main()
{
    int valeur = 42;
    t_list *test = ft_lstnew(&valeur);

    if (test)
    {
        printf("Valeur : %d\n", *(int *)(test->content));
        printf("Adresse next : %p\n", (void *)test->next);
        free(test);
    }
    return (0);
}*/
