/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameters.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 19:48:49 by lomartin          #+#    #+#             */
/*   Updated: 2026/02/14 11:35:00 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_pos(char *str, t_pos_xyz *pos)
{
	char	**spl_str;

	spl_str = ft_split(str, ',');
	if (!spl_str || check_args_count(spl_str, 3, 3) == -1)
		return (ft_free_strs(spl_str), 1);
	if (!ft_isfloat_str(spl_str[0]) || !ft_isfloat_str(spl_str[1])
		|| !ft_isfloat_str(spl_str[2]))
		return (ft_free_strs(spl_str), 1);
	pos->x = ft_atod(spl_str[0]) * 1000;
	pos->y = ft_atod(spl_str[1]) * 1000;
	pos->z = ft_atod(spl_str[2]) * 1000;
	ft_free_strs(spl_str);
	return (0);
}

int	parse_raw_color(char *str, int *color)
{
	int		a;
	int		r;
	int		v;
	int		b;
	int		args_count;
	char	**spl_str;
	int		i;

	spl_str = ft_split(str, ',');
	args_count = check_args_count(spl_str, 3, 4);
	if (!spl_str || args_count == -1)
		return (ft_free_strs(spl_str), 1);
	if (!ft_isdigit_str(spl_str[0]) || !ft_isdigit_str(spl_str[1])
		|| !ft_isdigit_str(spl_str[2]))
		return (ft_free_strs(spl_str), 1);
	i = -1;
	if (args_count == 4)
		a = ft_atoi(spl_str[++i]);
	else
		a = 255;
	r = ft_atoi(spl_str[++i]);
	v = ft_atoi(spl_str[++i]);
	b = ft_atoi(spl_str[++i]);
	ft_free_strs(spl_str);
	if (a > 255 || a < 0 || r > 255 || r < 0 || v > 255 || v < 0 || b > 255
		|| b < 0)
		return (2);
	*color = get_color_chars(a, r, v, b);
	return (0);
}
