/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 19:00:02 by myuen             #+#    #+#             */
/*   Updated: 2024/08/03 20:36:25 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	unsigned char	val;
	size_t			i;

	if (s)
	{
		val = (unsigned char) c;
		str = (unsigned char *) s;
		i = 0;
		while (i < n)
		{
			if ((unsigned char)str[i] == val)
				return ((void *) str + i);
			i++;
		}
	}
	return (NULL);
}

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (*s++ != '\0')
		len++;
	return (len);
}

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	s_len;
	size_t	d_len;
	size_t	i;

	s_len = ft_strlen(src);
	d_len = ft_strlen(dest);
	if (size <= d_len)
		return (size + s_len);
	i = 0;
	while (src[i] && (d_len + i) < (size - 1))
	{
		dest[d_len + i] = src[i];
		i++;
	}
	dest[d_len + i] = '\0';
	return (d_len + s_len);
}

void	gnl_free_list(t_list **list)
{
	t_list	*tmp;

	while (*list)
	{
		tmp = (*list)->next;
		free((*list)->content);
		free(*list);
		*list = tmp;
	}
}

int	gnl_add_node(t_list **list, char *content)
{
	t_list	*new_node;
	t_list	*last;

	new_node = malloc(sizeof(t_list));
	if (!new_node || !list || !content)
		return (0);
	new_node->content = content;
	new_node->next = NULL;
	if (*list == NULL)
	{
		*list = new_node;
		return (1);
	}
	else
	{
		last = *list;
		while (last->next != NULL)
			last = last->next;
		last->next = new_node;
		return (1);
	}
}

/*
char	*ft_strncpy(char *dst, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dst[i] = '\0';
		i++;
	}
	return (dst);
}*/
