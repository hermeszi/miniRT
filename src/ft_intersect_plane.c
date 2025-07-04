/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intersect_plane.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 13:43:25 by jngew             #+#    #+#             */
/*   Updated: 2025/07/04 19:22:37 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

static double	compute_plane_t(t_plane plane, t_ray ray, double denominator)
{
	t_vec3	p0_l0;

	p0_l0 = vec3_sub(plane.position, ray.origin);
	return (vec3_dot(p0_l0, plane.normal) / denominator);
}

static t_vec3	adjust_normal(t_vec3 normal, t_ray ray)
{
	if (vec3_dot(ray.direction, normal) > 0)
		return (vec3_multiply(normal, -1));
	return (normal);
}

static t_color	get_plane_checker_color(t_hit hit)
{
	double	u;
	double	v;
	int		check_u;
	int		check_v;

	u = hit.point.x * CHECKER_SCALE;
	v = hit.point.z * CHECKER_SCALE;
	check_u = floor(u);
	check_v = floor(v);
	if ((check_u + check_v) % 2 == 0)
		return (hit.color);
	else
		return (invert_color(hit.color));
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
			hit.point = vec3_add(ray.origin, \
				vec3_multiply(ray.direction, hit.t));
			hit.normal = adjust_normal(plane.normal, ray);
			hit.color = plane.color;
			hit.color = get_plane_checker_color(hit);
			hit.object = NULL;
		}
	}
	return (hit);
}
