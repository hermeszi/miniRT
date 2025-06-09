/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_app.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 16:21:07 by myuen             #+#    #+#             */
/*   Updated: 2025/06/09 21:50:26 by myuen            ###   ########.fr       */
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

void	init_app(t_main *app, char *filename)
{
	app->display = malloc(sizeof(t_display));
	if (!app->display || init_display_struct(app->display)
		|| init_screen_mlx(app->display))
	{
		print_error("Failed to initialize display.");
		exit(EXIT_FAILURE);
	}
	(void) filename;
	app->scene = NULL;
	//app->scene = parse_rt_file(filename);
}
