/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_fd_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 13:24:15 by lomartin          #+#    #+#             */
/*   Updated: 2025/11/23 20:00:44 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** @brief Output integer n in given base to fd
** @param n Integer to print
** @param base Base to convert n to
** @param fd File descriptor for output
** @return Written character count
*/
size_t	ft_putnbr_base_fd(long n, char *base, int fd)
{
	char	c;
	size_t	len;
	size_t	baselen;

	len = 0;
	if (!ft_isvalidbase(base))
		return (0);
	baselen = ft_strlen(base);
	if (n < 0)
	{
		n = -n;
		len += write(fd, "-", 1);
	}
	if ((unsigned long)n >= baselen)
		len += ft_putnbr_base_fd(n / baselen, base, fd);
	c = base[n % baselen];
	len += write(fd, &c, 1);
	return (len);
}
