/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 09:41:13 by lomartin          #+#    #+#             */
/*   Updated: 2025/11/13 10:55:22 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	init_flags(t_printf_data *d)
{
	d->falt = 0;
	d->fpadd = 0;
	d->fpaddleft = 0;
	d->fprec = 0;
	d->fprecon = 0;
	d->fsign = 0;
	d->ffiller = " ";
	d->fw = 0;
}

static void	parse_f_padd_prec(const char **str, t_printf_data *d)
{
	size_t	count;
	char	*cpy;
	int		*var;

	count = 0;
	var = &(d->fpadd);
	if (**str == '.')
	{
		d->fprecon = 1;
		var = &(d->fprec);
		(*str)++;
	}
	while (ft_isdigit(*(*str + count)))
		count++;
	cpy = ft_substr((*str), 0, count);
	*var = ft_atoi(cpy);
	free(cpy);
	(*str) += count;
}

void	parse_flags(const char **str, t_printf_data *d)
{
	init_flags(d);
	while (ft_isinset(**str, " .-+#0123456789"))
	{
		if ((ft_isdigit(**str) && **str != '0') || **str == '.')
			parse_f_padd_prec(str, d);
		else
		{
			if (**str == '0')
				d->ffiller = "0";
			else if (**str == '#')
				d->falt = 1;
			else if (**str == '+')
				d->fsign = 1;
			else if (**str == '-')
				d->fpaddleft = 1;
			else if (**str == ' ')
				d->fw = 1;
			(*str)++;
		}
	}
}
