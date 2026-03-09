/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_collision.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adastugu <adastugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 18:50:07 by adastugu          #+#    #+#             */
/*   Updated: 2026/03/09 13:35:41 by adastugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vectors_maths_1.h"
#include "vectors_maths_2.h"

typedef struct s_cyc
{
	t_vect3						ba;
	t_vect3						bottom_center;
	t_vect3						oc;
	float						radius;
	float						baba;
	float						bard;
	float						baoc;
	float						k2;
	float						k1;
	float						k0;
	float						h;
	float						t_body;
	float						t1;
	float						t2;
	float						y1;
	float						y2;
	float						t_cap;
	float						final_t;
	float						t_top;
	float						t_bot;
	float						y;
	t_vect3						p_rel;
	t_vect3						n;
}								t_cyc;

static inline void	cc_ini_1(t_cyc *cyc, t_ray ray, t_object *object)
{
	cyc->ba = vector_mult(object->rot, object->u_data.cylinder.height);
	cyc->bottom_center = vectors_sub(object->pos, vector_mult(object->rot,
				object->u_data.cylinder.height / 2.0));
	cyc->oc = vectors_sub(ray.origin, cyc->bottom_center);
	cyc->radius = object->u_data.cylinder.radius;
	cyc->baba = dot_product(cyc->ba, cyc->ba);
	cyc->bard = dot_product(cyc->ba, ray.dir);
	cyc->baoc = dot_product(cyc->ba, cyc->oc);
	cyc->k2 = cyc->baba - cyc->bard * cyc->bard;
	cyc->k1 = cyc->baba * dot_product(cyc->oc, ray.dir) - cyc->baoc * cyc->bard;
	cyc->k0 = cyc->baba * dot_product(cyc->oc, cyc->oc) - cyc->baoc * cyc->baoc
		- cyc->radius * cyc->radius * cyc->baba;
	cyc->h = cyc->k1 * cyc->k1 - cyc->k2 * cyc->k0;
}

static inline void	cc_calc_t_body(t_cyc *cyc)
{
	cyc->t_body = -1.0f;
	cyc->t1 = (-cyc->k1 - cyc->h) / cyc->k2;
	cyc->t2 = (-cyc->k1 + cyc->h) / cyc->k2;
	cyc->y1 = cyc->baoc + cyc->t1 * cyc->bard;
	if (cyc->t1 > 0.001f && cyc->y1 > 0.0f && cyc->y1 < cyc->baba)
		cyc->t_body = cyc->t1;
	else
	{
		cyc->y2 = cyc->baoc + cyc->t2 * cyc->bard;
		if (cyc->t2 > 0.001f && cyc->y2 > 0.0f && cyc->y2 < cyc->baba)
			cyc->t_body = cyc->t2;
	}
}

static inline void	cc_calc_t_cap(t_cyc *cyc)
{
	cyc->t_cap = -1.0f;
	if (ft_abs_float(cyc->bard) > 0.0001f)
	{
		cyc->t_bot = (0.0f - cyc->baoc) / cyc->bard;
		cyc->t_top = (cyc->baba - cyc->baoc) / cyc->bard;
		if (cyc->t_bot > 0.001f && ft_abs_float(cyc->k1 + cyc->k2
				* cyc->t_bot) < cyc->h)
			cyc->t_cap = cyc->t_bot;
		if (cyc->t_top > 0.001f && ft_abs_float(cyc->k1 + cyc->k2
				* cyc->t_top) < cyc->h)
		{
			if (cyc->t_cap < 0.001f || cyc->t_top < cyc->t_cap)
				cyc->t_cap = cyc->t_top;
		}
	}
}

static inline void	cc_choose_cap(t_cyc *cyc, t_ray ray, t_nearest_object *hit)
{
	if (cyc->t_body > 0.001f && (cyc->t_cap < 0.001f
			|| cyc->t_body < cyc->t_cap))
	{
		cyc->final_t = cyc->t_body;
		cyc->y = cyc->baoc + cyc->final_t * cyc->bard;
		cyc->p_rel = vectors_add(cyc->oc, vector_mult(ray.dir, cyc->final_t));
		hit->normal = vector_norm(vectors_sub(cyc->p_rel, vector_mult(cyc->ba,
						cyc->y / cyc->baba)));
		hit->e_hit_type = _body;
	}
	else if (cyc->t_cap > 0.001f)
	{
		cyc->final_t = cyc->t_cap;
		cyc->y = cyc->baoc + cyc->final_t * cyc->bard;
		cyc->n = vector_norm(cyc->ba);
		if (cyc->y < cyc->baba / 2.0f)
			hit->normal = vectors_sub((t_vect3){0.0, 0.0, 0.0}, hit->normal);
		else
			hit->normal = cyc->n;
		hit->e_hit_type = _caps;
	}
}

static inline t_nearest_object	cylinder_collision(t_ray ray, t_object *object)
{
	t_nearest_object	hit;
	t_cyc				cyc;

	hit.t = -1.0f;
	hit.is_inside = false;
	cc_ini_1(&cyc, ray, object);
	if (cyc.h < 0.0f)
		return (hit);
	cyc.h = sqrt(cyc.h);
	cc_calc_t_body(&cyc);
	cc_calc_t_cap(&cyc);
	cyc.final_t = -1.0f;
	hit.e_hit_type = _none;
	cc_choose_cap(&cyc, ray, &hit);
	if (cyc.final_t > 0.001f)
	{
		hit.t = cyc.final_t;
		hit.obj = object;
		if (dot_product(hit.normal, ray.dir) > 0)
		{
			hit.is_inside = true;
			hit.normal = vectors_sub((t_vect3){0.0, 0.0, 0.0}, hit.normal);
		}
	}
	return (hit);
}
