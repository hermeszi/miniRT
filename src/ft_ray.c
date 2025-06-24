/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ray.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 14:13:00 by myuen             #+#    #+#             */
/*   Updated: 2025/06/24 20:41:36 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

// t_ray	create_ray(t_vec3 origin, t_vec3 vp_point)
// {
// 	t_ray	ray;

// 	ray.origin = origin;
// 	ray.direction = vec3_norm(vp_point);
// 	return (ray);
// }

t_ray create_ray(t_camera *camera, t_viewport *viewport, int pixel_x, int pixel_y)
{
	t_ray	ray;
	t_vec3	viewport_dir;
	t_vec3	world_dir;

	viewport_dir = pixel_to_viewport(viewport, pixel_x, pixel_y);
	world_dir = camera_to_world_direction(camera, viewport_dir);
	ray.origin = camera->position;
	ray.direction = vec3_norm(world_dir);
	return (ray);
}

t_color	get_hit_color(t_hit *closest_hit, t_scene *scene)
{
	int			in_shadow;
	double		light_dist;
	t_ray		shadow_ray;
	t_hit		shadow_hit;
	t_object	*current;

	in_shadow = 0;
	shadow_ray.origin = vec3_add(closest_hit->point,
		vec3_multiply(closest_hit->normal, 1e-4));
	shadow_ray.direction = vec3_norm(vec3_sub(scene->light.position,
		closest_hit->point));
	light_dist = vec3_length(vec3_sub(scene->light.position,
		closest_hit->point));
	current = scene->objects;
	while (current)
	{
		if (current == closest_hit->object)
		{
			current = current->next;
			continue ;
		}
		if (current->type == OBJ_SPHERE)
		{
			shadow_hit = intersect_sphere(shadow_ray, current->data.sphere);
			if (shadow_hit.hit && shadow_hit.t < light_dist)
			{
				in_shadow = 1;
				break ;
			}
		}
		else if (current->type == OBJ_PLANE)
		{
			shadow_hit = intersect_plane(shadow_ray, current->data.plane);
			if (shadow_hit.hit && shadow_hit.t < light_dist)
			{
				in_shadow = 1;
				break ;
			}
		}
		// Add else-if blocks here for planes and cylinders
		current = current->next;
	}
	return (calculate_shading(closest_hit, scene, in_shadow));
}


t_color	trace_ray(t_ray ray, t_scene *scene)
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
		{
			current_hit = intersect_sphere(ray, current->data.sphere);
			if (current_hit.hit && current_hit.t < closest_hit.t)
			{
				closest_hit = current_hit;
				closest_hit.object = current;
			}
		}
		else if (current->type == OBJ_PLANE)
		{
			current_hit = intersect_plane(ray, current->data.plane);
			if (current_hit.hit && current_hit.t < closest_hit.t)
			{
				closest_hit = current_hit;
				closest_hit.object = current;
			}
		}
		else if (current->type == OBJ_CYLINDER)
		{

		}
		current = current->next;
	}
	if (closest_hit.hit)
		return (get_hit_color(&closest_hit, scene));
	return (scene->background);
}
