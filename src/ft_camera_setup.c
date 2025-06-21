/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_camera_setup.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 14:13:00 by myuen             #+#    #+#             */
/*   Updated: 2025/06/21 18:34:50 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

void	init_camera(t_camera *camera)
{
	camera->position = vec3_new(0, 0, 0);
	camera->orientation = vec3_new(0, 0, 1);  // Default: looking forward
	camera->fov = -1;  // Trigger Error
	camera->right = vec3_new(1, 0, 0);    // Default: X-axis
	camera->up = vec3_new(0, 1, 0);       // Default: Y-axis
	camera->rotation = mat3_from_vectors(camera->right, camera->up, camera->orientation);
}
/*
** Builds a complete orthonormal coordinate system for the camera.
** Takes the orientation vector from the .rt file and constructs
** the right and up vectors to form a proper 3D basis.
**
** The mathematical approach:
** 1. Forward = orientation (already normalized from parsing)
** 2. Right = Forward × WorldUp (cross product gives perpendicular vector)
** 3. Up = Right × Forward (ensures perfect orthogonality)
*/

/*Handle edge case: camera looking straight up or down
*/
static t_vec3	handle_camera_straight_up_down(t_vec3 forward)
{
	t_vec3	world_right;
	
	world_right = vec3_new(1, 0, 0);
	return (vec3_norm(vec3_cross(world_right, forward)));
}

void	build_camera_matrix(t_camera *camera)
{
	t_vec3	world_up;
	t_vec3	forward;
	t_vec3	right;
	t_vec3	up;

	forward = camera->orientation;
	world_up = vec3_new(0, 1, 0);
	if (fabs(vec3_dot(forward, world_up)) > 0.99)
		right = handle_camera_straight_up_down(forward);
	else
		right = vec3_norm(vec3_cross(world_up, forward)); 
	printf("Camera right vector: (%.1f, %.1f, %.1f)\n", right.x, right.y, right.z);
	up = vec3_cross(forward, right);
	printf("Camera up vector: (%.1f, %.1f, %.1f)\n", up.x, up.y, up.z);
	camera->right = right;
	camera->up = up;
	camera->rotation = mat3_from_vectors(right, up, forward);
}
