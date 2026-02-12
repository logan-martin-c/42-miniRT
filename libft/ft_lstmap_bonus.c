/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 13:20:05 by lomartin          #+#    #+#             */
/*   Updated: 2025/11/23 13:20:11 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** @brief Create a new list by applying function f to each element's content
** @param lst Pointer to first element of source list
** @param f Function to transform content
** @param del Function to free content on failure
** @return Pointer to new list or NULL on failure
*/
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*dest;
	t_list	*new;

	dest = NULL;
	if (!f || !del)
		return (NULL);
	while (lst)
	{
		new = ft_lstnew(f(lst->content));
		if (!new)
		{
			ft_lstclear(&dest, del);
			return (NULL);
		}
		ft_lstadd_back(&dest, new);
		lst = lst->next;
	}
	return (dest);
}
