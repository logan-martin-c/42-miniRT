/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 14:06:14 by lomartin          #+#    #+#             */
/*   Updated: 2025/11/23 19:34:40 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	router(const char **str, va_list ap, t_printf_data *d)
{
	(*str)++;
	parse_flags(str, d);
	if (**str == 's')
		r_str(str, ap, d, NULL);
	else if (**str == 'c')
		r_char(str, ap, d);
	else if (ft_isinset(**str, "diuxX"))
		r_number(str, ap, d, **str);
	else if (**str == 'p')
		r_pointer(str, ap, d);
	else if (**str == '%')
	{
		d->siz += write(1, "%", 1);
		(*str)++;
	}
	else
		d->siz += write(1, "%", 1);
}

void	reader(const char *str, va_list ap, t_printf_data *d)
{
	while (*str)
	{
		if (*str == '%')
			router(&str, ap, d);
		else
		{
			d->len = ft_strclen(str, '%');
			d->siz += write(1, str, d->len);
			str += d->len;
		}
		if (d->err)
			return ;
	}
}

int	ft_printf(const char *str, ...)
{
	va_list			ap;
	t_printf_data	*d;
	int				ret;

	if (!str)
		return (-1);
	ret = 0;
	d = malloc(sizeof(t_printf_data));
	if (!d)
		return (-1);
	d->siz = 0;
	d->err = 0;
	va_start(ap, str);
	reader(str, ap, d);
	ret = d->siz;
	if (d->err)
		ret = -1;
	free(d);
	va_end(ap);
	return (ret);
}
