/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwassim <rwassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 16:07:57 by rwassim           #+#    #+#             */
/*   Updated: 2025/04/27 16:07:58 by rwassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	int	i;
	int	len;

	i = 0;
	len = ft_lstsize(lst);
	while (i < len - 1)
	{
		lst = lst->next;
		i++;
	}
	return (lst);
}

/*int main(void)
{
    t_list *head;
    t_list *node1;
    t_list *node2;
    t_list *node3;
    t_list *last;

    node1 = ft_lstnew("Premier");
    node2 = ft_lstnew("Deuxième");
    node3 = ft_lstnew("Troisième");

    head = node1;
    node1->next = node2;
    node2->next = node3;
    node3->next = NULL;

    last = ft_lstlast(head);
    if (last)
        printf("Dernier élément : %s\n", (char *)last->content);
    else
        printf("La liste est vide\n");

    return 0;
}*/
