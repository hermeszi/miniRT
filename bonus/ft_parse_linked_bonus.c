/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_linked_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 10:56:57 by jngew             #+#    #+#             */
/*   Updated: 2025/07/04 19:49:24 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt_bonus.h"

t_object	*last_obj(t_object *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

int	num_of_obj(t_object *lst)
{
	int	len;

	len = 0;
	while (lst)
	{
		lst = lst->next;
		len++;
	}
	return (len);
}

void	object_add_end(t_object **lst, t_object *new)
{
	t_object	*last;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = last_obj(*lst);
	last->next = new;
}

void	free_objects(t_object *lst)
{
	t_object	*temp;

	while (lst)
	{
		temp = lst->next;
		free (lst);
		lst = temp;
	}
}
