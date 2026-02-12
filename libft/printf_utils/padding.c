/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padding.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 10:24:01 by lomartin          #+#    #+#             */
/*   Updated: 2025/12/03 21:57:05 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	calc_padd_prec(t_printf_data *d, t_rstr_data *p, char *arg)
{
	size_t	strlen;

	strlen = ft_strlen(arg);
	if (d->fprecon)
	{
		p->prec = ft_min(strlen, d->fprec);
		p->padd = d->fpadd - p->prec;
	}
	else
	{
		p->prec = strlen;
		p->padd = d->fpadd - p->prec;
	}
}

int	put_padd_before(t_printf_data *d, int len, char mode)
{
	if (mode == 's')
		d->ffiller = " ";
	if (mode == 'n' && *d->ffiller == '0')
		return (len);
	if (d->fpadd && !d->fpaddleft)
	{
		while (--len >= 0)
			d->siz += write(1, d->ffiller, 1);
	}
	return (len);
}

int	put_padd_after(t_printf_data *d, int len)
{
	if (d->fpaddleft && d->fpadd)
	{
		while (--len >= 0)
			d->siz += write(1, " ", 1);
	}
	return (len);
}
