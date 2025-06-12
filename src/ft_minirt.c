/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minirt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 17:46:22 by myuen             #+#    #+#             */
/*   Updated: 2025/06/12 19:18:56 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

static void	check_args(int argc, char **argv)
{
	int	len;

	if (argc != 2)
	{
		print_error_exit("Usage: ./miniRT <scene.rt>");
		return ;
	}
	len = ft_strlen(argv[1]);
	if (len < 4 || ft_strncmp(argv[1] + len - 3, ".rt", 3) != 0)
	{
		print_error_exit("Invalid file extension. Use .rt");
		return ;
	}
}

int	main(int argc, char *argv[])
{
	t_main	app;

	check_args(argc, argv);
	if (init_app(&app, argv[1]))
	{
		clear_image(app.display);
		mlx_put_image_to_window(app.display->mlx_ptr,
			app.display->win_ptr, app.display->img_ptr, 0, 0);
	}
	else
	{
		print_scene_info(app.scene);
		render_scene(&app);
	}
	printf("miniRT app init\n");
	init_hooks(&app);
	mlx_loop(app.display->mlx_ptr);
	return (0);
}
