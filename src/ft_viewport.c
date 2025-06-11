/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_viewport.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 16:21:07 by myuen             #+#    #+#             */
/*   Updated: 2025/06/11 20:36:26 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

t_vec3	pixel_to_viewport(int screen_x, int screen_y, t_viewport viewport)
{
	t_vec3	viewport_point;
	double	h;
	double	v;

	h = (double)screen_x / (double)WIN_WIDTH;
	v = (double)screen_y / (double)WIN_HEIGHT;

	viewport_point.x = (h - 0.5) * viewport.width;
	viewport_point.y = (0.5 - v) * viewport.height;
	viewport_point.z = viewport.distance;

	return (viewport_point);
}