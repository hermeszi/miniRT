/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_viewport.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 16:21:07 by myuen             #+#    #+#             */
/*   Updated: 2025/06/21 20:46:50 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

t_vec3 pixel_to_viewport(t_camera *camera, int screen_x, int screen_y)
{
    t_vec3 viewport_dir;
    double u, v;
    double fov_rad, half_angle;
    double angle_x, angle_y;
    
    // Convert to normalized coordinates [-0.5, +0.5]
    u = ((double)screen_x / (double)WIN_WIDTH) - 0.5;
    v = 0.5 - ((double)screen_y / (double)WIN_HEIGHT);
    
    // Calculate the half-angle of the FOV
    fov_rad = degrees_to_radians(camera->fov);
    half_angle = tan(fov_rad / 2.0);
    
    // Calculate the actual angles for this pixel
    angle_x = u * half_angle * ((double)WIN_WIDTH / (double)WIN_HEIGHT);
    angle_y = v * half_angle;
    
    // Create direction using tangent values (this is the key difference!)
    viewport_dir.x = angle_x;
    viewport_dir.y = angle_y;
    viewport_dir.z = 1.0;
    
    return vec3_norm(viewport_dir);
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
