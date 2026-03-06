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

static inline t_vect3 get_diffuse_vector_2(t_vect3 normal)
{
    // Lambertian Reflection: Normal + Random Unit Vector
    // This creates a distribution where light is stronger 
    // when the bounce is closer to the normal.
    t_vect3 bounce_dir = vectors_add(normal, random_unit_vector());
    
    // If the random vector was exactly opposite the normal, we get zero.
    // Let's catch that rare case to avoid NaNs.
    if (dot_product(bounce_dir, bounce_dir) < 0.001f)
        return (normal);
        
    return (vector_norm(bounce_dir));
}

float fresnel(t_vect3 ray_dir, t_vect3 normal, float n1, float n2)
{
    float r0 = (n1 - n2) / (n1 + n2);
    r0 = r0 * r0;

    float cos_theta = -dot_product(normal, ray_dir);
    if (n1 > n2)
    {
        float eta = n1 / n2;
        float sin2_t = eta * eta * (1.0f - cos_theta * cos_theta);
        if (sin2_t > 1.0f) return 1.0f; // Total Internal Reflection
        cos_theta = sqrt(1.0f - sin2_t);
    }
    float x = 1.0f - cos_theta;
    return r0 + (1.0f - r0) * (x * x * x * x * x); // r0 + (1-r0) * (1-cos)^5
}

t_vect3 refract_2(t_vect3 i, t_vect3 n, float n1, float n2)
{
    float eta = n1 / n2;
    float cos_i = -dot_product(n, i);
    float k = 1.0f - eta * eta * (1.0f - cos_i * cos_i);
    
    if (k < 0.0f) // Total Internal Reflection
        return reflect(i, n);
        
    return vectors_add(vector_mult(i, eta), vector_mult(n, eta * cos_i - sqrt(k)));
}

static inline t_vect3 get_bounce_2(t_ray ray, t_nearest_object hit, float n1, float n2)
{
    if (hit.obj->color.a < 1.0f)
    {
        float kr = fresnel(ray.dir, hit.normal, n1, n2);
        if (fast_rand() < (kr * hit.obj->reflectance))
            return reflect(ray.dir, hit.normal);

        t_vect3 refr_dir = refract_2(ray.dir, hit.normal, n1, n2);
        float milkiness = hit.obj->color.a; 
        if (milkiness > 0.05f)
        {
            t_vect3 random_jitter = get_random_vector(-1, 1);
            refr_dir = vector_norm(vectors_add(refr_dir, vector_mult(random_jitter, milkiness * 0.5f)));
        }
        return (refr_dir);
    }
    if (fast_rand() < hit.obj->reflectance)
        return reflect(ray.dir, hit.normal);
    else
        return get_diffuse_vector_2(hit.normal); 
}

#endif