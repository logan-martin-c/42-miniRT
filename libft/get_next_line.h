/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 11:45:48 by lomartin          #+#    #+#             */
/*   Updated: 2025/12/09 20:20:38 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

# include <stdlib.h>
# include <unistd.h>
// Min value is 2, otherwise it can't handle an opened file.
# define HANDLED_FD 2

// DATA
typedef struct s_fd_list
{
	int					fd;
	char				rest[BUFFER_SIZE + 1];
	struct s_fd_list	*next;
}						t_fd_list;
typedef struct s_gnl_data
{
	long				read_bytes;
	char				*line;
	int					memz;
	t_fd_list			*curr;
}						t_gnl_data;
typedef struct s_join_data
{
	size_t				len;
	char				*dest;
	long				i;
}						t_join_data;

// UTILS
char					*ft_substr_gnl(char *s, char rest[]);
char					*ft_strjoin_gnl(char *s1, char *s2, int to_free);
int						has_eol(char *str);
char					*get_next_line(int fd);
int						init_vars(t_fd_list **fd_list, char **buffer,
							t_gnl_data *d, int fd);
t_fd_list				*lst_get(t_fd_list *fd_list, int fd);
void					ft_lstadd_back_gnl(t_fd_list **lst, int fd);

#endif
