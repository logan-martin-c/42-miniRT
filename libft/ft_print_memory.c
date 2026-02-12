/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_memory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 09:54:11 by lomartin          #+#    #+#             */
/*   Updated: 2025/12/09 11:13:55 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_print_addr(unsigned long laddr)
{
	int				n;
	unsigned char	catch;
	char			*hex;

	n = 7;
	hex = "0123456789abcdef";
	while (n >= 0)
	{
		catch = (laddr >> 8 * n) & 255;
		write(1, hex + (catch / 16), 1);
		write(1, hex + (catch % 16), 1);
		n--;
	}
	write(1, ": ", 2);
}

void	ft_print_hex(char *caddr, unsigned long laddr, unsigned long max)
{
	int		n;
	char	*hex;

	n = 0;
	hex = "0123456789abcdef";
	while (n < 16 && laddr + n < max)
	{
		write(1, hex + ((unsigned char)(caddr[n]) / 16), 1);
		write(1, hex + ((unsigned char)(caddr[n]) % 16), 1);
		if (n % 2 == 1)
			write(1, " ", 1);
		n++;
	}
	while (n < 16)
	{
		write(1, "  ", 2);
		if (n % 2 == 1)
			write(1, " ", 1);
		n++;
	}
}

void	ft_print_char(char *caddr, unsigned long laddr, unsigned long max)
{	
	int	n;

	n = 0;
	while (n < 16 && laddr + n < max)
	{
		if ((char)(caddr[n]) >= 32 && (char)(caddr[n]) != 127)
			write(1, caddr + n, 1);
		else
			write(1, ".", 1);
		n++;
	}
}

void	*ft_print_memory(void *addr, unsigned int size)
{
	unsigned int	i;
	unsigned long	laddr;
	char			*caddr;
	unsigned long	max;

	i = 0;
	while (i < size)
	{
		laddr = (unsigned long)(addr + i);
		ft_print_addr(laddr);
		caddr = (char *)(addr + i);
		max = (unsigned long) addr + size;
		ft_print_hex(caddr, laddr, max);
		ft_print_char(caddr, laddr, max);
		write(1, "\n", 1);
		i += 16;
	}
	return (addr);
}
