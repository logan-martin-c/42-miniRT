/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 19:49:09 by lomartin          #+#    #+#             */
/*   Updated: 2025/11/23 11:46:44 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** @brief Iterate a list and apply function f to each node's content
** @param lst Pointer to first element of list
** @param f Function to apply to each content
** @return void
*/
void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*elem;

	elem = lst;
	while (elem)
	{
		f(elem->content);
		elem = elem->next;
	}
}
