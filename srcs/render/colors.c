/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 19:37:29 by lomartin          #+#    #+#             */
/*   Updated: 2026/02/12 09:06:03 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

int	get_color_chars(char a, char r, char g, char b)
{
	int	color;

	color = 0;
	color += (a << (24));
	color += (r << (16)) & 16777215;
	color += (g << 8) & 65535;
	color += b & 255;
	return (color);
}

int	color_gradient(int start, int end, float progress)
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
