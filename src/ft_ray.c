/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ray.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 14:13:00 by myuen             #+#    #+#             */
/*   Updated: 2025/06/12 20:11:54 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

t_ray	create_ray(t_vec3 origin, t_vec3 direction)
{
	t_ray	ray;

	ray.origin = origin;
	ray.direction = vec3_norm(direction);
	return (ray);
}

t_color	trace_ray(t_ray ray, t_scene *scene)
{
	t_object	*current;
	t_hit		closest_hit;
	t_hit		current_hit;

	closest_hit.hit = 0;
	closest_hit.t = INFINITY;
	current = scene->objects;
	while (current)
	{
		if (current->type == OBJ_SPHERE)
		{
			current_hit = intersect_sphere(ray, current->data.sphere);
			if (current_hit.hit && current_hit.t < closest_hit.t)
			{
				closest_hit = current_hit;
			}
		}
		else if (current->type == OBJ_PLANE)
		{

		}
		else if (current->type == OBJ_CYLINDER)
		{

		}
		current = current->next;
	}
	if (closest_hit.hit)
		return (closest_hit.color);
	return (scene->background);
}
