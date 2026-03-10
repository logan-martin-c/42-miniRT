/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_collision.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adastugu <adastugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 11:16:20 by adastugu          #+#    #+#             */
/*   Updated: 2026/03/09 15:31:14 by adastugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONE_COLLISION_H
# define CONE_COLLISION_H

typedef struct s_coc
{
	t_vect3						axis;
	float						h;
	float						r;
	float						m;
	t_vect3						oc;
	float						dot_rd_axis;
	float						dot_oc_axis;
	float						a;
	float						b;
	float						c;
	float						delta;
	float						sqrt_delta;
	float						t1;
	float						t2;
	float						t_body;
	float						selected_t;
	float						cp_v;
	float						t_cap;
	t_vect3						base_center;
	float						denom;
	float						t;
	t_vect3						v;
	float						final_t;
	t_vect3						outward_n;
	t_vect3						p;
	t_vect3						cp;
	float						dist_on_axis;
	t_vect3						orthogonal;
}								t_coc;

static inline void	coc_ini(t_coc *coc, t_ray ray, t_object *obj)
{
	coc->axis = obj->rot;
	coc->h = obj->u_data.cone.height;
	coc->r = obj->u_data.cone.radius / 2;
	coc->m = (coc->r * coc->r) / (coc->h * coc->h);
	coc->oc = vectors_sub(ray.origin, obj->pos);
	coc->dot_rd_axis = dot_product(ray.dir, coc->axis);
	coc->dot_oc_axis = dot_product(coc->oc, coc->axis);
	coc->a = dot_product(ray.dir, ray.dir) - (1.0f + coc->m) * (coc->dot_rd_axis
			* coc->dot_rd_axis);
	coc->b = 2.0f * (dot_product(ray.dir, coc->oc) - (1.0f + coc->m)
			* coc->dot_rd_axis * coc->dot_oc_axis);
	coc->c = dot_product(coc->oc, coc->oc) - (1.0f + coc->m) * (coc->dot_oc_axis
			* coc->dot_oc_axis);
	coc->delta = coc->b * coc->b - 4.0f * coc->a * coc->c;
}

static inline void	coc_cal_t_body(t_coc *coc, t_ray ray)
{
	coc->t_body = -1.0f;
	if (coc->t1 > 0.001f)
		coc->selected_t = coc->t1;
	else
		coc->selected_t = coc->t2;
	if (coc->selected_t > 0.001f)
	{
		coc->cp_v = dot_product(vectors_add(coc->oc, vector_mult(ray.dir,
						coc->selected_t)), coc->axis);
		if (coc->cp_v > 0.0f && coc->cp_v < coc->h)
			coc->t_body = coc->selected_t;
	}
}

static inline void	coc_cal_t_cap(t_coc *coc, t_ray ray, t_object *obj)
{
	coc->t_cap = -1.0f;
	coc->base_center = vectors_add(obj->pos, vector_mult(coc->axis, coc->h));
	coc->denom = dot_product(ray.dir, coc->axis);
	if (ft_abs_float(coc->denom) > 0.0001f)
	{
		coc->t = dot_product(vectors_sub(coc->base_center, ray.origin),
				coc->axis) / coc->denom;
		if (coc->t > 0.001f)
		{
			coc->p = vectors_add(ray.origin, vector_mult(ray.dir, coc->t));
			coc->v = vectors_sub(coc->p, coc->base_center);
			if (dot_product(coc->v, coc->v) <= coc->r * coc->r)
				coc->t_cap = coc->t;
		}
	}
}

static inline void	coc_choose_t_final(t_coc *coc, t_nearest_object *hit)
{
	coc->final_t = -1.0f;
	hit->e_hit_type = _none;
	if (coc->t_body > 0.001f && (coc->t_cap < 0.001f
			|| coc->t_body < coc->t_cap))
	{
		coc->final_t = coc->t_body;
		hit->e_hit_type = _body;
	}
	else if (coc->t_cap > 0.001f)
	{
		coc->final_t = coc->t_cap;
		hit->e_hit_type = _caps;
	}
}

static inline void	coc_calc_hit(t_coc *coc, t_ray ray, t_object *obj,
		t_nearest_object *hit)
{
	hit->t = coc->final_t;
	if (hit->e_hit_type == _body)
	{
		coc->p = vectors_add(ray.origin, vector_mult(ray.dir, coc->final_t));
		coc->cp = vectors_sub(coc->p, obj->pos);
		coc->dist_on_axis = dot_product(coc->cp, coc->axis);
		coc->orthogonal = vectors_sub(coc->cp, vector_mult(coc->axis,
					coc->dist_on_axis));
		coc->outward_n = vector_norm(vectors_sub(coc->orthogonal,
					vector_mult(coc->axis, coc->m * coc->dist_on_axis)));
	}
	else
	{
		coc->outward_n = coc->axis;
	}
	if (dot_product(ray.dir, coc->outward_n) > 0.0f)
	{
		hit->is_inside = true;
		hit->normal = vector_mult(coc->outward_n, -1.0f);
	}
	else
	{
		hit->is_inside = false;
		hit->normal = coc->outward_n;
	}
}

#endif
