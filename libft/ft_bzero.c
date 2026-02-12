/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 18:35:58 by lomartin          #+#    #+#             */
/*   Updated: 2025/12/11 17:37:11 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** @brief Zero (set to '\0') size bytes starting at area
** @param area Pointer to memory area
** @param size Number of bytes to zero
** @return void
*/
void	ft_bzero(void *area, size_t size)
{
	size_t			i;
	unsigned long	*l_area;

	i = 0;
	while (((unsigned long)area + i) % 64 && i < size)
		*((char *)area + i++) = 0;
	l_area = area + i;
	while (i < size - 8)
	{
		*(l_area++) = 0;
		i += 8;
	}
	while (i < size)
		*((char *)area + i++) = 0;
}
