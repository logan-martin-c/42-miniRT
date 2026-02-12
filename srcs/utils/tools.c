/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 22:49:31 by lomartin          #+#    #+#             */
/*   Updated: 2026/02/11 17:02:52 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "sys/time.h"

char	*get_progname(char *av_zero)
{
	char	*progname;

	progname = ft_strrchr(av_zero, '/');
	if (progname)
		return (progname + 1);
	else
		return (av_zero);
}

void	clean_exit(int exit_status, t_global_data *g_data,
		t_parsing_data *p_data)
{
	char	*gnl;

	if (p_data)
	{
		gnl = "";
		while (gnl && p_data->map_fd != -1)
		{
			gnl = get_next_line(p_data->map_fd);
			free(gnl);
		}
	}
	if (g_data->mlx.mlx)
	{
		mlx_do_key_autorepeaton(g_data->mlx.mlx);
		if (g_data->mlx.s_img_data.img)
			mlx_destroy_image(g_data->mlx.mlx, g_data->mlx.s_img_data.img);
		if (g_data->mlx.win)
			mlx_destroy_window(g_data->mlx.mlx, g_data->mlx.win);
		mlx_destroy_display(g_data->mlx.mlx);
		free(g_data->mlx.mlx);
	}
	exit(exit_status);
}

int	win_close(t_global_data *g_data)
{
	clean_exit(0, g_data, NULL);
	return (0);
}

/// @brief get the time in ms
/// @param start start time in ms, set to 0 for real time
/// @return time in ms
unsigned long	get_time(unsigned long start)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1e3 + tv.tv_usec * 1e-3 - start);
}
