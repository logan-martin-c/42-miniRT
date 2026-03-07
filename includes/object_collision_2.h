/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_collision_2.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adastugu <adastugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 15:45:10 by adastugu          #+#    #+#             */
/*   Updated: 2026/03/07 16:40:42 by adastugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vectors_maths_1.h"
#include "vectors_maths_2.h"

/* static inline t_nearest_object	cylinder_collision(t_ray ray, t_object *object)
{
	t_nearest_object hit;

	float t_hit = -1.0f;
	t_vect3 ba = vector_mult(object->rot, object->u_data.cylinder.height);
	t_vect3 bottom_center = vectors_sub(object->pos, vector_mult(object->rot, object->u_data.cylinder.height / 2.0));
	t_vect3 oc = vectors_sub(ray.origin, bottom_center);
	float radius = object->u_data.cylinder.diameter / 2.0f;
	float baba = dot_product(ba, ba);
	float bard = dot_product(ba, ray.dir) ;
	float baoc = dot_product(ba, oc);
	float k2 = baba - bard * bard;
	float k1 = baba*dot_product(oc, ray.dir) - baoc*bard;
	float k0 = baba*dot_product(oc,oc) - baoc*baoc - radius * radius * baba;
	float h = k1*k1 - k2 * k0;
	float t1 = (-k1 - h) / k2;
    float t2 = (-k1 + h) / k2;
	if (h < 0.0f)
		return (hit.t = -1, hit);
	h = sqrt(h);
	float t = (-k1 - h) / k2;
	float y  = baoc + t*bard;

	float y1 = baoc + t1 * bard;
    if (t1 > 0.001f && y1 > 0.0f && y1 < baba)
        t_hit = t1;
    else 
    {
        float y2 = baoc + t2 * bard;
        if (t2 > 0.001f && y2 > 0.0f && y2 < baba)
            t_hit = t2;
    }

	if (t > 0.001f)
	{
		t_vect3 tmp = vectors_add(oc, vector_mult(ray.dir, t));
        t_vect3 projection = vector_mult(ba, y / baba);
        hit.normal = vector_norm(vectors_sub(tmp, projection));
		if (dot_product(hit.normal, ray.dir) > 0)
            hit.normal = vector_mult(hit.normal, -1.0f);
		return (hit.t = t_hit, hit.obj = object, hit);
	}
	if (fabs(bard) < 0.0001f) return (hit);
	if (y < 0.0)
		t = 0.0;
	else
		t = baba;
	t = (t -baoc) / bard;
	if(t > 0.001f && ft_abs_float(k1+k2 *t) < h)
	{
		if (y < 0.0f)
			hit.normal = vector_mult(vector_norm(ba), -1.0f);
		else
			hit.normal = vector_mult(vector_norm(ba), 1.0f);
		if (dot_product(hit.normal, ray.dir) > 0)
            hit.normal = vector_mult(hit.normal, -1.0f);
		return (hit.t = t, hit.obj = object, hit);
	}
	return (hit.t = -1, hit);
} */

