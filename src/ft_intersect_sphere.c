/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intersect_sphere.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 14:13:00 by myuen             #+#    #+#             */
/*   Updated: 2025/06/26 20:39:27 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

/*
** Solves the quadratic equation using discriminant
** Returns the smallest valid t ≥ 1.0 (in front of camera), or -1 if no solution
This tries to solve for t. 
There are 3 cases:
	Discriminant b² - 4ac
	< 0		Miss – no intersection
	= 0		Just touches the sphere
	> 0		Hits the sphere in 2 spots (entry and exit)
We only care about t ≥ 1.0, meaning the sphere is in front of the camera.
*/
static double	solve_quadratic(double a, double b, double c)
{
	double	discriminant;
	double	t1;
	double	t2;

	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (-1.0);
	t1 = (-b - sqrt(discriminant)) / (2 * a);
	t2 = (-b + sqrt(discriminant)) / (2 * a);
	if (t1 >= 1.0)
		return (t1);
	if (t2 >= 1.0)
		return (t2);
	return (-1.0);
}

/*
** Populates the hit record with intersection point, normal, and color
If hit, find the point
	hit.point: where the ray touched the sphere
	hit.normal: the direction the surface faces there
	hit.color: the sphere’s color
*/
static void	get_hit_record(t_hit *hit, t_ray ray, t_sphere sphere, double t)
{
	hit->hit = 1;
	hit->t = t;
	hit->point = vec3_add(ray.origin, vec3_multiply(ray.direction, t));
	hit->normal = vec3_norm(vec3_sub(hit->point, sphere.center));
	hit->color = sphere.color;
}
/*
** Computes coefficients a, b, and c for the ray-sphere intersection equation:
** Ray: P(t) = O + tD
** Sphere: |P - C|² = r²
** => a·t² + b·t + c = 0
This step finds:
    a: how long the ray's direction is (usually 1, since it's normalized)
    b: how far the ray points toward the sphere
    c: how far away the ray starts from the sphere (minus the radius)
*/
/*
** Main ray-sphere intersection function
** Returns a t_hit record with hit = 1 if ray intersects sphere
*/
t_hit	intersect_sphere(t_ray ray, t_sphere sphere)
{
	t_hit		hit;
	t_quadratic	q;

	hit.hit = 0;
	hit.t = INFINITY;
	q.oc = vec3_sub(ray.origin, sphere.center);
	q.a = 1.0;
	q.b = 2.0 * vec3_dot(q.oc, ray.direction);
	q.c = vec3_dot(q.oc, q.oc) - (sphere.radius * sphere.radius);
	q.t = solve_quadratic(q.a, q.b, q.c);
	if (q.t < 0)
		return (hit);
	get_hit_record(&hit, ray, sphere, q.t);
	return (hit);
}


/*
** Ray-sphere intersection using quadratic equation
** Ray: P = O + t*D
** Sphere: |P - C|² = r²
** Substitute: |O + t*D - C|² = r²
** Solve for t
*/


// t_hit	intersect_sphere(t_ray ray, t_sphere sphere)
// {
// 	t_hit	hit;
// 	t_vec3	oc;
// 	double	a;
// 	double	b;
// 	double	c;
// 	double	discriminant;
// 	double	t1;
// 	double	t2;
// 	double	closest_t;

// 	// Initialize hit as no intersection
// 	hit.hit = 0;
// 	hit.t = INFINITY;

// 	// Vector from ray origin to sphere center
// 	oc = vec3_sub(ray.origin, sphere.center);

// 	// Quadratic equation coefficients
// 	// a = dot(D, D) - but since D is normalized, this equals 1
// 	a = vec3_dot(ray.direction, ray.direction);
// 	b = 2.0 * vec3_dot(oc, ray.direction);
// 	c = vec3_dot(oc, oc) - (sphere.radius * sphere.radius);

// 	discriminant = b * b - 4 * a * c;

// 	// No intersection if discriminant < 0
// 	if (discriminant < 0)
// 		return (hit);

// 	// Calculate both intersection points
// 	t1 = (-b - sqrt(discriminant)) / (2 * a);
// 	t2 = (-b + sqrt(discriminant)) / (2 * a);

// 	// Choose closest positive t (in front of camera)
// 	closest_t = t1;
// 	if (t1 < 1.0)  // Behind camera or too close
// 		closest_t = t2;
// 	if (closest_t < 1.0)  // Both behind camera
// 		return (hit);

// 	// We have a valid hit
// 	hit.hit = 1;
// 	hit.t = closest_t;
// 	hit.point = vec3_add(ray.origin, vec3_multiply(ray.direction, closest_t));
// 	hit.normal = vec3_norm(vec3_sub(hit.point, sphere.center));
// 	hit.color = sphere.color;

// 	return (hit);
// }

