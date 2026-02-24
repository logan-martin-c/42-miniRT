/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multithreading.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 17:17:41 by lomartin          #+#    #+#             */
/*   Updated: 2026/02/21 17:18:11 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
//
#include <pthread.h>
#include <stdint.h>
#include <stdlib.h>
#include <strings.h>

void	*thread_routine(void *data)
{
	t_global_data	*g_data;
	int				task_n;

	g_data = (t_global_data *)data;
	while (!g_data->e_data->stop)
	{
		while (!g_data->e_data->stop && !g_data->e_data->rendering)
			usleep(100);
		while (!g_data->e_data->stop
			&& g_data->e_data->current_task < g_data->e_data->to_do)
		{
			task_n = g_data->e_data->current_task++;
			render_canva(g_data->e_data->tasks[task_n].start,
				g_data->e_data->tasks[task_n].end, &g_data->world,
				&g_data->mlx);
			if (++g_data->e_data->tasks_done == g_data->e_data->to_do)
				g_data->e_data->rendering = false;
		}
	}
	return (NULL);
}

int	init_threads(t_exec_data *e_data, t_global_data *g_data)
{
	unsigned int	i;
	int				nb_max_tasks;

	e_data->nb_threads = sysconf(_SC_NPROCESSORS_ONLN);
	e_data->threads = malloc((e_data->nb_threads) * sizeof(pthread_t));
	if (!e_data->threads)
		return (1);
	ft_bzero(e_data->threads, (e_data->nb_threads) * sizeof(pthread_t));
	i = -1;
	while (++i < e_data->nb_threads)
	{
		if (pthread_create(e_data->threads + i, NULL, thread_routine, g_data))
			return (1);
	}
	nb_max_tasks = ceil((ceil((float)WIN_HEIGHT / (float)RENDERING_SQUARE)
				* (ceil((float)WIN_WIDTH / (float)RENDERING_SQUARE))));
	e_data->tasks = malloc((nb_max_tasks + 1) * sizeof(t_tasks));
	return (0);
}

void	create_tasks(t_exec_data *e_data)
{
	int	yy;
	int	xx;
	int	i;

	yy = 0;
	i = 0;
	while (yy < WIN_HEIGHT)
	{
		xx = 0;
		while (xx < WIN_WIDTH)
		{
			e_data->tasks[i++] = (t_tasks){(t_vect2){xx, yy},
				(t_vect2){ft_min(xx + RENDERING_SQUARE - 1, WIN_WIDTH - 1),
				ft_min(yy + RENDERING_SQUARE - 1, WIN_HEIGHT - 1)}};
			xx += RENDERING_SQUARE;
		}
		yy += RENDERING_SQUARE;
	}
	e_data->tasks_done = 0;
	e_data->current_task = 0;
	e_data->to_do = i;
	e_data->rendering = true;
}