static inline t_nearest_object  cylinder_collision(t_ray ray, t_object *object)
{
    t_nearest_object hit;
    hit.t = -1.0f;
	hit.is_inside = false;

    t_vect3 ba = vector_mult(object->rot, object->u_data.cylinder.height);
    t_vect3 bottom_center = vectors_sub(object->pos, vector_mult(object->rot, object->u_data.cylinder.height / 2.0));
    t_vect3 oc = vectors_sub(ray.origin, bottom_center);
    float radius = object->u_data.cylinder.diameter / 2.0f;
    
    float baba = dot_product(ba, ba);
    float bard = dot_product(ba, ray.dir);
    float baoc = dot_product(ba, oc);
    
    float k2 = baba - bard * bard;
    float k1 = baba * dot_product(oc, ray.dir) - baoc * bard;
    float k0 = baba * dot_product(oc, oc) - baoc * baoc - radius * radius * baba;
    
    float h = k1 * k1 - k2 * k0;
    if (h < 0.0f) return (hit);
    h = sqrt(h);

    // --- BODY CHECK (Try t1 then t2) ---
    float t_body = -1.0f;
    float t1 = (-k1 - h) / k2;
    float t2 = (-k1 + h) / k2;

    float y1 = baoc + t1 * bard;
    if (t1 > 0.001f && y1 > 0.0f && y1 < baba)
        t_body = t1;
    else {
        float y2 = baoc + t2 * bard;
        if (t2 > 0.001f && y2 > 0.0f && y2 < baba)
            t_body = t2;
    }

    // --- CAPS CHECK ---
    float t_cap = -1.0f;
    if (fabs(bard) > 0.0001f)
    {
        // Check bottom cap (y=0) and top cap (y=baba)
        float t_bot = (0.0f - baoc) / bard;
        float t_top = (baba - baoc) / bard;

        if (t_bot > 0.001f && ft_abs_float(k1 + k2 * t_bot) < h)
            t_cap = t_bot;
        
        // If top is closer than bottom (or bottom was invalid), take top
        if (t_top > 0.001f && ft_abs_float(k1 + k2 * t_top) < h)
        {
            if (t_cap < 0.001f || t_top < t_cap)
                t_cap = t_top;
        }
    }

    // --- DECIDE WINNER (Body vs Cap) ---
    float final_t = -1.0f;
	hit.hit_type = _none;
    if (t_body > 0.001f && (t_cap < 0.001f || t_body < t_cap))
    {
        final_t = t_body;
        float y = baoc + final_t * bard;
        t_vect3 p_rel = vectors_add(oc, vector_mult(ray.dir, final_t));
        hit.normal = vector_norm(vectors_sub(p_rel, vector_mult(ba, y / baba)));
		hit.hit_type = _body;
    }
    else if (t_cap > 0.001f)
    {
        final_t = t_cap;
        float y = baoc + final_t * bard;
        t_vect3 n = vector_norm(ba);
        hit.normal = (y < baba / 2.0f) ? vectors_sub((t_vect3){0.0, 0.0, 0.0}, hit.normal) : n;
		hit.hit_type = _caps;
    }

    if (final_t > 0.001f)
    {
        hit.t = final_t;
        hit.obj = object;
        if (dot_product(hit.normal, ray.dir) > 0)
		{
			hit.is_inside = true;
            hit.normal = vectors_sub((t_vect3){0.0, 0.0, 0.0}, hit.normal);
		}
        return (hit);
    }

    return (hit);
}

