/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ray.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 14:13:00 by myuen             #+#    #+#             */
/*   Updated: 2025/06/11 21:09:15 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

t_ray	create_ray(t_vec3 origin, t_vec3 direction)
{
	t_ray	ray;

	ray.origin = origin;
	ray.direction = vec3_norm(direction);
	return (ray);
}

/*
** Ray-sphere intersection using quadratic equation
** Ray: P = O + t*D
** Sphere: |P - C|² = r²
** Substitute: |O + t*D - C|² = r²
** Solve for t
*/
/*
t_hit	intersect_sphere(t_ray ray, t_sphere sphere)
{
	t_hit	hit;
	t_vec3	oc;
	double	a;
	double	b;
	double	c;
	double	discriminant;
	double	t1;
	double	t2;
	double	closest_t;

	// Initialize hit as no intersection
	hit.hit = 0;
	hit.t = INFINITY;

	// Vector from ray origin to sphere center
	oc = vec3_sub(ray.origin, sphere.center);

	// Quadratic equation coefficients
	// a = dot(D, D) - but since D is normalized, this equals 1
	a = vec3_dot(ray.direction, ray.direction);
	b = 2.0 * vec3_dot(oc, ray.direction);
	c = vec3_dot(oc, oc) - (sphere.radius * sphere.radius);

	discriminant = b * b - 4 * a * c;

	// No intersection if discriminant < 0
	if (discriminant < 0)
		return (hit);

	// Calculate both intersection points
	t1 = (-b - sqrt(discriminant)) / (2 * a);
	t2 = (-b + sqrt(discriminant)) / (2 * a);

	// Choose closest positive t (in front of camera)
	closest_t = t1;
	if (t1 < 1.0)  // Behind camera or too close
		closest_t = t2;
	if (closest_t < 1.0)  // Both behind camera
		return (hit);

	// We have a valid hit
	hit.hit = 1;
	hit.t = closest_t;
	hit.point = vec3_add(ray.origin, vec3_multiply(ray.direction, closest_t));
	hit.normal = vec3_norm(vec3_sub(hit.point, sphere.center));
	hit.color = sphere.color;

	return (hit);
}
*/

/*
** Trace a ray through the scene
** Returns the color that should be displayed for this ray
*/
/*
t_color	trace_ray(t_ray ray, t_scene *scene)
{
	t_object	*current;
	t_hit		closest_hit;
	t_hit		current_hit;
	t_color		background;

	// Background color (black)
	background.r = 0;
	background.g = 0;
	background.b = 0;

	closest_hit.hit = 0;
	closest_hit.t = INFINITY;

	// Check intersection with all objects
	current = scene->objects;
	while (current)
	{
		if (current->type == OBJ_SPHERE)
		{
			current_hit = intersect_sphere(ray, current->data.sphere);
			if (current_hit.hit && current_hit.t < closest_hit.t)
				closest_hit = current_hit;
		}
		current = current->next;
	}

	if (closest_hit.hit)
		return (closest_hit.color);
	return (background);
}
*/