/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 18:20:30 by lomartin          #+#    #+#             */
/*   Updated: 2026/02/14 18:26:27 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** @brief Write string s to file descriptor fd followed by a newline
** @param s Null-terminated string to write
** @param fd File descriptor
** @return void
*/
void	ft_putendl_fd(char *s, int fd)
{
	size_t	len;
	int		i;

	if (!s)
		return ;
	len = ft_strlen(s);
	i = write(fd, s, len);
	i = write(fd, "\n", 1);
	(void)i;
}
