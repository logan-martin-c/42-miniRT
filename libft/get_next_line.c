/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 11:45:52 by lomartin          #+#    #+#             */
/*   Updated: 2025/11/28 22:42:29 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_lstdelone_gnl(t_fd_list **lst, t_fd_list *elem)
{
	t_fd_list	*check;

	if (!*lst || !elem)
		return ;
	check = *lst;
	if (check != elem)
	{
		while ((check)->next != elem)
			check = check->next;
		check->next = elem->next;
	}
	else if (!elem->next)
		*lst = NULL;
	else
		*lst = elem->next;
	free(elem);
}

void	ft_lstadd_back_gnl(t_fd_list **lst, int fd)
{
	t_fd_list	*last;
	t_fd_list	*new;

	new = malloc(sizeof(t_fd_list));
	if (!new)
		return ;
	new->fd = fd;
	new->rest[0] = '\0';
	new->next = NULL;
	last = *lst;
	if (!(*lst))
		*lst = new;
	else
	{
		while (last->next)
			last = last->next;
		last->next = new;
	}
	return ;
}

t_fd_list	*lst_get(t_fd_list *fd_list, int fd)
{
	if (!fd_list)
		return (NULL);
	while (fd_list)
	{
		if (fd_list->fd == fd)
			return (fd_list);
		fd_list = fd_list->next;
	}
	return (NULL);
}

int	reader_gnl(t_gnl_data *d, char *buffer, t_fd_list **fd_list, int fd)
{
	while ((!d->curr || !has_eol(d->curr->rest)) && !has_eol(buffer)
		&& (d->read_bytes == BUFFER_SIZE || d->read_bytes == -2))
	{
		d->read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (d->read_bytes == -1)
		{
			if (buffer)
				free(buffer);
			ft_lstdelone_gnl(fd_list, d->curr);
			return (0);
		}
		buffer[d->read_bytes] = '\0';
		if (d->read_bytes)
			d->line = ft_strjoin_gnl(d->line, buffer, 1);
	}
	return (1);
}

char	*get_next_line(int fd)
{
	char				*buffer;
	static t_fd_list	*fd_list = NULL;
	t_gnl_data			d;

	if (!init_vars(&fd_list, &buffer, &d, fd) || !reader_gnl(&d, buffer,
			&fd_list, fd))
		return (NULL);
	free(buffer);
	if (!d.read_bytes && !*d.curr->rest && !d.line)
	{
		ft_lstdelone_gnl(&fd_list, d.curr);
		return (NULL);
	}
	d.line = ft_strjoin_gnl(d.curr->rest, d.line, 2);
	if (!d.line)
	{
		ft_lstdelone_gnl(&fd_list, d.curr);
		return (NULL);
	}
	return (ft_substr_gnl(d.line, d.curr->rest));
}
