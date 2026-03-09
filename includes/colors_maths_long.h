/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_maths_long.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adastugu <adastugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 11:22:24 by lomartin          #+#    #+#             */
/*   Updated: 2026/03/09 13:18:37 by adastugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_MATHS_LONG_H
# define COLORS_MATHS_LONG_H

static inline t_float_color	color_correction(t_float_color color);

static inline t_long_color	set_long_color(int color)
{
	t_long_color	p_color;

	p_color.a = color >> 8 * 3;
	p_color.r = color >> (8 * 2) & 255;
	p_color.g = color >> 8 & 255;
	p_color.b = color & 255;
	return (p_color);
}

static inline t_long_color	add_long_color(t_long_color last_color, int color)
{
	t_long_color	p_color;

	p_color = last_color;
	p_color.a += (int)(color >> (8 * 3) & 255);
	p_color.r += color >> (8 * 2) & 255;
	p_color.g += color >> 8 & 255;
	p_color.b += color & 255;
	return (p_color);
}

static inline int	get_long_color(t_long_color p_color)
{
	int	color;

	color = 0;
	color += p_color.a << 8 * 3;
	color += p_color.r << 8 * 2;
	color += p_color.g << 8;
	color += p_color.b;
	return (color);
}

static inline t_long_color	divide_long_color(t_long_color color, long div)
{
	color.a /= div;
	color.r /= div;
	color.g /= div;
	color.b /= div;
	return (color);
}

static inline int	get_color_summed(t_vect2 pointer, t_float_color *color_tab,
		t_float_color new_color, long frame_nb)
{
	t_float_color	*color;

	color = &color_tab[pointer.y * WIN_WIDTH + pointer.x];
	if (frame_nb <= 0)
		*color = new_color;
	else if (frame_nb == __LONG_MAX__)
		return (vec4_to_color((colors_divide(*color, frame_nb + 1))));
	else
	{
		*color = colors_add(*color, new_color);
		return (vec4_to_color((colors_divide(*color, frame_nb + 1))));
	}
	return (vec4_to_color((*color)));
}

static inline int	float_to_int_color_gamma(t_float_color f)
{
	int	r;
	int	g;
	int	b;

	f.r = fminf(1.0f, fmaxf(0.0f, f.r));
	f.g = fminf(1.0f, fmaxf(0.0f, f.g));
	f.b = fminf(1.0f, fmaxf(0.0f, f.b));
	f.r = powf(f.r, 1.0f / 2.2f);
	f.g = powf(f.g, 1.0f / 2.2f);
	f.b = powf(f.b, 1.0f / 2.2f);
	r = (int)(f.r * 255.999f);
	g = (int)(f.g * 255.999f);
	b = (int)(f.b * 255.999f);
	return (r << 16 | g << 8 | b);
}

/* static inline int get_color_summed_2(t_vect2 p, t_float_color *color_tab,
	t_float_color new_ray_color, long frame)
{
	int i = p.y * WIN_WIDTH + p.x;

	if (frame <= 1) {
		color_tab[i] = new_ray_color;
	} else {
		float a = 1.0f / (float)frame;
		color_tab[i].r = color_tab[i].r * (1.0f - a) + (new_ray_color.r * a);
		color_tab[i].g = color_tab[i].g * (1.0f - a) + (new_ray_color.g * a);
		color_tab[i].b = color_tab[i].b * (1.0f - a) + (new_ray_color.b * a);
	}
	return (vec4_to_color(color_tab[i]));
} */

#endif
