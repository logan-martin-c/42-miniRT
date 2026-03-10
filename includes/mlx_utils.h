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

static inline void	my_mlx_pixel_put(t_mlx_data *mlx, t_vect2 pos, int color)
{
	int	*dst;

	if (pos.x < 0 || pos.x >= WIN_WIDTH || pos.y < 0 || pos.y >= WIN_HEIGHT)
		return ;
	dst = (int *)(mlx->s_img_data.addr) + ((int)pos.y * WIN_WIDTH + (int)pos.x);
	*dst = color;
}

static inline t_long_color	get_prev_color(t_vect2 pos, t_long_color *color_tab)
{
	if (pos.x < 0 || pos.x >= WIN_WIDTH || pos.y < 0 || pos.y >= WIN_HEIGHT)
		return ((t_long_color){0, 0, 0, 0});
	return (color_tab[((int)pos.y * LINE_SIZE + (int)pos.x)]);
}

#endif
