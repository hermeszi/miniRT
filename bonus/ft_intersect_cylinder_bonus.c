/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intersect_cylinder_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 13:43:25 by jngew             #+#    #+#             */
/*   Updated: 2025/07/04 19:48:56 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt_bonus.h"

static double	get_body_intersection_t(t_ray ray, t_cylinder cylinder)
{
	t_cyl_cal	calc;
	double		closest_t;

	closest_t = INFINITY;
	calc.oc = vec3_sub(ray.origin, cylinder.center);
	calc.a = vec3_dot(ray.direction, ray.direction)
		- pow(vec3_dot(ray.direction, cylinder.axis), 2);
	calc.b = 2 * (vec3_dot(ray.direction, calc.oc)
			- (vec3_dot(ray.direction, cylinder.axis)
				* vec3_dot(calc.oc, cylinder.axis)));
	calc.c = vec3_dot(calc.oc, calc.oc)
		- pow(vec3_dot(calc.oc, cylinder.axis), 2)
		- pow(cylinder.diameter / 2.0, 2);
	calc.discriminant = calc.b * calc.b - 4 * calc.a * calc.c;
	if (calc.discriminant < 0)
		return (INFINITY);
	calc.t1 = (-calc.b - sqrt(calc.discriminant)) / (2 * calc.a);
	calc.t2 = (-calc.b + sqrt(calc.discriminant)) / (2 * calc.a);
	if (is_within_height(calc.t1, ray, cylinder))
		closest_t = calc.t1;
	if (is_within_height(calc.t2, ray, cylinder) && calc.t2 < closest_t)
		closest_t = calc.t2;
	return (closest_t);
}

t_hit	intersect_cylinder(t_ray ray, t_cylinder cylinder)
{
	t_hit	hit;
	double	t_body;
	double	t_cap;
	double	closest_t;

	hit.hit = 0;
	t_body = get_body_intersection_t(ray, cylinder);
	t_cap = intersect_caps(ray, cylinder);
	closest_t = t_body;
	if (t_cap < closest_t)
		closest_t = t_cap;
	if (closest_t < INFINITY && closest_t > EPSILON)
	{
		if (t_cap == closest_t)
			get_cap_hit(&hit, closest_t, ray, cylinder);
		else
			get_body_hit(&hit, closest_t, ray, cylinder);
	}
	return (hit);
}
