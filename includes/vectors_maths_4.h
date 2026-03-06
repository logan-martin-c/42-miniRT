/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_maths_4.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adastugu <adastugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 11:44:46 by adastugu          #+#    #+#             */
/*   Updated: 2026/03/06 16:21:41 by adastugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORS_MATHS_4H
# define VECTORS_MATHS_4_H

#include "minirt.h"
#include "vectors_maths_1.h"
#include "vectors_maths_3.h"

static inline t_vect3 random_unit_vector(void)
{
    float z = fast_rand() * 2.0f - 1.0f; // Range -1 to 1
    float a = fast_rand() * 2.0f * 3.14159265f; // Range 0 to 2pi
    float r = sqrt(1.0f - z * z);
    float x = r * cos(a);
    float y = r * sin(a);
    return ((t_vect3){x, y, z});
}

#endif