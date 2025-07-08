/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checker_plane_bonus.c	                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 13:43:25 by jngew             #+#    #+#             */
/*   Updated: 2025/07/04 19:49:02 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt_bonus.h"

static void	get_plane_coordinates(t_hit hit, t_plane plane, \
	double *u, double *v)
{
	t_vec3	tangent_u;
	t_vec3	tangent_v;
	t_vec3	hit_offset;

	tangent_u = get_stable_tangent(plane.normal);
	tangent_v = vec3_norm(vec3_cross(plane.normal, tangent_u));
	hit_offset = vec3_sub(hit.point, plane.position);
	*u = vec3_dot(hit_offset, tangent_u) * CHECKER_SCALE;
	*v = vec3_dot(hit_offset, tangent_v) * CHECKER_SCALE;
}

static t_color	apply_checker_pattern(double u, double v, t_color base_color)
{
	int	check_u;
	int	check_v;

	check_u = (int)floor(u);
	check_v = (int)floor(v);
	if ((check_u + check_v) % 2 == 0)
		return (base_color);
	else
		return (invert_color(base_color));
}

t_color	get_plane_checker_color(t_hit hit, t_plane plane)
{
	double	u;
	double	v;

	get_plane_coordinates(hit, plane, &u, &v);
	return (apply_checker_pattern(u, v, hit.color));
}
