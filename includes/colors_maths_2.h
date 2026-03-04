/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_maths_2.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adastugu <adastugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 15:17:00 by adastugu          #+#    #+#             */
/*   Updated: 2026/03/04 16:02:07 by adastugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static inline t_float_color	colors_add(t_float_color a, t_float_color b)
{
	return ((t_float_color){a.a ,a.r + b.r, a.g + b.g, a.b + b.b});
}

static inline t_float_color	colors_sub(t_float_color a, t_float_color b)
{
	return ((t_float_color){a.a , a.r - b.r, a.g - b.g, a.b - b.b});
}

static inline t_float_color	colors_mult(t_float_color a, t_float_color b)
{
	t_float_color new_vec3;

	new_vec3.a = a.a;
	new_vec3.r = a.r * b.r;
	new_vec3.g = a.g * b.g;
	new_vec3.b = a.b * b.b;
	return (new_vec3);
}

static inline t_float_color	colors_scal(t_float_color a, float scal)
{
	a.r *= scal;
	a.g *= scal;
	a.b *= scal;
	return (a);
}