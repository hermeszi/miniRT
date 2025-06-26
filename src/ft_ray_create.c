/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ray_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 14:13:00 by myuen             #+#    #+#             */
/*   Updated: 2025/06/26 20:43:11 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

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
