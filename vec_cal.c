/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_cal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngew <jngew@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 14:39:32 by jngew             #+#    #+#             */
/*   Updated: 2025/06/05 14:40:10 by jngew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
		print_error ("Error\nCannot normalize zero vector");
	norm.x = v.x / length;
	norm.y = v.y / length;
	norm.z = v.z / length;
	return (norm);
}
