/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 22:49:31 by lomartin          #+#    #+#             */
/*   Updated: 2026/02/14 19:15:04 by lomartin         ###   ########.fr       */
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

unsigned long	get_utime(unsigned long start)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1e6 + tv.tv_usec - start);
}
