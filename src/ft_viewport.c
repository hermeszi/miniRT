/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_viewport.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 16:21:07 by myuen             #+#    #+#             */
/*   Updated: 2025/06/23 20:42:13 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

static double	calculate_viewport_scale(double fov_rad)
{
	return (tan(fov_rad / 2.0) * VIEWPORT_DISTANCE);
}

static double	normalized_to_viewport_x(double u, double viewport_scale)
{
	double	aspect_ratio;

	aspect_ratio = (double)WIN_WIDTH / (double)WIN_HEIGHT;
	return (u * viewport_scale * aspect_ratio);
}

static double	normalized_to_viewport_y(double v, double viewport_scale)
{
	return (v * viewport_scale);
}

static void	pixel_to_normalized(int screen_x, int screen_y, double *u, double *v)
{
	*u = ((double)screen_x / (double)WIN_WIDTH) - 0.5;
	*v = 0.5 - ((double)screen_y / (double)WIN_HEIGHT);
}

t_vec3	pixel_to_viewport(t_camera *camera, int screen_x, int screen_y)
{
	t_vec3	viewport_dir;
	double	u;
	double	v;
	double	viewport_scale;
	double	fov_rad;

	pixel_to_normalized(screen_x, screen_y, &u, &v);
	fov_rad = degrees_to_radians(camera->fov);
	viewport_scale = calculate_viewport_scale(fov_rad);
	viewport_dir.x = normalized_to_viewport_x(u, viewport_scale);
	viewport_dir.y = normalized_to_viewport_y(v, viewport_scale);
	viewport_dir.z = VIEWPORT_DISTANCE;
	return (vec3_norm(viewport_dir));
}

// t_vec3	pixel_to_viewport(int screen_x, int screen_y, t_viewport viewport)
// {
// 	t_vec3	viewport_point;
// 	double	h;
// 	double	v;

// 	h = (double)screen_x / (double)WIN_WIDTH;
// 	v = (double)screen_y / (double)WIN_HEIGHT;

// 	viewport_point.x = (h - 0.5) * viewport.width;
// 	viewport_point.y = (0.5 - v) * viewport.height;
// 	viewport_point.z = viewport.distance;

// 	return (viewport_point);
// }

/*
Pixel-to-Viewport Conversion

Step 1: Normalize to [0,1] range
u = screen_x / screen_width
v = screen_y / screen_height

Step 2: Convert to 3D viewport coordinates
viewport_x = (u - 0.5) × viewport_width
viewport_y = (0.5 - v) × viewport_height    ← Note: Y flip
viewport_z = viewport_distance

Step 3: Viewport Dimensions calalation
// Option A: Fixed Distance
viewport.distance = 1.0;
viewport.width = 2.0 * tan(fov_radians / 2.0);

// Option B: Fixed Size
viewport.width = 1.0;
viewport.distance = 1.0 / (2.0 * tan(fov_radians / 2.0));
*/
