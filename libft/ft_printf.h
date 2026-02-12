/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 11:15:55 by lomartin          #+#    #+#             */
/*   Updated: 2025/11/23 19:56:11 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "libft.h"
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_printf_data
{
	va_list			ap;
	char			*s;
	char			c;
	int				siz;
	int				err;
	size_t			len;
	int				fpadd;
	int				fpaddleft;
	char			*ffiller;
	int				falt;
	int				fsign;
	int				fprec;
	int				fprecon;
	int				fw;
}					t_printf_data;

typedef struct s_rstr_data
{
	int				prec;
	int				padd;
}					t_rstr_data;

typedef struct s_rnumber_data
{
	char			*set;
	int				u;
	long			nb;
	long			nblen;
	long			nblen_min;
	unsigned int	baselen;
	int				i;
	int				m;
}					t_rnumber_data;

// UTILS
void				err(t_printf_data *d);
size_t				printf_nblen_base(long nb, char *base, t_printf_data *d);
size_t				printf_nblen_base_ul(unsigned long nb, char *base);
void				calc_nblen_min(t_printf_data *d, t_rnumber_data *dn);
// PUTNBRS
size_t				printf_putnbr_base(t_rnumber_data *dn, t_printf_data *d);
size_t				printf_putnbr_base_ul(unsigned long nb, char *base);
// PARSER
void				parse_flags(const char **str, t_printf_data *d);
// ROUTER
void				r_str(const char **str, va_list ap, t_printf_data *d,
						char *self);
void				r_char(const char **str, va_list ap, t_printf_data *d);
void				r_number(const char **str, va_list ap, t_printf_data *d,
						char flag);
void				r_number2(t_printf_data *d, t_rnumber_data *dn, char flag);
void				r_pointer(const char **str, va_list ap, t_printf_data *d);
// PADDING
void				calc_padd_prec(t_printf_data *d, t_rstr_data *p, char *arg);
int					put_padd_before(t_printf_data *d, int len, char mode);
int					put_padd_after(t_printf_data *d, int len);

#endif
