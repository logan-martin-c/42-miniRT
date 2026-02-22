/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 15:38:04 by lomartin          #+#    #+#             */
/*   Updated: 2026/02/12 19:24:11 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

// ft_itoa utils
typedef struct s_itoa_data
{
	int				len;
	int				alloc;
	int				neg;
	int				depth;
}					t_itoa_data;

// ft_split utils
typedef struct s_split_data
{
	int				i;
	int				n;
	int				len;
}					t_split_data;

// list struct
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

// Protos
long				ft_abs(long n);
float				ft_abs_float(float n);
double				ft_abs_double(double n);
double				ft_atod(const char *str);
float				ft_atof(const char *str);
int					ft_atoi(const char *str);
int					ft_atoi_base(const char *str, char *base);
long				ft_atol(const char *str);
void				ft_free_strs(char **strs);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_isspace(int c);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isdigit_str(char *str);
int					ft_isfloat_str(char *str);
int					ft_isalnum(int c);
int					ft_isinset(char c, const char *set);
int					ft_toupper(int c);
int					ft_tolower(int c);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strnstr(const char *haystack, const char *needle,
						size_t n);
char				*ft_strchr(const char *str, int c);
char				*ft_strrchr(const char *str, int c);
size_t				ft_strlen(char const *str);
int					ft_strcharsetlen(const char *str, char *charset);
size_t				ft_strlcpy(char *dest, const char *src, size_t n);
size_t				ft_strlcat(char *dest, char *src, unsigned int size);
void				*ft_memset(void *area, int c, size_t size);
void				*ft_memset_int(void *area, int c, size_t n);
void				ft_bzero(void *area, size_t size);
void				*ft_memcpy(void *dest, const void *src, size_t size);
void				*ft_memccpy(void *dest, const void *src, char c,
						size_t size);
void				*ft_memmove(void *dest, const void *src, size_t size);
void				*ft_memchr(const void *area, int c, size_t n);
void				*ft_calloc(size_t n, size_t size);
char				*ft_strdup(const char *src);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strjoin_mult(unsigned int count, ...);
char				*ft_strtrim(const char *s1, const char *set);
char				**ft_split(const char *s, char c);
char				**ft_split_charset(const char *s, char *charset);
char				*ft_itoa(int n);
char				*ft_itoa_pure(int n, char *nb);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
size_t				ft_putnbr_base_fd(long n, char *base, int fd);
size_t				ft_putnbr_fd(int n, int fd);
void				ft_lstadd_front(t_list **lst, t_list *new);
void				ft_lstadd_back(t_list **lst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));
t_list				*ft_lstnew(void *content);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstdelone_fr(t_list **lst, t_list *elem,
						void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
int					ft_memcmp(const void *s1, const void *s2, size_t n);
long				ft_pow(int n, int pow);
int					ft_strclen(const char *str, char c);
int					ft_isvalidbase(char *base);
size_t				ft_nblen(long nb);
size_t				ft_nblen_base(long nb, char *base);
size_t				ft_nblen_base_ul(unsigned long nb, char *base);
long				ft_min_var(unsigned int count, ...);
long				ft_max_var(unsigned int count, ...);
long				ft_min(long a, long b);
float				ft_min_float(float a, float b);
long				ft_max(long a, long b);
float				ft_max_float(float a, float b);
int					ft_printf(const char *str, ...);
char				*get_next_line(int fd);
void				*ft_print_memory(void *addr, unsigned int size);

#endif
