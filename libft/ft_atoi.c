/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 15:26:34 by lomartin          #+#    #+#             */
/*   Updated: 2025/11/23 13:20:42 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** @brief Converts string to int
** @param str Null-terminated string to convert
** @return Converted integer value
*/
int	ft_atoi(const char *str)
{
	int	nbr;
	int	sin;

	nbr = 0;
	sin = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sin = -sin;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		nbr = nbr * 10 + (*str - '0');
		str++;
	}
	return (nbr * sin);
}
