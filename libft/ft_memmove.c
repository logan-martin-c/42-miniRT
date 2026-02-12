/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 19:10:18 by lomartin          #+#    #+#             */
/*   Updated: 2025/11/23 11:54:28 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** @brief Copy n bytes from src to dest handling overlapping regions
** @param dest Destination memory area
** @param src Source memory area
** @param n Number of bytes to copy
** @return Pointer to dst
*/
void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*srccpy;
	char	*destcpy;

	if (!dest && !src)
		return (NULL);
	srccpy = (char *)src;
	destcpy = dest;
	if (dest - src > 0)
	{
		while (n--)
			destcpy[n] = srccpy[n];
	}
	else
	{
		while (n--)
			*(destcpy++) = *(srccpy++);
	}
	return (dest);
}
