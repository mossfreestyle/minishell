/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwassim <rwassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 16:07:44 by rwassim           #+#    #+#             */
/*   Updated: 2025/04/27 16:07:45 by rwassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		ft_lstdelone(*lst, *del);
		*lst = temp;
	}
	*lst = NULL;
}

/*int main()
{
	t_list *list;
	void	del_content(void *content)
{
	free(content);
	printf("Contenu supprimé !\n");
}
    list = ft_lstnew(strdup("Premier"));
    list->next = ft_lstnew(strdup("Deuxième"));
    list->next->next = ft_lstnew(strdup("Troisième"));

    printf("Avant ft_lstclear :\n");
    t_list *tmp = list;
    while (tmp)
    {
        printf("- %s\n", (char *)tmp->content);
        tmp = tmp->next;
    }

    ft_lstclear(&list, del_content);

    if (list == NULL)
        printf("Liste complètement supprimée !\n");

    return 0;
}*/
