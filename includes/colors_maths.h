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

static inline int	color_sup(int front, int back)
{
	t_color	ret;
	t_color	c_f;
	t_color	c_b;
	float	a;

	c_f = parse_color(front);
	c_b = parse_color(back);
	if (c_f.alpha == 0)
		return (back);
	if (c_f.alpha == 255)
		return (front);
	a = (float)c_f.alpha / 255.0;
	ret.alpha = 255;
	ret.red = c_f.red * a + c_b.red * (1 - a);
	ret.green = c_f.green * a + c_b.green * (1 - a);
	ret.blue = c_f.blue * a + c_b.blue * (1 - a);
	return (get_color(ret));
}

static inline int	color_gradient(int start, int end, float progress)
{
	t_color	p_color_start;
	t_color	p_color_end;
	t_color	p_color_progress;

	p_color_start = parse_color(start);
	p_color_end = parse_color(end);
	p_color_progress.alpha = p_color_start.alpha + (p_color_end.alpha
			- p_color_start.alpha) * progress;
	p_color_progress.red = p_color_start.red + (p_color_end.red
			- p_color_start.red) * progress;
	p_color_progress.green = p_color_start.green + (p_color_end.green
			- p_color_start.green) * progress;
	p_color_progress.blue = p_color_start.blue + (p_color_end.blue
			- p_color_start.blue) * progress;
	return (get_color(p_color_progress));
}

static inline int	color_intensity(int color, float intensity)
{
	t_color	p_color;

	p_color = parse_color(color);
	p_color.red *= intensity;
	p_color.green *= intensity;
	p_color.blue *= intensity;
	return (get_color(p_color));
}

static inline int	light_filter(int light, int filter)
{
	t_color	p_light;
	t_color	p_filter;

	p_light = parse_color(light);
	p_filter = parse_color(filter);
	p_light.red = ft_min(p_light.red, p_filter.red);
	p_light.green = ft_min(p_light.green, p_filter.green);
	p_light.blue = ft_min(p_light.blue, p_filter.blue);
	return (get_color(p_light));
}
