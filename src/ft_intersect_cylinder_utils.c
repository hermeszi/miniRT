/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intersect_cylinder_utils.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 12:06:14 by jngew             #+#    #+#             */
/*   Updated: 2025/07/04 17:44:36 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

void	get_body_hit(t_hit *hit, double t, t_ray ray, t_cylinder cyl)
{
	t_vec3	oc;
	double	x;

	hit->t = t;
	hit->hit = 1;
	hit->point = vec3_add(ray.origin, vec3_multiply(ray.direction, t));
	oc = vec3_sub(hit->point, cyl.center);
	x = vec3_dot(oc, cyl.axis);
	hit->normal = vec3_norm(vec3_sub(oc, vec3_multiply(cyl.axis, x)));
	hit->color = cyl.color;
	hit->object = NULL;
}

void	get_cap_hit(t_hit *hit, double t, t_ray ray, t_cylinder cyl)
{
	hit->t = t;
	hit->hit = 1;
	hit->point = vec3_add(ray.origin, vec3_multiply(ray.direction, t));
	hit->normal = cyl.axis;
	if (vec3_dot(ray.direction, cyl.axis) > 0)
		hit->normal = vec3_multiply(cyl.axis, -1);
	hit->color = cyl.color;
	hit->object = NULL;
}

int	is_within_height(double t, t_ray ray, t_cylinder cyl)
{
	double	x;
	t_vec3	p;
	t_vec3	oc;

	if (t <= EPSILON)
		return (0);
	p = vec3_add(ray.origin, vec3_multiply(ray.direction, t));
	oc = vec3_sub(p, cyl.center);
	x = vec3_dot(oc, cyl.axis);
	return (x >= -cyl.height / 2.0 && x <= cyl.height / 2.0);
}

double	intersect_caps(t_ray ray, t_cylinder cyl)
{
	t_hit	hit;
	t_plane	cap;
	double	x;
	double	radius;

	x = INFINITY;
	radius = cyl.diameter / 2.0;
	cap.position = vec3_sub(cyl.center,
			vec3_multiply(cyl.axis, cyl.height / 2.0));
	cap.normal = vec3_multiply(cyl.axis, -1);
	hit = intersect_plane(ray, cap);
	if (hit.hit && hit.t < x)
		if (vec3_length(vec3_sub(hit.point, cap.position)) < radius)
			x = hit.t;
	cap.position = vec3_add(cyl.center,
			vec3_multiply(cyl.axis, cyl.height / 2.0));
	cap.normal = cyl.axis;
	hit = intersect_plane(ray, cap);
	if (hit.hit && hit.t < x)
		if (vec3_length(vec3_sub(hit.point, cap.position)) < radius)
			x = hit.t;
	return (x);
}
