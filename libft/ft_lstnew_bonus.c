/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 18:40:19 by lomartin          #+#    #+#             */
/*   Updated: 2025/11/23 11:46:51 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** @brief Create a new list node with given content
** @param content pointer to node content
** @return Pointer to newly allocated t_list node or NULL on allocation failure
*/
t_list	*ft_lstnew(void *content)
{
	t_list	*elem;

	elem = malloc(sizeof(t_list));
	if (!elem)
		return (NULL);
	elem->content = content;
	elem->next = NULL;
	return (elem);
}
