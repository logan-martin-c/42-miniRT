/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 18:26:31 by lomartin          #+#    #+#             */
/*   Updated: 2025/11/23 18:54:16 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** @brief Output integer n to given file descriptor
** @param n Integer to print
** @param fd File descriptor
** @return Written character count
*/
size_t	ft_putnbr_fd(int n, int fd)
{
	char	c;
	size_t	len;

	len = 0;
	if (n == -2147483648)
		return (write(fd, "-2147483648", 11));
	if (n < 0)
	{
		n = -n;
		len += write(fd, "-", 1);
	}
	if (n > 9)
		len += ft_putnbr_fd(n / 10, fd);
	c = n % 10 + '0';
	len += write(fd, &c, 1);
	return (len);
}
