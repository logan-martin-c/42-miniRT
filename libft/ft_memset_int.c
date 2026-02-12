/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset_int.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 11:09:22 by lomartin          #+#    #+#             */
/*   Updated: 2025/12/09 22:17:48 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset_int(void *area, int c, size_t n)
{
	size_t	i;
	int		*dest;

	if (n % sizeof(int) && (unsigned long)area % sizeof(int))
		return (NULL);
	dest = area;
	i = 0;
	while (i * sizeof(int) < n)
		dest[i++] = c;
	return (dest);
}
