/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec_calculations.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngew <jngew@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 11:44:49 by jngew             #+#    #+#             */
/*   Updated: 2025/06/10 11:44:54 by jngew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

double	vec3_length(t_vec3 v)
{
	double	x_squared;
	double	y_squared;
	double	z_squared;
	double	sum_of_squares;
	double	length;

	x_squared = v.x * v.x;
	y_squared = v.y * v.y;
	z_squared = v.z * v.z;
	sum_of_squares = x_squared + y_squared + z_squared;
	length = sqrt(sum_of_squares);
	return (length);
}

t_vec3	vec3_norm(t_vec3 v)
{
	t_vec3	norm;
	double	length;

	length = vec3_length(v);
	if (length == 0)
		print_error ("Cannot normalize zero vector");
	norm.x = v.x / length;
	norm.y = v.y / length;
	norm.z = v.z / length;
	return (norm);
}

t_vec3	vec3_add(t_vec3 v1, t_vec3 v2)
{
	t_vec3	res;

	res.x = v1.x + v2.x;
	res.y = v1.y + v2.y;
	res.z = v1.z + v2.z;
	return (res);
}

t_vec3	vec3_sub(t_vec3 v1, t_vec3 v2)
{
	t_vec3	res;

	res.x = v1.x - v2.x;
	res.y = v1.y - v2.y;
	res.z = v1.z - v2.z;
	return (res);
}

t_vec3	vec3_multiply(t_vec3 v, double scalar)
{
	t_vec3	res;

	res.x = v.x * scalar;
	res.y = v.y * scalar;
	res.z = v.z * scalar;
	return (res);
}

t_vec3	vec3_cross(t_vec3 v1, t_vec3 v2)
{
	t_vec3	res;

	res.x = v1.y * v2.z - v1.z * v2.y;
	res.y = v1.z * v2.x - v1.x * v2.z;
	res.z = v1.x * v2.y - v1.y * v2.x;
	return (res);
}

t_vec3	vec3_new(double x, double y, double z)
{
	t_vec3	v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

double	vec3_dot(t_vec3 v1, t_vec3 v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}
