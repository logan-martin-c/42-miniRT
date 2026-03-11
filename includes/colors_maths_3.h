/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_maths_3.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adastugu <adastugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 11:22:24 by lomartin          #+#    #+#             */
/*   Updated: 2026/03/09 13:27:57 by adastugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_MATHS_3_H
# define COLORS_MATHS_3_H

static inline int	get_color_summed(t_vect2 pointer, t_float_color *color_tab,
		t_float_color new_color, long frame_nb)
{
	t_float_color	*color;

	color = &color_tab[pointer.y * WIN_WIDTH + pointer.x];
	if (frame_nb == -2)
		return (vec4_to_color((colors_divide(*color, frame_nb + 1))));
	if (frame_nb <= 0)
		*color = new_color;
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

#endif
