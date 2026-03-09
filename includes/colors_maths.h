/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_maths.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adastugu <adastugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 11:22:24 by lomartin          #+#    #+#             */
/*   Updated: 2026/03/09 11:54:40 by adastugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_MATHS_H
# define COLORS_MATHS_H

static inline t_float_color	color_to_vec4(int argb)
{
	t_float_color	color;

	color.a = ((argb >> 24) & 0xFF) / 255.0f;
	color.r = ((argb >> 16) & 0xFF) / 255.0f;
	color.g = ((argb >> 8) & 0xFF) / 255.0f;
	color.b = (argb & 0xFF) / 255.0f;
	return (color);
}

static inline int	vec4_to_color(t_float_color color)
{
	int	a;
	int	r;
	int	g;
	int	b;

	if (color.a > 1.0f)
		color.r = 1.0f;
	if (color.r > 1.0f)
		color.r = 1.0f;
	if (color.g > 1.0f)
		color.g = 1.0f;
	if (color.b > 1.0f)
		color.b = 1.0f;
	a = (int)(color.a * 255.0f);
	r = (int)(color.r * 255.0f);
	g = (int)(color.g * 255.0f);
	b = (int)(color.b * 255.0f);
	return ((a << 24) | (r << 16) | (g << 8) | b);
}

static inline int	color_sup(int front, int back)
{
	t_float_color	ret;
	t_float_color	c_f;
	t_float_color	c_b;
	float			a;

	c_f = parse_color(front);
	c_b = parse_color(back);
	if (c_f.a == 0)
		return (back);
	if (c_f.a == 255)
		return (front);
	a = (float)c_f.a / 255.0;
	ret.a = 255;
	ret.r = c_f.r * a + c_b.r * (1 - a);
	ret.g = c_f.g * a + c_b.g * (1 - a);
	ret.b = c_f.b * a + c_b.b * (1 - a);
	return (get_color(ret));
}

static inline t_float_color	color_gradient(t_float_color p_color_start,
		t_float_color p_color_end, float progress)
{
	t_float_color	p_color_progress;

	p_color_progress.a = p_color_start.a + (p_color_end.a - p_color_start.a)
		* progress;
	p_color_progress.r = p_color_start.r + (p_color_end.r - p_color_start.r)
		* progress;
	p_color_progress.g = p_color_start.g + (p_color_end.g - p_color_start.g)
		* progress;
	p_color_progress.b = p_color_start.b + (p_color_end.b - p_color_start.b)
		* progress;
	return (p_color_progress);
}

static inline t_float_color	color_intensity(t_float_color color,
		float intensity)
{
	color.a *= intensity;
	color.r *= intensity;
	color.g *= intensity;
	color.b *= intensity;
	return (color);
}

#endif
