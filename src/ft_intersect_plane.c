/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intersect_plane.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngew <jngew@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 13:43:25 by jngew             #+#    #+#             */
/*   Updated: 2025/06/17 13:45:21 by jngew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

t_hit	intersect_plane(t_ray ray, t_plane plane)
{
	t_hit	hit;
	double	denominator;
	t_vec3	p0_l0;

	hit.hit = 0;
	denominator = vec3_dot(plane.normal, ray.direction);
	if (fabs(denominator) > 1e-6)
	{
		p0_l0 = vec3_sub(plane.position, ray.origin);
		hit.t = vec3_dot(p0_l0, plane.normal) / denominator;
		if (hit.t >= 0)
		{
			hit.hit = 1;
			hit.point = vec3_add(ray.origin, vec3_multiply(ray.direction, hit.t));
			hit.normal = plane.normal;
			if (vec3_dot(ray.direction, plane.normal) > 0)
				hit.normal = vec3_multiply(plane.normal, -1);
			hit.color = plane.color;
			hit.object = NULL;
		}
	}
	return (hit);
}
