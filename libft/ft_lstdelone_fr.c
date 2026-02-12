/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_fr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 11:05:55 by lomartin          #+#    #+#             */
/*   Updated: 2025/11/28 22:40:54 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone_fr(t_list **lst, t_list *elem, void (*del)(void *))
{
	t_list	*check;

	if (!*lst || !elem || !del)
		return ;
	check = *lst;
	if (check != elem)
	{
		while ((check)->next != elem)
			check = check->next;
		check->next = elem->next;
	}
	else if (!elem->next)
		*lst = NULL;
	else
		*lst = elem->next;
	del(elem->content);
	elem->content = NULL;
	free(elem);
}
