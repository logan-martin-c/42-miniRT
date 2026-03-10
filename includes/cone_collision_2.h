/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_collision_2.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adastugu <adastugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 15:28:21 by adastugu          #+#    #+#             */
/*   Updated: 2026/03/09 15:31:43 by adastugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONE_COLLISION_2_H
# define CONE_COLLISION_2_H

static inline t_nearest_object	cone_collision(t_ray ray, t_object *obj)
{
	t_nearest_object	hit;
	t_coc				coc;

	hit = (t_nearest_object){.t = -1.0f, .is_inside = false, .obj = obj};
	coc_ini(&coc, ray, obj);
	if (coc.delta < 0.0f)
		return (hit);
	coc.sqrt_delta = sqrt(coc.delta);
	coc.t1 = (-coc.b - coc.sqrt_delta) / (2.0f * coc.a);
	coc.t2 = (-coc.b + coc.sqrt_delta) / (2.0f * coc.a);
	coc_cal_t_body(&coc, ray);
	coc_cal_t_cap(&coc, ray, obj);
	coc_choose_t_final(&coc, &hit);
	if (coc.final_t > 0.001f)
		coc_calc_hit(&coc, ray, obj, &hit);
	return (hit);
}

#endif
