/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameters.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 19:48:49 by lomartin          #+#    #+#             */
/*   Updated: 2026/02/12 09:09:45 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_pos(char *str, t_pos_xyz *pos)
{
	char		**spl_str;

	spl_str = ft_split(str, ',');
	if (!spl_str || !spl_str[0] || !spl_str[1] || !spl_str[2] || spl_str[3])
		return (1);
	pos->x = ft_atod(spl_str[0]) * 1000;
	pos->y = ft_atod(spl_str[1]) * 1000;
	pos->z = ft_atod(spl_str[2]) * 1000;
	return (0);
}

int	parse_raw_color(char *str, int *color)
{
	int		r;
	int		v;
	int		b;
	char	**spl_str;

	spl_str = ft_split(str, ',');
	if (!spl_str || !spl_str[0] || !spl_str[1] || !spl_str[2] || spl_str[3])
		return (1);
	r = ft_atoi(spl_str[0]);
	v = ft_atoi(spl_str[1]);
	b = ft_atoi(spl_str[2]);
	if (r > 255 || r < 0)
		return (2);
	if (v > 255 || v < 0)
		return (2);
	if (b > 255 || b < 0)
		return (2);
	*color = get_color_chars(255, r, v, b);
	return (0);
}
