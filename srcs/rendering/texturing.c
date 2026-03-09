/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texturing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adastugu <adastugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 15:16:39 by adastugu          #+#    #+#             */
/*   Updated: 2026/03/09 12:04:06 by adastugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
//
#include "colors_maths.h"
#include "mlx_utils.h"
#include "vectors_maths_1.h"
#include "vectors_maths_2.h"
#include "vectors_maths_3.h"
#define _USE_MATH_DEFINES

t_float_color	get_checkerboard_color(t_uv uv)
{
	int	check;

	check = (int)(uv.u * 10) + (int)(uv.v * 10);
	if (check % 2 == 0)
		return ((t_float_color){1, 1, 1, 1});
	return ((t_float_color){1, 0, 0, 0});
}

t_float_color	get_texel_color(t_texture tex, t_uv uv)
{
	int	x;
	int	y;
	int	color;

	x = (int)(uv.u * tex.width);
	y = (int)(uv.v * tex.height);
	if (x >= tex.width)
		x = tex.width - 1;
	if (y >= tex.height)
		y = tex.height - 1;
	if (x < 0)
		x = 0;
	if (y < 0)
		y = 0;
	color = tex.pixels[y * tex.width + x];
	return (color_to_vec4(color));
}

t_float_color	get_texture_color(t_nearest_object hit)
{
	if (hit.obj->material.tex_name && ft_strncmp(hit.obj->material.tex_name, "UV", 2))
		return (get_texel_color(hit.obj->material.tex, hit.uv));
	if (hit.obj->material.tex_name && !ft_strncmp(hit.obj->material.tex_name, "UV", 2))
		return (get_checkerboard_color(hit.uv));
	return ((hit.obj->material.color));
}
