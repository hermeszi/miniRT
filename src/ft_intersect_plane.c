/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intersect_plane.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngew <jngew@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 13:43:25 by jngew             #+#    #+#             */
/*   Updated: 2025/07/09 17:19:18 by jngew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

static double	compute_plane_t(t_plane plane, t_ray ray, double denominator)
{
	t_vec3	ray_to_plane;

	ray_to_plane = vec3_sub(plane.position, ray.origin);
	return (vec3_dot(ray_to_plane, plane.normal) / denominator);
}

static t_vec3	adjust_normal(t_vec3 normal, t_ray ray)
{
	if (vec3_dot(ray.direction, normal) > 0)
		return (vec3_multiply(normal, -1));
	return (normal);
}

t_hit	intersect_plane(t_ray ray, t_plane plane)
{
	t_hit	hit;
	double	denominator;

	hit.hit = 0;
	denominator = vec3_dot(plane.normal, ray.direction);
	if (fabs(denominator) > EPSILON)
	{
		hit.t = compute_plane_t(plane, ray, denominator);
		if (hit.t >= 0)
		{
			hit.hit = 1;
			hit.point = vec3_add(ray.origin,
					vec3_multiply(ray.direction, hit.t));
			hit.normal = adjust_normal(plane.normal, ray);
			hit.color = plane.color;
			hit.object = NULL;
		}
	}
	return (hit);
}
