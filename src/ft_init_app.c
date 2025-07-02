/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_app.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngew <jngew@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 16:21:07 by myuen             #+#    #+#             */
/*   Updated: 2025/07/02 18:44:31 by jngew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

static int	init_display_struct(t_display *win)
{
	if (!win)
		return (1);
	win->mlx_ptr = NULL;
	win->win_ptr = NULL;
	win->img_ptr = NULL;
	win->img_data = NULL;
	win->bpp = 0;
	win->line_len = 0;
	win->endian = 0;
	win->width = WIN_WIDTH;
	win->height = WIN_HEIGHT;
	return (0);
}

static int	init_screen_mlx(t_display *win)
{
	win->mlx_ptr = mlx_init();
	if (!win->mlx_ptr)
		return (1);
	win->win_ptr = mlx_new_window(win->mlx_ptr,
			win->width, win->height, "miniRT");
	if (!win->win_ptr)
		return (1);
	win->img_ptr = mlx_new_image(win->mlx_ptr, win->width, win->height);
	if (!win->img_ptr)
	{
		mlx_destroy_window(win->mlx_ptr, win->win_ptr);
		return (1);
	}
	win->img_data = mlx_get_data_addr(win->img_ptr,
			&(win->bpp), &(win->line_len), &(win->endian));
	if (!win->img_data)
	{
		mlx_destroy_image(win->mlx_ptr, win->img_ptr);
		mlx_destroy_window(win->mlx_ptr, win->win_ptr);
		return (1);
	}
	return (0);
}

static int	init_viewport(t_viewport *vp, double fov_deg, int width, int height)
{
	if (fov_deg <= 0.0 || fov_deg >= 180.0)
	{
		printf("Viewport: To see objects in the scene, FOV should be BETWEEN 0 and 180 degrees.\n");
		return (2);
	}
	if (width <= 0 || height <= 0)
	{
		perror("Viewport: Invalid screen size.");
		return (1);
	}
	vp->fov_rad = degrees_to_radians(fov_deg);
	vp->distance = VIEWPORT_DISTANCE;
	vp->half_scale = tan(vp->fov_rad / 2.0) * vp->distance;
	vp->height = 2.0 * vp->half_scale;
	vp->aspect_ratio = (double)width / (double)height;
	vp->width = vp->height * vp->aspect_ratio;
	return (0);
}

int	init_app(t_main *app, char *filename)
{
	int	viewpoint_status;

	app->scene = parse_file(filename);
	app->display = malloc(sizeof(t_display));
	if (!app->display || init_display_struct(app->display)
		|| init_screen_mlx(app->display))
	{
		free_all(app);
		print_error_exit("Failed to initialize display.");
	}
	viewpoint_status = init_viewport(&app->viewport, app->scene->camera.fov, \
			app->display->width, app->display->height);
	if (viewpoint_status == 1)
	{
		free_all(app);
		print_error_exit("Failed to initialize viewport.");
	}
	//app->scene->background = color_scale(app->scene->background, app->scene->ambient.ratio);
	printf("miniRT app init\n");
	return(viewpoint_status);
}
