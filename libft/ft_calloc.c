/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 08:54:38 by lomartin          #+#    #+#             */
/*   Updated: 2025/11/23 13:15:26 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** @brief Allocate and zero-initialize memory for count elements of size bytes
** @param count number of elements
** @param size size of each element in bytes
** @return Pointer to allocated memory or NULL on failure
*/
void	*ft_calloc(size_t n, size_t size)
{
	char	*area;
	size_t	len;

	len = n * size;
	if (len && (len < n || len < size))
		return (NULL);
	area = malloc(len);
	if (!area)
		return (NULL);
	ft_bzero(area, len);
	return (area);
}

/*#include <stdio.h>

int	main(int argc, char const *argv[])
{
	printf("%p\n", ft_calloc(-5, -5));
	printf("%p\n", calloc(-5, -5));
	return (0);
}*/
