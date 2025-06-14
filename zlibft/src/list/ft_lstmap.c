/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwassim <rwassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 16:07:59 by rwassim           #+#    #+#             */
/*   Updated: 2025/04/28 10:23:35 by rwassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlist;
	t_list	*new;
	void	*content;

	if (!lst || !f || !del)
		return (NULL);
	newlist = NULL;
	while (lst)
	{
		content = (f(lst->content));
		new = ft_lstnew(content);
		if (new == NULL)
		{
			ft_lstclear(&newlist, del);
			del(content);
			return (NULL);
		}
		ft_lstadd_back(&newlist, new);
		lst = lst->next;
	}
	return (newlist);
}
