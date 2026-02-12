/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   router.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 12:05:04 by lomartin          #+#    #+#             */
/*   Updated: 2025/12/03 21:57:32 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	r_str(const char **str, va_list ap, t_printf_data *d, char *self)
{
	char		*arg;
	t_rstr_data	*p;

	arg = self;
	if (!arg)
		arg = va_arg(ap, char *);
	if (!arg)
	{
		if ((d->fprec >= 6 || !d->fprecon))
			return (r_str(str, ap, d, "(null)"));
		(*str)++;
		return ;
	}
	d->s = ft_strdup(arg);
	p = malloc(sizeof(t_rstr_data));
	if (!d->s || !p)
		return (err(d));
	calc_padd_prec(d, p, d->s);
	p->padd = put_padd_before(d, p->padd, 's');
	d->siz += write(1, d->s, p->prec);
	p->padd = put_padd_after(d, p->padd);
	(*str)++;
	free(p);
	free(d->s);
	return ;
}

void	r_char(const char **str, va_list ap, t_printf_data *d)
{
	if (d->fpadd && !d->fpaddleft)
	{
		while (--d->fpadd)
			d->siz += write(1, " ", 1);
	}
	d->c = va_arg(ap, int);
	write(1, &d->c, 1);
	if (d->fpaddleft && d->fpadd)
	{
		while (--d->fpadd)
			d->siz += write(1, " ", 1);
	}
	(*str)++;
	d->siz++;
}

void	r_number2(t_printf_data *d, t_rnumber_data *dn, char flag)
{
	if (dn->nb < 0 && d->fprecon && d->fprec >= dn->nblen)
		dn->m = 1;
	if (d->fprecon)
	{
		if (!dn->nb && d->fpadd && *d->ffiller == '0' && !d->fprec)
			d->fpadd++;
		d->ffiller = " ";
	}
	put_padd_before(d, d->fpadd - dn->nblen - ft_max(d->fprec - dn->nblen, 0)
		- dn->m, 'n');
	if (ft_isinset(flag, "xX") && d->falt && dn->nb)
	{
		d->siz += write(1, "0", 1);
		d->siz += write(1, &flag, 1);
	}
	calc_nblen_min(d, dn);
	if (!(d->fprecon && !dn->nb && !d->fprec))
		d->siz += printf_putnbr_base(dn, d);
	else
		dn->nblen = 0;
	put_padd_after(d, d->fpadd - dn->nblen - ft_max(d->fprec - dn->nblen, 0)
		- dn->m);
}

void	r_number(const char **str, va_list ap, t_printf_data *d, char flag)
{
	t_rnumber_data	*dn;

	dn = malloc(sizeof(t_rnumber_data));
	dn->m = 0;
	dn->u = 1;
	if (ft_isinset(flag, "di"))
	{
		dn->nb = va_arg(ap, int);
		dn->set = "0123456789";
		dn->u = 0;
	}
	else
	{
		dn->nb = va_arg(ap, unsigned int);
		if (flag == 'u')
			dn->set = "0123456789";
		if (flag == 'x')
			dn->set = "0123456789abcdef";
		if (flag == 'X')
			dn->set = "0123456789ABCDEF";
	}
	dn->nblen = printf_nblen_base(dn->nb, dn->set, d);
	r_number2(d, dn, flag);
	free(dn);
	(*str)++;
}

void	r_pointer(const char **str, va_list ap, t_printf_data *d)
{
	void	*addr;
	int		nblen;

	addr = va_arg(ap, void *);
	nblen = printf_nblen_base_ul((unsigned long)addr, "0123456789abcdef");
	if (!addr)
	{
		r_str(str, ap, d, "(nil)");
		return ;
	}
	if (d->fpadd && !d->fpaddleft)
	{
		while (--(d->fpadd) - nblen - 2 >= 0)
			d->siz += write(1, " ", 1);
	}
	ft_putstr_fd("0x", 1);
	d->siz += printf_putnbr_base_ul((unsigned long)addr, "0123456789abcdef")
		+ 2;
	if (d->fpaddleft && d->fpadd)
	{
		while (--d->fpadd - nblen - 2 >= 0)
			d->siz += write(1, " ", 1);
	}
	(*str)++;
}
