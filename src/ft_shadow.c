/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shadow.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 10:11:34 by jngew             #+#    #+#             */
/*   Updated: 2025/06/28 14:49:34 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

static t_color	calculate_ambient_light(t_color object_color, t_ambient ambient)
{
	t_color	ambient_component;

	ambient_component = color_mult(object_color, ambient.color);
	return (color_scale(ambient_component, ambient.ratio));
}

t_color	calculate_shading(t_hit *hit, t_scene *scene, int in_shadow)
{
	t_color	final_color;
	t_color	obj_color;
	
	final_color = calculate_ambient_light(hit->color, scene->ambient);
	if (!in_shadow)
	{
		obj_color =  calculate_point_light(hit, scene);
		final_color = color_add(final_color,obj_color);
	}
	return (final_color);
}
