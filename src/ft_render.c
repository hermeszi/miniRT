/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 17:46:22 by myuen             #+#    #+#             */
/*   Updated: 2025/06/12 15:43:18 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

static void	draw_test_layers_screen(t_display *display)
{
	int	x;
	int	y;
	int	dx;
	int	dy;
	int	dist_to_edge;
	int	border_size;
	int	layer;
	int	color;
	int	max_dim;

	if (display->width < display->height)
		max_dim = display->width;
	else
		max_dim = display->height;
	border_size = max_dim / 20;

	y = 0;
	while (y < display->height)
	{
		x = 0;
		while (x < display->width)
		{
			if (x < display->width / 2)
				dx = x;
			else
				dx = display->width - 1 - x;
			if (y < display->height / 2)
				dy = y;
			else
				dy = display->height - 1 - y;
			if (dx < dy)
				dist_to_edge = dx;
			else
				dist_to_edge = dy;

			layer = dist_to_edge / border_size;
			if (layer > 9)
				layer = 9;
			color = layer * 0x111111;
			set_pixel(display, x, y, color);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(display->mlx_ptr,
		display->win_ptr, display->img_ptr, 0, 0);
}

static void test_raytacing(t_main *app)
{
	t_ray		ray;
	t_vec3		viewport_point;
	//t_color	pixel_color;
	int			x;
	int			y;
	
	y = 0;
	while (y < app->display->height)
	{
		x = 0;
		while (x < app->display->width)
		{
			viewport_point = pixel_to_viewport(x, y, app->viewport);
			//printf("<x:%f, y:%f, z:%f> ", viewport_point.x, viewport_point.y, viewport_point.z);

			ray = create_ray(vec3_new(0, 0, 0), viewport_point);

			// Trace the ray and get pixel color
			//pixel_color = trace_ray(ray, app->scene);

			// Set the pixel
			//set_pixel(app->display, x, y, rgb_to_int(pixel_color));

			x++;
		}
		printf("\n");
		y++;
	}
}

void	render_scene(t_main *app)
{
	test_raytacing(app);
    draw_test_layers_screen(app->display);
}
