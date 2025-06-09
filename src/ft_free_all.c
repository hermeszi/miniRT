/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 16:21:07 by myuen             #+#    #+#             */
/*   Updated: 2025/06/09 21:57:48 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

void	free_scene(t_scene *scene)
{
	if (!scene)
		return;
	if (scene->objects)
		free(scene->objects);
	free(scene);
}

void	free_all(t_main *app)
{
	if (app->scene)
		free_scene(app->scene);
	if (app->display)
	{
		if (app->display->img_ptr)
			mlx_destroy_image(app->display->mlx_ptr, app->display->img_ptr);
		if (app->display->win_ptr)
			mlx_destroy_window(app->display->mlx_ptr, app->display->win_ptr);
		if (app->display->mlx_ptr)
		{
			mlx_destroy_display(app->display->mlx_ptr); // <-- this one is crucial
			free(app->display->mlx_ptr);
		}
		free(app->display);
	}

}
