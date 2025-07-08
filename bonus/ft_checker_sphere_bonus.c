/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checker_sphere_bonus.c	                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 13:43:25 by jngew             #+#    #+#             */
/*   Updated: 2025/07/04 19:49:02 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt_bonus.h"

static void	get_sphere_coordinates(t_hit hit, t_sphere sphere, \
	double *u, double *v)
{
	t_vec3	hit_offset;
	t_vec3	direction;
	double	theta;
	double	phi;

	hit_offset = vec3_sub(hit.point, sphere.center);
	direction = vec3_norm(hit_offset);
	theta = atan2(direction.z, direction.x);
	phi = acos(direction.y);
	*u = (theta + M_PI) / (2.0 * M_PI);
	*v = phi / M_PI;
}

static t_color	apply_sphere_checker_pattern(double u, double v, \
	t_color base_color)
{
	double	scaled_u;
	double	scaled_v;
	int		check_u;
	int		check_v;

	scaled_u = u * CHECKER_SCALE;
	scaled_v = v * CHECKER_SCALE;
	check_u = (int)floor(scaled_u);
	check_v = (int)floor(scaled_v);
	if ((check_u + check_v) % 2 == 0)
		return (base_color);
	else
		return (invert_color(base_color));
}

t_color	get_sphere_checker_color(t_hit hit, t_sphere sphere)
{
	double	u;
	double	v;

	get_sphere_coordinates(hit, sphere, &u, &v);
	return (apply_sphere_checker_pattern(u, v, hit.color));
}
