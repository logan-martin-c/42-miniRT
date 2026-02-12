/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nblen_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 19:01:04 by lomartin          #+#    #+#             */
/*   Updated: 2025/11/23 19:16:54 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** @brief Counts the numbers needed to convert nb in given base
** @param nb Long int to process
** @param base String containing the base
** @return Length of the converted number, or 0 on error
*/
size_t	ft_nblen_base(long nb, char *base)
{
	size_t	baselen;
	size_t	len;

	if (nb == 0)
		return (1);
	if (!base || !ft_isvalidbase(base))
		return (0);
	baselen = ft_strlen(base);
	len = 0;
	if (nb < 0)
	{
		len++;
		nb = -nb;
	}
	while (nb)
	{
		len++;
		nb /= baselen;
	}
	return (len);
}
