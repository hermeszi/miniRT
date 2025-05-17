/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 19:00:21 by myuen             #+#    #+#             */
/*   Updated: 2024/08/03 20:36:04 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 256
# endif

# define MAX_FD 1024

typedef struct s_buffer
{
	char	content[BUFFER_SIZE];
	int		pos;
	int		bytes_read;
}	t_buffer;

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}	t_list;

char	*get_next_line(int fd);
int		gnl_add_node(t_list **list, char *content);
void	gnl_free_list(t_list **list);
void	*ft_memchr(const void *s, int c, size_t n);
size_t	ft_strlcat(char *dest, const char *src, size_t size);
size_t	ft_strlen(const char *s);

#endif
