/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 18:57:46 by lomartin          #+#    #+#             */
/*   Updated: 2025/11/23 12:53:02 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** @brief Copy bytes from src to dest until character c is found (or n bytes)
** @param dst Destination buffer
** @param src Source buffer
** @param c Character to stop at (as unsigned char)
** @param n Maximum bytes to copy
** @return Pointer to next char in dst after c, or NULL if c not found
*/
void	*ft_memccpy(void *dest, const void *src, char c, size_t n)
{
	int		i;
	char	*srccpy;
	char	*destcpy;

	srccpy = (void *)src;
	destcpy = dest;
	i = -1;
	while (n - ++i && srccpy[i] != c)
		destcpy[i] = srccpy[i];
	if (srccpy[i] == c)
	{
		destcpy[i] = c;
		return (destcpy + i + 1);
	}
	return (0);
}
