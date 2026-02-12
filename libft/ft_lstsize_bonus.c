/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 18:47:39 by lomartin          #+#    #+#             */
/*   Updated: 2025/11/23 12:51:52 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** @brief Count number of nodes in list
** @param lst Pointer to first node
** @return Number of nodes (size_t or int depending on implementation)
*/
int	ft_lstsize(t_list *lst)
{
	size_t	size;

	size = 0;
	while (lst && ++size)
		lst = lst->next;
	return (size);
}
