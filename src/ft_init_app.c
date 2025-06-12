/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_app.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngew <jngew@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 16:21:07 by myuen             #+#    #+#             */
/*   Updated: 2025/06/12 16:19:35 by jngew            ###   ########.fr       */
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
	win->win_ptr = mlx_new_window(win->mlx_ptr, win->width, win->height, "miniRT");
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
	double	aspect_ratio;
	double	fov_rad;

	if (fov_deg <= 0.0 || fov_deg >= 180.0)
	{
		perror("Viewport: Invalid FOV - must be between (0, 180) degrees.");
		return (1);
	}
	if (width <= 0 || height <= 0)
	{
		perror("Viewport: Invalid screen size.");
		return (1);
	}
	fov_rad = degrees_to_radians(fov_deg);
	vp->distance = VIEWPORT_DISTANCE;
	vp->height = 2.0 * tan(fov_rad / 2.0);
	aspect_ratio = (double)width / (double)height;
	vp->width = vp->height * aspect_ratio;
	return (0);
}
// static t_scene	*dummy_scene(void)
// {
// 	t_scene		*scene;
// 	t_object	*test_sphere;

// 	scene = malloc(sizeof(t_scene));
// 	if (!scene)
// 		return (NULL);

// 	scene->ambient.ratio = 0.2;
// 	scene->ambient.color = (t_color){255, 255, 255};

// 	scene->camera.position = (t_vec3){0.0, 0.0, 0.0};
// 	scene->camera.orientation = vec3_norm((t_vec3){0.0, 0.0, 1.0});
// 	scene->camera.fov = 70.0;

// 	scene->light.position = (t_vec3){-10.0, 10.0, -10.0};
// 	scene->light.brightness = 0.7;
// 	scene->light.color = (t_color){255, 255, 255};

// 	test_sphere = malloc(sizeof(t_object));
// 	if (!test_sphere)
// 	{
// 		free(scene);
// 		return (NULL);
// 	}
// 	test_sphere->type = OBJ_SPHERE;
// 	test_sphere->data.sphere.color = (t_color){255, 0, 0};
// 	test_sphere->data.sphere.center = (t_vec3){0.0, 0.0, 5.0};
// 	test_sphere->data.sphere.radius = 1.0;
// 	test_sphere->next = NULL;

// 	scene->objects = test_sphere;
// 	scene->object_count = 1;

// 	return (scene);
// }
void	init_app(t_main *app, char *filename)
{
	app->display = malloc(sizeof(t_display));
	if (!app->display || init_display_struct(app->display)
		|| init_screen_mlx(app->display))
	{
		print_error_exit("Failed to initialize display.");
		exit(EXIT_FAILURE);
	}
	// (void) filename;
	// app->scene = dummy_scene();
	app->scene = parse_file(filename);
	if (init_viewport(&app->viewport, app->scene->camera.fov, \
	app->display->width, app->display->height))
	{
		free_all(app);
		print_error_exit("Failed to initialize display.");
	}
	printf("miniRT app init\n");
}
