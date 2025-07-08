/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec_calculations2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngew <jngew@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 11:44:49 by jngew             #+#    #+#             */
/*   Updated: 2025/07/02 18:44:02 by jngew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

t_vec3	vec3_cross(t_vec3 v1, t_vec3 v2)
{
	t_vec3	res;

	res.x = v1.y * v2.z - v1.z * v2.y;
	res.y = v1.z * v2.x - v1.x * v2.z;
	res.z = v1.x * v2.y - v1.y * v2.x;
	return (res);
}

double	vec3_dot(t_vec3 v1, t_vec3 v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_vec3	vec3_mult_vec3(t_vec3 v1, t_vec3 v2)
{
	t_vec3	res;

	res.x = v1.x * v2.x;
	res.y = v1.y * v2.y;
	res.z = v1.z * v2.z;
	return (res);
}

t_vec3	get_stable_tangent(t_vec3 normal)
{
	t_vec3	world_up;
	t_vec3	world_right;

	world_up = vec3_new(0, 1, 0);
	world_right = vec3_new(1, 0, 0);
	if (fabs(vec3_dot(normal, world_up)) > 0.99)
		return (vec3_norm(vec3_cross(normal, world_right)));
	else
		return (vec3_norm(vec3_cross(world_up, normal)));
}
