/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 16:21:07 by myuen             #+#    #+#             */
/*   Updated: 2025/06/10 13:18:10 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

void	free_scene(t_scene *scene)
{
	if (!scene)
		return ;
	if (scene->objects)
		free(scene->objects);
	free(scene);
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
	if (app->scene)
		free_scene(app->scene);
	if (app->display)
		free_display(app->display);
}
