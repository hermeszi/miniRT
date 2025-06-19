/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_camera_transform.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 14:13:00 by myuen             #+#    #+#             */
/*   Updated: 2025/06/17 16:33:12 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

/*
** Transforms a viewport-space direction vector into world-space.
** The transformation: world_dir = camera_matrix * viewport_dir
*/
t_vec3	camera_to_world_direction(t_camera *camera, t_vec3 viewport_dir)
{
	return (mat3_multiply_vec3(camera->rotation, viewport_dir));
}
