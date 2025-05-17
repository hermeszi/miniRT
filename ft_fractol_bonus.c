/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fractol_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 17:46:22 by myuen             #+#    #+#             */
/*   Updated: 2024/10/26 15:18:25 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fractol.h"

static int	init_data(void *ptr, t_complex *num)
{
	t_data	*data;

	data = (t_data *)ptr;
	if (!data)
		return (1);
	data->mlx_ptr = NULL;
	data->win_ptr = NULL;
	data->img_ptr = NULL;
	data->img_data = NULL;
	data->bits_per_pixel = 0;
	data->size_line = 0;
	data->endian = 0;
	data->zoom_factor = ZOOM_FACTOR;
	ft_set_aspect_ratio(data);
	data->fractal_type = 1;
	data->current_color = COLOR_BLUE;
	data->base_color = COLOR_WHITE;
	data->current_color_index = 4;
	data->base_color_index = 0;
	data->c = num;
	data->c->real = -0.4;
	data->c->imag = 0.6;
	data->draw_fractal = NULL;
	return (0);
}

static int	init_screen(void *ptr)
{
	t_data	*data;

	data = (t_data *)ptr;
	data->win_ptr = mlx_new_window(data->mlx_ptr, WIDTH, HEIGHT, "42 Fractol");
	if (!data->win_ptr)
	{
		free(data->mlx_ptr);
		return (1);
	}
	data->img_ptr = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	if (!data->img_ptr)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		free(data->mlx_ptr);
		return (1);
	}
	data->img_data = mlx_get_data_addr(data->img_ptr, \
		&(data->bits_per_pixel), &(data->size_line), &(data->endian));
	return (0);
}

static void	init_hooks(void *ptr)
{
	t_data	*data;

	data = ptr;
	mlx_mouse_hook(data->win_ptr, ft_mouse_event, data);
	mlx_hook(data->win_ptr, 2, 1L << 0, ft_key_press, data);
	mlx_hook(data->win_ptr, 17, 0, ft_close, data);
}

int	main(int argc, char *argv[])
{
	t_data		data;
	t_complex	julia;

	if (init_data(&data, &julia) != 0)
		ft_close(&data);
	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
		return (1);
	if (ft_process_fractal(&data, argc, (const char **)argv) != 0)
		ft_close(&data);
	if (init_screen(&data) != 0)
		ft_close(&data);
	if (data.draw_fractal)
		data.draw_fractal(&data);
	else
		perror("No drawing function set for fractal type.");
	ft_print_control();
	init_hooks(&data);
	mlx_loop(data.mlx_ptr);
	ft_close(&data);
	return (0);
}
