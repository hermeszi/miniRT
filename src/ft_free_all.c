/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngew <jngew@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 16:21:07 by myuen             #+#    #+#             */
/*   Updated: 2025/06/11 17:28:55 by jngew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

void	free_scene(t_scene *scene)
{
	if (!scene)
		return ;
	free_objects(scene->objects);
	scene->objects = NULL;
}

void	free_display(t_display *display)
{
	if (!display)
		return ;
	if (display->img_ptr)
		mlx_destroy_image(display->mlx_ptr, display->img_ptr);
	if (display->win_ptr)
		mlx_destroy_window(display->mlx_ptr, display->win_ptr);
	if (display->mlx_ptr)
	{
		mlx_destroy_display(display->mlx_ptr);
		free(display->mlx_ptr);
	}
	free(display);
}

void	free_all(t_main *app)
{
	if (!app)
		return ;
	if (app->scene)
	{
		free_scene(app->scene);
		free (app->scene);
		app->scene = NULL;
	}
	if (app->display)
	{
		free_display(app->display);
		free (app->display);
		app->display = NULL;
	}
}
