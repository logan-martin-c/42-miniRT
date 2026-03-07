/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tone_mapping.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adastugu <adastugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 18:01:20 by adastugu          #+#    #+#             */
/*   Updated: 2026/03/07 18:08:30 by adastugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static inline t_float_color ace_tone_map(t_float_color color)
{
    const float a = 2.51f;
    const float b = 0.03f;
    const float c = 2.43f;
    const float d = 0.59f;
    const float e = 0.14f;

    color.r = (color.r * (a * color.r + b)) / (color.r * (c * color.r + d) + e);
    color.g = (color.g * (a * color.g + b)) / (color.g * (c * color.g + d) + e);
    color.b = (color.b * (a * color.b + b)) / (color.b * (c * color.b + d) + e);

    // Clamp to [0, 1] just in case
    if (color.r > 1.0f) color.r = 1.0f;
    if (color.g > 1.0f) color.g = 1.0f;
    if (color.b > 1.0f) color.b = 1.0f;

    return (color);
}

static inline t_float_color gamma_correct(t_float_color color)
{
    float gamma = 1.0f / 2.2f;
    color.r = powf(color.r, gamma);
    color.g = powf(color.g, gamma);
    color.b = powf(color.b, gamma);
    return (color);
}

static inline t_float_color exposure_correction(t_float_color color)
{
    t_float_color final_pixel;
    float exposure = 0.3f;

    final_pixel = color;
    final_pixel.r *= exposure;
    final_pixel.g *= exposure;
    final_pixel.b *= exposure;
    return (final_pixel);
}

static inline t_float_color color_correction(t_float_color color)
{
    t_float_color final_pixel;

    final_pixel = exposure_correction(color);
    final_pixel = ace_tone_map(final_pixel);
    final_pixel = gamma_correct(final_pixel);
    return final_pixel;
}
