/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fractol.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 17:46:22 by myuen             #+#    #+#             */
/*   Updated: 2025/05/17 20:48:13 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fractol.h"

static int	init_display(void *ptr)
{
	t_window	*win;

	win = (t_window *)ptr;
	if (!win)
		return (1);
	win->mlx_ptr = NULL;
	win->win_ptr = NULL;
	win->img_ptr = NULL;
	win->img_data = NULL;
	win->bits_per_pixel = 0;
	win->size_line = 0;
	win->endian = 0;
	return (0);
}

static int	init_screen(void *ptr)
{
	t_window	*win;

	win = (t_window *)ptr;
	win->win_ptr = mlx_new_window(win->mlx_ptr, WIDTH, HEIGHT, "Nitemare");
	if (!win->win_ptr)
	{
		free(win->mlx_ptr);
		return (1);
	}
	win->img_ptr = mlx_new_image(win->mlx_ptr, WIDTH, HEIGHT);
	if (!win->img_ptr)
	{
		mlx_destroy_window(win->mlx_ptr, win->win_ptr);
		free(win->mlx_ptr);
		return (1);
	}
	win->img_data = mlx_get_data_addr(win->img_ptr, \
		&(win->bits_per_pixel), &(win->size_line), &(win->endian));
	return (0);
}

static void	init_hooks(void *ptr)
{
	t_window	*win;

	win = ptr;
	mlx_mouse_hook(win->win_ptr, ft_mouse_event, win);
	mlx_hook(win->win_ptr, 2, 1L << 0, ft_key_press, win);
	mlx_hook(win->win_ptr, 17, 0, ft_close, win);
}

int	main(int argc, char *argv[])
{
	t_window	win;

	if (argc != 1)
		return (1);
	if (init_display(&win) != 0)
		ft_close(&win);
	win.mlx_ptr = mlx_init();
	if (!win.mlx_ptr)
		return (1);
	if (init_screen(&win) != 0)
		ft_close(&win);
	printf("You see window\n");
	init_hooks(&win);
	mlx_loop(win.mlx_ptr);
	ft_close(&win);
	return (0);
}
