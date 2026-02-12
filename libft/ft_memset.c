/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 18:09:37 by lomartin          #+#    #+#             */
/*   Updated: 2025/12/09 11:08:35 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** @brief Fill memory area with a constant byte c for n bytes
** @param area Pointer to memory
** @param c Byte value to set (int, converted to unsigned char)
** @param n Number of bytes to set
** @return Pointer to memory area
*/
void	*ft_memset(void *area, int c, size_t n)
{
	int		i;
	char	*dest;

	dest = area;
	i = 0;
	while (n - i)
		dest[i++] = c;
	return (dest);
}
