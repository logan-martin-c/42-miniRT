/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 15:26:34 by lomartin          #+#    #+#             */
/*   Updated: 2025/12/11 14:00:13 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** @brief Converts string to int
** @param str Null-terminated string to convert
** @return Converted integer value
*/
int	ft_atoi_base(const char *str, char *base)
{
	int		nbr;
	int		sin;
	size_t	baselen;

	nbr = 0;
	sin = 1;
	if (!str || !ft_isvalidbase(base))
		return (0);
	baselen = ft_strlen(base);
	while (ft_isspace(*str))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sin = -sin;
		str++;
	}
	while (ft_isinset(*str, base))
	{
		nbr = nbr * baselen + (ft_strclen(base, *str));
		str++;
	}
	return (nbr * sin);
}
