/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 18:51:47 by lomartin          #+#    #+#             */
/*   Updated: 2025/11/23 12:57:12 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** @brief Add node 'new' at the end of list 'lst'
** @param lst Address of pointer to first element of list
** @param new New node to append
** @return void
*/
void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (!lst || !new)
		return ;
	last = *lst;
	if (!(*lst))
		*lst = new;
	else
	{
		while (last->next)
			last = last->next;
		last->next = new;
	}
	return ;
}
