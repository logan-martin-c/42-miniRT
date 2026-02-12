/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 11:45:54 by lomartin          #+#    #+#             */
/*   Updated: 2025/11/27 15:22:16 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strclen_gnl(const char *str, char c)
{
	int	len;

	len = 0;
	while (str[len] && str[len] != c)
		len++;
	return (len);
}

char	*ft_substr_gnl(char *s, char rest[])
{
	char	*substring;
	long	size;
	long	i;
	long	j;

	if (!s)
		return (NULL);
	size = ft_strclen_gnl(s, '\n') + 1;
	substring = malloc((size + 1) * sizeof(char));
	if (!substring)
		return (NULL);
	i = -1;
	while (s[++i] && i < size)
		substring[i] = s[i];
	substring[i] = '\0';
	j = -1;
	while (s[i])
		rest[++j] = s[i++];
	rest[j + 1] = '\0';
	free(s);
	return (substring);
}

char	*ft_strjoin_gnl(char *s1, char *s2, int to_free)
{
	t_join_data	jd;

	if (!s1 || !s2)
		to_free = 0;
	if (!s2)
		s2 = "";
	if (!s1)
		s1 = "";
	jd.len = ft_strclen_gnl(s1, '\0') + ft_strclen_gnl(s2, '\0');
	jd.dest = malloc((jd.len + 1) * sizeof(char));
	if (!jd.dest)
		return (NULL);
	jd.i = -1;
	while (s1[++jd.i])
		*(jd.dest++) = s1[jd.i];
	jd.i = -1;
	while (s2[++jd.i])
		*(jd.dest++) = s2[jd.i];
	if (to_free == 1)
		free(s1);
	if (to_free == 2)
		free(s2);
	*jd.dest = '\0';
	return (jd.dest - jd.len);
}

int	has_eol(char *str)
{
	while (*str)
	{
		if (*str == '\n')
			return (1);
		str++;
	}
	return (0);
}

int	init_vars(t_fd_list **fd_list, char **buffer, t_gnl_data *d, int fd)
{
	if (fd < 0)
		return (0);
	if (!*fd_list || !lst_get(*fd_list, fd))
		ft_lstadd_back_gnl(fd_list, fd);
	*buffer = malloc(BUFFER_SIZE + 1);
	if (!*buffer)
		return (0);
	*buffer[0] = '\0';
	d->line = NULL;
	d->read_bytes = -2;
	d->curr = NULL;
	d->curr = lst_get(*fd_list, fd);
	if (!d->curr)
	{
		free(buffer);
		return (0);
	}
	return (1);
}
