/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_maths.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 11:22:24 by lomartin          #+#    #+#             */
/*   Updated: 2026/02/16 11:10:13 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

t_long_color	set_long_color(int color)
{
	t_long_color	p_color;

	p_color.a = color >> 8 * 3;
	p_color.r = color >> (8 * 2) & 255;
	p_color.g = color >> 8 & 255;
	p_color.b = color & 255;
	return (p_color);
}

t_long_color	add_long_color(t_long_color last_color, int color)
{
	t_long_color	p_color;

	p_color = last_color;
	p_color.a += (int)(color >> (8 * 3) & 255);
	p_color.r += color >> (8 * 2) & 255;
	p_color.g += color >> 8 & 255;
	p_color.b += color & 255;
	return (p_color);
}

int	get_long_color(t_long_color p_color)
{
	int	color;

	color = 0;
	color += p_color.a << 8 * 3;
	color += p_color.r << 8 * 2;
	color += p_color.g << 8;
	color += p_color.b;
	return (color);
}

t_long_color	divide_long_color(t_long_color color, long div)
{
	color.a /= div;
	color.r /= div;
	color.g /= div;
	color.b /= div;
	return (color);
}

static inline int	get_color_summed(t_vect2 pointer, t_long_color *color_tab, int new_color, long frame_nb)
{
	t_long_color	*color;

	color = &color_tab[pointer.y * WIN_WIDTH + pointer.x];
	if (!frame_nb)
		*color = set_long_color(new_color);
	else if (frame_nb == __LONG_MAX__)
		return (get_long_color(divide_long_color(*color, frame_nb + 1)));
	else
	{
		*color = add_long_color(*color, new_color);
		return (get_long_color(divide_long_color(*color, frame_nb + 1)));
	}
	return (get_long_color(*color));
}
