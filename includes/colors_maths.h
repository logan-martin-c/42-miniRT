/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_maths.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adastugu <adastugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 11:22:24 by lomartin          #+#    #+#             */
/*   Updated: 2026/02/24 16:48:06 by adastugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static inline t_vect3 color_to_vec3(int argb)
{
	t_vect3 color;

        color.x = ((argb >> 16) & 0xFF) / 255.0f;
		color.y = ((argb >> 8) & 0xFF) / 255.0f;
   		color.z = (argb & 0xFF) / 255.0f;
	return (color);
}

static inline int vec3_to_color(t_vect3 color)
{
    if (color.x > 1.0f) color.x = 1.0f;
    if (color.y > 1.0f) color.y = 1.0f;
    if (color.z > 1.0f) color.z = 1.0f;

    int r = (int)(color.x * 255.0f);
    int g = (int)(color.y * 255.0f);
    int b = (int)(color.z * 255.0f);

    return (255 << 24) | (r << 16) | (g << 8) | b;
}

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
