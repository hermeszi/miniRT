/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 17:46:22 by myuen             #+#    #+#             */
/*   Updated: 2025/07/11 14:41:07 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

void	draw_scene(t_main *app)
{
	int		x;
	int		y;
	t_ray	ray;
	t_color	pixel_color;

	if (!app || !app->display || !app->scene)
		return ;
	y = 0;
	while (y < app->display->height)
	{
		x = 0;
		while (x < app->display->width)
		{
			ray = create_ray(&app->scene->camera, &app->viewport, x, y);
			pixel_color = trace_ray(ray, app->scene);
			set_pixel(app->display, x, y, rgb_to_int(pixel_color));
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(app->display->mlx_ptr, app->display->win_ptr,
		app->display->img_ptr, 0, 0);
}

void	render_scene(t_main *app)
{
	if (!app || !app->display || !app->scene)
		return ;
	draw_scene(app);
	mlx_put_image_to_window(app->display->mlx_ptr, app->display->win_ptr,
		app->display->img_ptr, 0, 0);
}
