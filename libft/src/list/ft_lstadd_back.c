/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwassim <rwassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 16:07:39 by rwassim           #+#    #+#             */
/*   Updated: 2025/04/27 16:07:40 by rwassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	temp = ft_lstlast(*lst);
	temp->next = new;
}

/*int main(void)
{
    t_list *head;
    t_list *node1;
    t_list *node2;
    t_list *node3;
    t_list *new_node;
    t_list *temp;

    node1 = ft_lstnew("Premier");
    node2 = ft_lstnew("Deuxième");
    node3 = ft_lstnew("Troisième");

    head = node1;
    node1->next = node2;
    node2->next = node3;
    node3->next = NULL;

    new_node = ft_lstnew("Dernier");

    ft_lstadd_back(&head, new_node);

    temp = head;
    while (temp)
    {
        printf("%s\n", (char *)temp->content);
        temp = temp->next;
    }

    return (0);
}*/
