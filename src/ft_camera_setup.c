/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_camera_setup.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngew <jngew@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 14:13:00 by myuen             #+#    #+#             */
/*   Updated: 2025/07/09 17:18:46 by jngew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

void	init_camera(t_camera *camera)
{
	camera->position = vec3_new(0, 0, 0);
	camera->orientation = vec3_new(0, 0, 1);
	camera->fov = -1;
	camera->right = vec3_new(1, 0, 0);
	camera->up = vec3_new(0, 1, 0);
	camera->rotation = mat3_from_vectors(camera->right,
			camera->up, camera->orientation);
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

void	build_camera_matrix(t_camera *camera)
{
	t_vec3	forward;
	t_vec3	right;
	t_vec3	up;

	forward = camera->orientation;
	right = get_stable_tangent(forward);
	up = vec3_cross(forward, right);
	camera->right = right;
	camera->up = up;
	camera->rotation = mat3_from_vectors(right, up, forward);
}