static inline t_nearest_object cone_collision(t_ray ray, t_object *obj)
{
    t_nearest_object hit = {.t = -1.0f, .is_inside = false, .obj = obj};
    
    t_vect3  axis = obj->rot;
    float    h = obj->u_data.cone.height;
    float    r = obj->u_data.cone.radius;
    float    m = (r * r) / (h * h);
    
    t_vect3  oc = vectors_sub(ray.origin, obj->pos);
    float    dot_rd_axis = dot_product(ray.dir, axis);
    float    dot_oc_axis = dot_product(oc, axis);
    
    float    a = dot_product(ray.dir, ray.dir) - (1.0f + m) * (dot_rd_axis * dot_rd_axis);
    float    b = 2.0f * (dot_product(ray.dir, oc) - (1.0f + m) * dot_rd_axis * dot_oc_axis);
    float    c = dot_product(oc, oc) - (1.0f + m) * (dot_oc_axis * dot_oc_axis);
    
    float    delta = b * b - 4.0f * a * c;
    if (delta < 0.0f) return (hit);
    
    float    sqrt_delta = sqrt(delta);
    float    t1 = (-b - sqrt_delta) / (2.0f * a);
    float    t2 = (-b + sqrt_delta) / (2.0f * a);
    
    float t_body = -1.0f;
    float selected_t = (t1 > 0.001f) ? t1 : t2;
    if (selected_t > 0.001f)
    {
        float cp_v = dot_product(vectors_add(oc, vector_mult(ray.dir, selected_t)), axis);
        if (cp_v > 0.0f && cp_v < h)
            t_body = selected_t;
    }

    float t_cap = -1.0f;
    t_vect3 base_center = vectors_add(obj->pos, vector_mult(axis, h));
    float denom = dot_product(ray.dir, axis);
    if (fabs(denom) > 0.0001f)
    {
        float t = dot_product(vectors_sub(base_center, ray.origin), axis) / denom;
        if (t > 0.001f)
        {
            t_vect3 p = vectors_add(ray.origin, vector_mult(ray.dir, t));
            t_vect3 v = vectors_sub(p, base_center);
            if (dot_product(v, v) <= r * r)
                t_cap = t;
        }
    }

    float final_t = -1.0f;
    hit.hit_type = _none; // 1 for body, 2 for cap
    if (t_body > 0.001f && (t_cap < 0.001f || t_body < t_cap)) {
        final_t = t_body;
        hit.hit_type = _body;
    } else if (t_cap > 0.001f) {
        final_t = t_cap;
        hit.hit_type = _caps;
    }

    if (final_t > 0.001f)
    {
        hit.t = final_t;
        t_vect3 outward_n;
        if (hit.hit_type == _body) {
            t_vect3 p = vectors_add(ray.origin, vector_mult(ray.dir, final_t));
            t_vect3 cp = vectors_sub(p, obj->pos);
            float dist_on_axis = dot_product(cp, axis);
            t_vect3 orthogonal = vectors_sub(cp, vector_mult(axis, dist_on_axis));
            outward_n = vector_norm(vectors_sub(orthogonal, vector_mult(axis, m * dist_on_axis)));
        } else {
            outward_n = axis;
        }

        if (dot_product(ray.dir, outward_n) > 0.0f) {
            hit.is_inside = true;
            hit.normal = vector_mult(outward_n, -1.0f);
        } else {
            hit.is_inside = false;
            hit.normal = outward_n;
        }
    }
    return (hit);
}

static inline t_nearest_object new_sphere_collision(t_ray ray, t_object *obj)
{
	t_nearest_object hit;

	hit.t = -1.0f;
    hit.obj = obj; 
    hit.is_inside = false;
    t_vect3 l = vectors_sub(ray.origin, obj->pos);
    float b = 2.0f * dot_product(ray.dir, l);
    float c = dot_product(l, l) - (obj->u_data.sphere.radius * obj->u_data.sphere.radius);
    float delta = b * b - 4.0f * c;
    if (delta < 0) 
		return (hit.t = -1, hit);
    float sqrt_delta = sqrt(delta);
    float t = (-b - sqrt_delta) / 2.0f;
    if (t < 0.001f)
        t = (-b + sqrt_delta) / 2.0f;
    if (t < 0.001f)
        return (hit.t = -1, hit);
    hit.t = t;
    hit.obj = obj;
    t_vect3 hit_point = vectors_add(ray.origin, vector_mult(ray.dir, t));
    t_vect3 normal_vec = vectors_sub(hit_point, obj->pos);
    hit.normal = vector_mult(normal_vec, 1.0f / obj->u_data.sphere.radius);
	if (dot_product(hit.normal, ray.dir) > 0)
	{
		hit.is_inside = true;
		hit.normal = vector_mult(hit.normal, -1.0f);
	}
    return (hit);
}

static inline t_nearest_object plane_collision(t_ray ray, t_object *obj)
{
    t_nearest_object    hit;
    float               dot_on_rd;
    float               t;
    t_vect3             oc;

    hit.t = -1.0f;
    hit.obj = obj;
	hit.is_inside = false;
    dot_on_rd = dot_product(obj->rot, ray.dir);
    if (ft_abs_float(dot_on_rd) < 0.00001f)
        return (hit);
    oc = vectors_sub(obj->pos, ray.origin);
    t = dot_product(oc, obj->rot) / dot_on_rd;
    if (t < 0.001f)
        return (hit);
    hit.t = t;
    if (dot_on_rd > 0)
        hit.normal = vector_mult(obj->rot, -1.0f);
    else
        hit.normal = obj->rot;
    return (hit);
}