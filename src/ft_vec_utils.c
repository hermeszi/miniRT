/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 15:11:45 by jngew             #+#    #+#             */
/*   Updated: 2025/06/12 15:26:53 by myuen            ###   ########.fr       */
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
		print_error_exit ("Cannot normalize zero vector");
	norm.x = v.x / length;
	norm.y = v.y / length;
	norm.z = v.z / length;
	return (norm);
}

t_vec3	vec3_new(double x, double y, double z)
{
	t_vec3	v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

t_vec3	vec3_mult_vec3(t_vec3 v1, t_vec3 v2)
{
	t_vec3	res;

	res.x = v1.x * v2.x;
	res.y = v1.y * v2.y;
	res.z = v1.z * v2.z;
	return (res);
}
