/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_linked.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngew <jngew@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 10:56:57 by jngew             #+#    #+#             */
/*   Updated: 2025/07/09 17:34:54 by jngew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

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

int	parse_vector(char *str, t_vec3 *vec)
{
	char	**coords;
	double	x;
	double	y;
	double	z;

	coords = ft_split(str, ',');
	if (!coords)
		return (print_error("Memory allocation failed during parsing."));
	if (!coords[0] || !coords[1] || !coords[2] || coords[3])
		return (pr_er(coords, "Invalid vector format: must be x,y,z"));
	if (get_validated_double(coords[0], &x) != 0
		|| get_validated_double(coords[1], &y) != 0
		|| get_validated_double(coords[2], &z) != 0)
		return (pr_er(coords, "Invalid number in vector definition."));
	vec->x = x;
	vec->y = y;
	vec->z = z;
	free_tokens(coords);
	return (0);
}
