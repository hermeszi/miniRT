/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minirt_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 17:46:22 by myuen             #+#    #+#             */
/*   Updated: 2025/07/04 20:04:48 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt_bonus.h"

static void	check_args(int argc, char **argv)
{
	int	len;

	if (argc != 2)
	{
		print_error_exit("Usage: ./miniRT_bonus <scene.rt>");
		return ;
	}
	len = ft_strlen(argv[1]);
	if (len < 4 || ft_strncmp(argv[1] + len - 3, ".rt", 3) != 0)
	{
		print_error_exit("Invalid file extension. Use .rt");
		return ;
	}
}

static void	show_scene(t_main *app, int result)
{
	print_scene_info(app->scene);
	if (!result)
		render_scene(app);
	else if (result == 1)
	{
		free_all(app);
		print_error_exit("Screen size is not computable");
	}
	else if (result == 2)
	{
		printf("The window is displaying a closed camera, or infinity.\n");
		clear_image(app->display);
		mlx_put_image_to_window(app->display->mlx_ptr,
			app->display->win_ptr, app->display->img_ptr, 0, 0);
	}
	else
	{
		free_all(app);
		print_error_exit("Display Error");
	}
}

int	main(int argc, char *argv[])
{
	t_main	app;

	check_args(argc, argv);
	show_scene(&app, init_app(&app, argv[1]));
	init_hooks(&app);
	mlx_loop(app.display->mlx_ptr);
	return (1);
}
