/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isvalidbase_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 18:35:24 by lomartin          #+#    #+#             */
/*   Updated: 2025/11/23 18:58:46 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** @brief Check the number base is valid(no duplicate, no spaces, no sign,
** 	and printable characters)
** @param base Base to check
** @return Non-zero if valid, zero otherwhise
*/
int	ft_isvalidbase(char *base)
{
	int	i;

	if (!base || ft_strlen(base) < 2)
		return (0);
	while (*base)
	{
		i = 0;
		if (*base == '+' || *base == '-' || ft_isspace(*base)
			|| !ft_isprint(*base))
			return (0);
		while (base[++i])
		{
			if (*base == base[i])
				return (0);
		}
		base++;
	}
	return (1);
}
