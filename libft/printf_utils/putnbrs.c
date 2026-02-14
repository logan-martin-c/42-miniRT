/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putnbrs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 10:05:13 by lomartin          #+#    #+#             */
/*   Updated: 2026/02/14 18:33:38 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr_base_recursive(long n, t_printf_data *d, t_rnumber_data *dn,
		size_t *len)
{
	int	i;

	if (++dn->i < dn->nblen_min || n > dn->baselen - 1)
		ft_putnbr_base_recursive((n / dn->baselen), d, dn, len);
	i = write(1, dn->set + n % dn->baselen, 1);
	*len = *len + 1;
	(void)i;
}

size_t	printf_putnbr_base(t_rnumber_data *dn, t_printf_data *d)
{
	long			n;
	size_t			len;

	len = 0;
	dn->i = 0;
	n = dn->nb;
	if (dn->u)
		n = (unsigned long)dn->nb;
	dn->baselen = ft_strlen(dn->set);
	if (n < 0)
	{
		n = -n;
		d->siz += write(1, "-", 1);
		if (d->fprecon && d->fprec == dn->nblen)
			dn->m = 1;
	}
	else if (d->fsign || d->fw)
	{
		if (d->fsign)
			len += write(1, "+", 1);
		else
			len += write(1, " ", 1);
	}
	ft_putnbr_base_recursive(n, d, dn, &len);
	return (len);
}

void	ft_putnbr_base_ul_recursive(unsigned long nb, unsigned int baselen,
		char *base, size_t *len)
{
	int	i;

	if (nb > baselen - 1)
		ft_putnbr_base_ul_recursive((nb / baselen), baselen, base, len);
	i = write(1, base + nb % baselen, 1);
	*len = *len + 1;
	(void)i;
}

size_t	printf_putnbr_base_ul(unsigned long nb, char *base)
{
	unsigned int	baselen;
	size_t			len;

	len = 0;
	baselen = ft_strlen(base);
	ft_putnbr_base_ul_recursive(nb, baselen, base, &len);
	return (len);
}
