/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_hit_color.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 14:13:00 by myuen             #+#    #+#             */
/*   Updated: 2025/06/28 17:14:36 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

static t_ray	build_shadow_ray(t_hit *hit, t_scene *scene)
{
	t_ray	shadow_ray;

	shadow_ray.origin = vec3_add(hit->point,
		vec3_multiply(hit->normal, 1e-4));
	shadow_ray.direction = vec3_norm(vec3_sub(scene->light.position, hit->point));
	return (shadow_ray);
}
static int	is_in_shadow(t_ray shadow_ray, double light_dist, t_hit *hit, t_scene *scene)
{
	t_object	*current;
	t_hit		shadow_hit;

	current = scene->objects;
	while (current)
	{
		if (current == hit->object)
		{
			current = current->next;
			continue ;
		}
		if (current->type == OBJ_SPHERE)
			shadow_hit = intersect_sphere(shadow_ray, current->data.sphere);
		else if (current->type == OBJ_PLANE)
			shadow_hit = intersect_plane(shadow_ray, current->data.plane);
		else if (current->type == OBJ_CYLINDER)
		{
			; // add cylinder
		}
		if (shadow_hit.hit && shadow_hit.t < light_dist)
			return (1);
		current = current->next;
	}
	return (0);
}

t_color	get_hit_color(t_hit *closest_hit, t_scene *scene)
{
	t_ray	shadow_ray;
	double	light_dist;
	int		in_shadow;

	shadow_ray = build_shadow_ray(closest_hit, scene);
	light_dist = vec3_length(vec3_sub(scene->light.position, closest_hit->point));
	in_shadow = is_in_shadow(shadow_ray, light_dist, closest_hit, scene);
	return (calculate_shading(closest_hit, scene, in_shadow));
}
