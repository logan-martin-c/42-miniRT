/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texturing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adastugu <adastugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 15:16:39 by adastugu          #+#    #+#             */
/*   Updated: 2026/03/04 15:28:25 by adastugu         ###   ########.fr       */
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
#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif

t_float_color	get_checkerboard_color(float u, float v)
{
	int	check;

	check = (int)(u * 10) + (int)(v * 10);
	if (check % 2 == 0)
		return ((t_float_color){1, 1, 1, 1});
	return ((t_float_color){1, 0, 0, 0});
}

void	get_sphere_uv(t_vect3 point_r_c, t_object object, float *u, float *v)
{
	t_vect3	d;

	d = vector_norm(vectors_sub(point_r_c, object.pos));
	*u = 0.5 + (atan2(d.z, d.x) / (2 * M_PI));
	*v = 0.5 - (asin(d.y) / M_PI);
}

t_float_color	get_texel_color(t_texture tex, float u, float v)
{
	int	x;
	int	y;
	int color;

	x = (int)(u * tex.width);
	y = (int)(v * tex.height);
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

t_float_color	get_texture_color(t_vect3 point_r_c, t_object object)
{
	t_float_color	tex_color;

	float u, v;
	get_sphere_uv(point_r_c, object, &u, &v);
	if (object.tex_name && ft_strncmp(object.tex_name, "UV", 2))
		return (get_texel_color(object.tex, u, v));
	else if (object.tex_name && !ft_strncmp(object.tex_name, "UV", 2))
		return (tex_color = get_checkerboard_color(u, v));
	else
		return ((object.material.color));
}
