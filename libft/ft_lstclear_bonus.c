/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 19:05:12 by lomartin          #+#    #+#             */
/*   Updated: 2025/12/09 13:08:17 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** @brief Delete and free all nodes from list starting at *lst using del
** @param lst Address of pointer to first node
** @param del Function used to free node content
** @return void (sets *lst to NULL)
*/
void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*elem;

	if (!lst)
		return ;
	while (*lst)
	{
		elem = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = elem;
	}
	*lst = NULL;
}
