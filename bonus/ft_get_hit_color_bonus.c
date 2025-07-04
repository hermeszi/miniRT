/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_hit_color_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 14:13:00 by myuen             #+#    #+#             */
/*   Updated: 2025/07/04 19:48:46 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt_bonus.h"

static t_ray	build_shadow_ray(t_hit *hit, t_scene *scene)
{
	t_ray	shadow_ray;

	shadow_ray.origin = vec3_add(hit->point,
			vec3_multiply(hit->normal, EPSILON));
	shadow_ray.direction = vec3_norm(vec3_sub(scene->light.position,
				hit->point));
	return (shadow_ray);
}

static int	is_in_shadow(t_ray shadow_ray, double light_dist,
				t_hit *hit, t_scene *scene)
{
	t_object	*curr;
	t_hit		shadow_hit;

	curr = scene->objects;
	while (curr)
	{
		if (curr == hit->object)
		{
			curr = curr->next;
			continue ;
		}
		shadow_hit.hit = 0;
		if (curr->type == OBJ_SPHERE)
			shadow_hit = intersect_sphere(shadow_ray, curr->u_data.sphere);
		else if (curr->type == OBJ_PLANE)
			shadow_hit = intersect_plane(shadow_ray, curr->u_data.plane);
		else if (curr->type == OBJ_CYLINDER)
			shadow_hit = intersect_cylinder(shadow_ray, curr->u_data.cylinder);
		if (shadow_hit.hit && shadow_hit.t < light_dist)
			return (1);
		curr = curr->next;
	}
	return (0);
}

t_color	get_hit_color(t_hit *closest_hit, t_scene *scene)
{
	t_ray	shadow_ray;
	double	light_dist;
	int		in_shadow;

	shadow_ray = build_shadow_ray(closest_hit, scene);
	light_dist = vec3_length(vec3_sub(scene->light.position,
				closest_hit->point));
	in_shadow = is_in_shadow(shadow_ray, light_dist, closest_hit, scene);
	return (calculate_shading(closest_hit, scene, in_shadow));
}
