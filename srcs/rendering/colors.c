/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 19:37:29 by lomartin          #+#    #+#             */
/*   Updated: 2026/02/16 11:17:40 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
//
#include "vectors_maths_1.h"
#include "colors_maths.h"

t_color	parse_color(int color)
{
	t_color	p_color;

	p_color.alpha = color >> 8 * 3;
	p_color.red = color >> (8 * 2) & 255;
	p_color.green = color >> 8 & 255;
	p_color.blue = color & 255;
	return (p_color);
}

int	get_color(t_color p_color)
{
	int	color;

	color = 0;
	color += p_color.alpha << 8 * 3;
	color += p_color.red << 8 * 2;
	color += p_color.green << 8;
	color += p_color.blue;
	return (color);
}

int	get_color_chars(unsigned char a, unsigned char r, unsigned char g,
		unsigned char b)
{
	int	color;

	color = 0;
	color += (a << 24);
	color += (r << 16) & 16777215;
	color += (g << 8) & 65535;
	color += b & 255;
	return (color);
}

int	get_sky_color(int ambient_color, t_vect3 ray)
{
	float	upness;

	upness = dot_product(ray, (t_vect3){0, 1, 0});
	upness = (upness + 1) / 8;
	return (color_intensity(ambient_color, 0.75 + upness));
}

// int	get_prev_color(t_vect3 pos, t_mlx_data *mlx)
// {
// 	if (pos.x < 0 || pos.x >= WIN_WIDTH || pos.y < 0 || pos.y >= WIN_HEIGHT)
// 		return (0);
// 	return (mlx->s_img_data.addr[((int)pos.y * LINE_SIZE + (int)pos.x
// 		* BPP)]);
// }
