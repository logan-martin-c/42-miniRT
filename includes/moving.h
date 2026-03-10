/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adastugu <adastugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 15:14:39 by lomartin          #+#    #+#             */
/*   Updated: 2026/03/09 16:04:41 by adastugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOVING_H
# define MOVING_H

static inline int	init_pos(t_vect2 *mouse_p, t_vect2 *last_mouse_p,
	t_vect3 *init_rot, t_vect3 cam_f)
{
	mouse_p->x -= WIN_WIDTH * 0.5;
	mouse_p->y -= WIN_HEIGHT * 0.5;
	if (last_mouse_p->x == -1 && last_mouse_p->y == -1)
	{
		last_mouse_p->x = mouse_p->x;
		last_mouse_p->y = mouse_p->y;
		*init_rot = (t_vect3){cam_f.x, cam_f.y, cam_f.z};
	}
	else if (last_mouse_p->y == mouse_p->y && last_mouse_p->x == mouse_p->x)
		return (1);
	return (0);
}

static inline void	center_mouse(t_vect2 *mouse_p, t_vect2 *last_mouse_p,
		t_mlx_data *mlx)
{
	if (mouse_p->x > WIN_WIDTH * 0.5 - 1 || mouse_p->y > WIN_HEIGHT * 0.5 - 1
		|| mouse_p->x < -WIN_WIDTH * 0.5 + 1 || mouse_p->y < -WIN_HEIGHT * 0.5 + 1)
	{
		last_mouse_p->x -= mouse_p->x;
		last_mouse_p->y -= mouse_p->y;
		mouse_p->x = 0;
		mouse_p->y = 0;
		mlx_mouse_move(mlx->mlx, mlx->win, WIN_WIDTH * 0.5, WIN_HEIGHT * 0.5);
	}
}

#endif
