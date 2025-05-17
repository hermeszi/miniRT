/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 18:59:17 by myuen             #+#    #+#             */
/*   Updated: 2024/08/03 20:35:52 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*extract_line(t_buffer *buffer, int len)
{
	char	*line;

	line = malloc(len + 1);
	if (!line)
		return (NULL);
	line[0] = '\0';
	ft_strlcat(line, buffer->content + buffer->pos, len + 1);
	line[len] = '\0';
	buffer->pos += len;
	return (line);
}

static char	*list_to_string(t_list *list)
{
	size_t	total_len;
	t_list	*tmp;
	char	*str;

	tmp = list;
	total_len = 0;
	while (tmp)
	{
		total_len += ft_strlen(tmp->content);
		tmp = tmp->next;
	}
	str = malloc(total_len + 1);
	if (str)
	{
		str[0] = '\0';
		while (list)
		{
			ft_strlcat(str, list->content, total_len + 1);
			list = list->next;
		}
	}
	return (str);
}

static int	read_line(t_buffer *buffer, t_list **list, char **str, int fd)
{
	size_t	i;

	buffer->pos = 0;
	buffer->bytes_read = read(fd, buffer->content, BUFFER_SIZE);
	if (buffer->bytes_read == 0)
	{
		if (*list)
			*str = list_to_string(*list);
		else
			*str = NULL;
		gnl_free_list(list);
		return (1);
	}
	else if (buffer->bytes_read < 0)
	{
		gnl_free_list(list);
		buffer->pos = 0;
		buffer->bytes_read = 0;
		i = 0;
		while (i < BUFFER_SIZE)
			buffer->content[i++] = '\0';
		*str = NULL;
		return (1);
	}
	return (0);
}

static int	process_line(t_buffer *buffer, t_list **list, \
	char *newline_pos, char **str)
{
	char	*read_content;

	if (newline_pos)
	{
		read_content = extract_line(buffer, \
			newline_pos - (buffer->content + buffer->pos) + 1);
		if (!read_content || !gnl_add_node(list, read_content))
		{
			free(read_content);
			gnl_free_list(list);
			str = NULL;
			return (1);
		}
		*str = list_to_string(*list);
		gnl_free_list(list);
		return (1);
	}
	else
	{
		read_content = extract_line(buffer, buffer->bytes_read - buffer->pos);
		if (!read_content || !gnl_add_node(list, read_content))
			free(read_content);
		return (0);
	}
}

char	*get_next_line(int fd)
{
	static t_buffer	buffer[MAX_FD];
	t_list			*list;
	char			*ret;
	char			*newline_pos;

	if (fd < 0 || fd >= MAX_FD || BUFFER_SIZE <= 0)
		return (NULL);
	ret = NULL;
	list = NULL;
	newline_pos = NULL;
	while (1)
	{
		if (buffer[fd].pos >= buffer[fd].bytes_read)
		{
			if (read_line(&buffer[fd], &list, &ret, fd))
				return (ret);
		}
		newline_pos = ft_memchr(buffer[fd].content + buffer[fd].pos, '\n', \
			buffer[fd].bytes_read - buffer[fd].pos);
		if (process_line(&buffer[fd], &list, newline_pos, &ret))
			return (ret);
	}
	return (ret);
}
