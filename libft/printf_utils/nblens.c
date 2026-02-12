/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nblens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 09:53:34 by lomartin          #+#    #+#             */
/*   Updated: 2025/12/03 21:56:35 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	printf_nblen_base(long nb, char *base, t_printf_data *d)
{
	size_t	baselen;
	size_t	len;

	baselen = ft_strlen(base);
	len = 0;
	if (!nb)
		return (1);
	if (nb < 0)
	{
		nb = -nb;
		len++;
	}
	else if (d->fsign || d->fw)
		len++;
	while (nb)
	{
		nb /= baselen;
		len++;
	}
	return (len);
}

size_t	printf_nblen_base_ul(unsigned long nb, char *base)
{
	size_t	baselen;
	size_t	len;

	baselen = ft_strlen(base);
	len = 0;
	while (nb)
	{
		nb /= baselen;
		len++;
	}
	return (len);
}

void	calc_nblen_min(t_printf_data *d, t_rnumber_data *dn)
{
	if (*d->ffiller == '0' && dn->nb < 0)
		dn->nblen_min = ft_max((long)d->fpadd - 1, (long)d->fprec);
	else if (*d->ffiller == '0')
		dn->nblen_min = ft_max((long)d->fpadd, (long)d->fprec);
	else
		dn->nblen_min = d->fprec;
}

void	err(t_printf_data *d)
{
	d->err = 1;
	if (d->s)
		free(d->s);
	d->s = NULL;
}
