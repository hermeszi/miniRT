/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 17:46:22 by myuen             #+#    #+#             */
/*   Updated: 2025/06/23 20:43:41 by myuen            ###   ########.fr       */
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
		return;
	y = 0;
	while (y < app->display->height)
	{
		x = 0;
		while (x < app->display->width)
		{
			ray = create_ray(&app->scene->camera, x, y);
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
	mlx_put_image_to_window(app->display->mlx_ptr, app->display->win_ptr, \
			app->display->img_ptr, 0, 0);
}

// static void	draw_test_layers_screen(t_display *display)
// {
// 	int	x;
// 	int	y;
// 	int	dx;
// 	int	dy;
// 	int	dist_to_edge;
// 	int	border_size;
// 	int	layer;
// 	int	color;
// 	int	max_dim;

// 	if (display->width < display->height)
// 		max_dim = display->width;
// 	else
// 		max_dim = display->height;
// 	border_size = max_dim / 20;

// 	y = 0;
// 	while (y < display->height)
// 	{
// 		x = 0;
// 		while (x < display->width)
// 		{
// 			if (x < display->width / 2)
// 				dx = x;
// 			else
// 				dx = display->width - 1 - x;
// 			if (y < display->height / 2)
// 				dy = y;
// 			else
// 				dy = display->height - 1 - y;
// 			if (dx < dy)
// 				dist_to_edge = dx;
// 			else
// 				dist_to_edge = dy;

// 			layer = dist_to_edge / border_size;
// 			if (layer > 9)
// 				layer = 9;
// 			color = layer * 0x111111;
// 			set_pixel(display, x, y, color);
// 			x++;
// 		}
// 		y++;
// 	}
// }
