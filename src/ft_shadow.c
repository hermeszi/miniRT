/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shadow.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 10:11:34 by jngew             #+#    #+#             */
/*   Updated: 2025/06/26 20:30:20 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

static t_color	calculate_ambient_light(t_color object_color, t_ambient ambient)
{
	t_color	ambient_component;

	ambient_component = color_mult(object_color, ambient.color);
	return (color_scale(ambient_component, ambient.ratio));
}
static t_color	calculate_point_light(t_hit *hit, t_scene *scene)
{
	t_vec3	light_dir;
	double	intensity;
	t_color	diffuse;

	light_dir = vec3_norm(vec3_sub(scene->light.position, hit->point));
	intensity = fmax(0.0, vec3_dot(hit->normal, light_dir));
	diffuse = color_scale(hit->color, intensity * scene->light.brightness);
	return (diffuse);
}

t_color	calculate_shading(t_hit *hit, t_scene *scene, int in_shadow)
{
	t_color	final_color;
	
	final_color = calculate_ambient_light(hit->color, scene->ambient);
	if (!in_shadow)
		final_color = color_add(final_color, calculate_point_light(hit, scene));
	return (final_color);
}
