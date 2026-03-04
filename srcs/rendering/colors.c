/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adastugu <adastugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 19:37:29 by lomartin          #+#    #+#             */
/*   Updated: 2026/03/04 15:51:15 by adastugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
//
#include "colors_maths.h"
#include "vectors_maths_1.h"

t_float_color	parse_color(int color)
{
	t_float_color	p_color;

	p_color.a = color >> 8 * 3;
	p_color.r = color >> (8 * 2) & 255;
	p_color.g = color >> 8 & 255;
	p_color.b = color & 255;
	return (p_color);
}

int	get_color(t_float_color p_color)
{
	int	r;
	int	g;
	int	b;
	int	a;

	r = (int)(p_color.r * 255.0f);
	g = (int)(p_color.g * 255.0f);
	b = (int)(p_color.b * 255.0f);
	a = (int)(p_color.a * 255.0f);
	return (a << 24 | r << 16 | g << 8 | b);
}

t_float_color	get_color_chars(unsigned char a, unsigned char r,
		unsigned char g, unsigned char b)
{
	t_float_color	color;

	color.a = (float)a / 255;
	color.r = (float)r / 255;
	color.g = (float)g / 255;
	color.b = (float)b / 255;
	return (color);
}

t_float_color	get_sky_color(t_float_color ambient_color, t_vect3 ray)
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
