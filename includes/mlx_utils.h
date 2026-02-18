/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 09:32:16 by lomartin          #+#    #+#             */
/*   Updated: 2026/02/17 09:33:42 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_UTILS_H
# define MLX_UTILS_H

static inline void	my_mlx_pixel_put(t_mlx_data *mlx, t_pos_xyz pos, int color)
{
	char	*dst;

	// int		index;
	if (pos.x < 0 || pos.x >= WIN_WIDTH || pos.y < 0 || pos.y >= WIN_HEIGHT)
		return ;
	// index = (int)pos.y * WIN_WIDTH + (int)pos.x;
	// if (!(index < 0 || index > WIN_HEIGHT
	// 		* WIN_WIDTH))
	// {
	// 	if (vars->z_buffer[index] > (int)pos.z)
	// 		return ;
	// 	vars->z_buffer[index] = (int)pos.z;
	// }
	dst = mlx->s_img_data.addr + ((int)pos.y * LINE_SIZE + (int)pos.x * BPP);
	*(unsigned int *)dst = color;
}

static inline int	get_prev_color(t_pos_xyz pos, t_mlx_data *mlx)
{
	if (pos.x < 0 || pos.x >= WIN_WIDTH || pos.y < 0 || pos.y >= WIN_HEIGHT)
		return (0);
	return (mlx->s_img_data.addr[((int)pos.y * LINE_SIZE + (int)pos.x * BPP)]);
}

#endif