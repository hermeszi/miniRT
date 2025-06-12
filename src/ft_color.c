/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngew <jngew@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 10:11:34 by jngew             #+#    #+#             */
/*   Updated: 2025/06/12 10:45:03 by jngew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

t_color	int_to_rgb(const int r, const int g, const int b)
{
	t_color	rgb;

	rgb.r = r;
	rgb.g = g;
	rgb.b = b;
	return (rgb);
}

t_color	color_add(t_color c1, t_color c2)
{
	t_color	res;

	res.r = fmin(c1.r + c2.r, 255.0);
	res.g = fmin(c1.g + c2.g, 255.0);
	res.b = fmin(c1.b + c2.b, 255.0);
	return (res);
}

t_color	color_scale(t_color c, double factor)
{
	t_color	res;

	res.r = c.r * factor;
	res.g = c.g * factor;
	res.b = c.b * factor;
	return (res);
}

t_color	color_mult(t_color c1, t_color c2)
{
	t_color	res;

	res.r = (unsigned int)(((c1.r / 255.0) * (c2.r / 255.0)) * 255.0);
	res.g = (unsigned int)(((c1.g / 255.0) * (c2.g / 255.0)) * 255.0);
	res.b = (unsigned int)(((c1.b / 255.0) * (c2.b / 255.0)) * 255.0);
	return (res);
}

t_color	calculate_shading(t_hit *hit, t_scene *scene, int in_shadow)
{
	t_color	ambient_component;
	t_color	diffuse_component;
	t_color	final_color;
	t_color	object_color;
	t_vec3	light_dir;
	double	light_intensity;

	if (hit->object->type == OBJ_SPHERE)
		object_color = hit->object->data.sphere.color;
	else if (hit->object->type == OBJ_PLANE)
		object_color = hit->object->data.plane.color;
	else
		object_color = hit->object->data.cylinder.color;
	ambient_component = color_mult(object_color, scene->ambient.color);
	ambient_component = color_scale(ambient_component, scene->ambient.ratio);
	final_color = ambient_component;
	if (in_shadow)
		return (final_color);
	light_dir = vec3_norm(vec3_sub(scene->light.position, hit->point));
	light_intensity = fmax(0.0, vec3_dot(hit->normal, light_dir));
	diffuse_component = color_scale(object_color, light_intensity * scene->light.brightness);
	final_color = color_add(final_color, diffuse_component);
	return (final_color);
}
