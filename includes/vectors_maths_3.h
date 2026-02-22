/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_maths.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 09:43:55 by lomartin          #+#    #+#             */
/*   Updated: 2026/02/16 11:11:51 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORS_MATHS_3_H
# define VECTORS_MATHS_3_H

# include "minirt.h"

static inline float fast_rand()
{
    static unsigned int  xorshift_state = 42;

    xorshift_state ^= xorshift_state << 13;
    xorshift_state ^= xorshift_state >> 17;
    xorshift_state ^= xorshift_state << 5;
    return (xorshift_state * (1.0f / 4294967296.0f));
}

static inline t_vect3 get_random_vector(float min, float max)
{
    t_vect3 v;

    v.x = fast_rand() * (max - min) + min;
    v.y = fast_rand() * (max - min) + min;
    v.z = fast_rand() * (max - min) + min;
    return (v);
}

static inline t_vect3  get_diffuse_vector(t_vect3 normal)
{
    t_vect3    v;

    while (1)
    {
        v = vector_norm(get_random_vector(-1, 1));
        if (dot_product(normal, v) <= 0)
            return (v);
    }
}

#endif
