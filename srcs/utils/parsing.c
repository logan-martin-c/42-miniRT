/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 11:06:07 by lomartin          #+#    #+#             */
/*   Updated: 2026/02/14 12:04:31 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	check_args_count(char **args, unsigned int min, unsigned int max)
{
	unsigned int	i;

	if (min > max || (!args && min))
		return (-1);
	if (!args && !min)
		return (0);
	i = 0;
	while (i < min)
	{
		if (!args[i])
			return (-1);
		i++;
	}
	while (i < max)
	{
		if (!args[i])
			return (i - 1);
		i++;
	}
	if (args[i])
		return (-1);
	return (i);
}
