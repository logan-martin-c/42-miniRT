/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 23:10:46 by lomartin          #+#    #+#             */
/*   Updated: 2026/03/08 23:10:51 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

///@brief Reallocates a new bigger memory block. Since it's a fake realloc,
/// the memory is only copied from the old bloc to the new one. The old bloc is
/// freed.
///@param src Old bloc. If NULL, the call is equivalent to calloc(new_size).
///@param old_size Old bloc size.
///@param new_size Size to allocate. If it is larger than *old_size*, the added
/// memory is initialized to NULL. If it is smaller than *old_size*, then the
/// old bloc is truncated. If it is 0, then the call is equivalent to free(src)
///@return Pointer to the new allocated memory bloc or NULL on failure
void	*ft_realloc(void *src, size_t old_size, size_t new_size)
{
	void	*dest;

	dest = ft_calloc(1, new_size);
	if (!dest)
		return (NULL);
	ft_memcpy(dest, src, ft_min(new_size, old_size));
	free(src);
	return (dest);
}
