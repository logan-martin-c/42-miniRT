/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 18:43:44 by lomartin          #+#    #+#             */
/*   Updated: 2025/11/23 12:50:53 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** @brief Copy n bytes from src to dest (behavior undefined if areas overlap)
** @param dst Destination memory area
** @param src Source memory area
** @param n Number of bytes to copy
** @return Pointer to dest
*/
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	int		i;
	char	*srccpy;
	char	*destcpy;

	if (!dest && !src)
		return (NULL);
	srccpy = (void *)src;
	destcpy = dest;
	i = -1;
	while (n - ++i)
		destcpy[i] = srccpy[i];
	return (dest);
}
