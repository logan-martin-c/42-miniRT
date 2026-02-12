/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 18:20:30 by lomartin          #+#    #+#             */
/*   Updated: 2025/11/23 11:51:51 by lomartin         ###   ########.fr       */
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

	if (!s)
		return ;
	len = ft_strlen(s);
	write(fd, s, len);
	write(fd, "\n", 1);
}
