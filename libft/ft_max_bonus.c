/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_max_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 19:41:34 by lomartin          #+#    #+#             */
/*   Updated: 2025/12/03 21:54:20 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** @brief Returns the highest value between count longs
** @param count Count of long to expect
** @return Highest between all given values
*/
long	ft_max_var(unsigned int count, ...)
{
	va_list	ap_max;
	long	max;
	long	arg;

	max = 0;
	if (!count)
		return (0);
	va_start(ap_max, count);
	while (count--)
	{
		arg = va_arg(ap_max, long);
		if (arg > max)
			max = arg;
	}
	va_end(ap_max);
	return (max);
}
