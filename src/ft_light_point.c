/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_light_point.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 10:11:34 by jngew             #+#    #+#             */
/*   Updated: 2025/07/04 17:49:34 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

static double	compute_attenuation(double distance)
{
	double	kc;
	double	kl;
	double	kq;

	kc = ATTENUATION_CONSTANT;
	kl = ATTENUATION_LINEAR;
	kq = ATTENUATION_QUADRATIC;
	return (1.0 / (kc + kl * distance + kq * distance * distance));
}

static void	light_dir_and_dis(t_vec3 hit_point,
	t_vec3 light_pos, t_vec3 *dir, double *dist)
{
	t_vec3	to_light;

	to_light = vec3_sub(light_pos, hit_point);
	*dist = vec3_length(to_light);
	*dir = vec3_divide(to_light, *dist);
}

static double	diffuse_intensity(t_vec3 normal,
	t_vec3 light_dir, double brightness, double distance)
{
	double	angle;
	double	attenuation;

	angle = fmax(0.0, vec3_dot(normal, light_dir));
	attenuation = compute_attenuation(distance);
	return (angle * brightness * attenuation);
}

t_color	calculate_point_light(t_hit *hit, t_scene *scene)
{
	t_vec3	light_dir;
	double	distance;
	double	intensity;

	light_dir_and_dis(hit->point,
		scene->light.position, &light_dir, &distance);
	intensity = diffuse_intensity(hit->normal,
			light_dir, scene->light.brightness, distance);
	return (color_scale(color_mult(hit->color, scene->light.color), intensity));
}
