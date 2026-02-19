/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_min.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 19:44:23 by lomartin          #+#    #+#             */
/*   Updated: 2025/12/03 21:53:02 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** @brief Returns the lowest value between count longs
** @param count Count of long to expect
** @return Lowest between all given values
*/
long	ft_min(long a, long b)
{
	if (a < b)
		return (a);
	return (b);
}

float	ft_min_float(float a, float b)
{
	if (a < b)
		return (a);
	return (b);
}
