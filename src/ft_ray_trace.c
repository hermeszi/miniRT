/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ray_trace.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngew <jngew@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 14:13:00 by myuen             #+#    #+#             */
/*   Updated: 2025/07/02 12:23:46 by jngew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

static t_hit	find_closest_hit(t_ray ray, t_scene *scene)
{
	t_object	*current;
	t_hit		closest_hit;
	t_hit		current_hit;

	closest_hit.hit = 0;
	closest_hit.t = INFINITY;
	closest_hit.object = NULL;
	current = scene->objects;
	while (current)
	{
		if (current->type == OBJ_SPHERE)
			current_hit = intersect_sphere(ray, current->data.sphere);
		else if (current->type == OBJ_PLANE)
			current_hit = intersect_plane(ray, current->data.plane);
		else if (current->type == OBJ_CYLINDER)
			current_hit = intersect_cylinder(ray, current->data.cylinder);
		if (current_hit.hit && current_hit.t < closest_hit.t)
		{
			closest_hit = current_hit;
			closest_hit.object = current;
		}
		current = current->next;
	}
	return (closest_hit);
}

t_color	trace_ray(t_ray ray, t_scene *scene)
{
	t_hit	closest_hit;

	closest_hit = find_closest_hit(ray, scene);
	if (closest_hit.hit)
		return (get_hit_color(&closest_hit, scene));
	return (scene->background);
}
