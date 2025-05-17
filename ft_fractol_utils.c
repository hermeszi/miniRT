/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fractol_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 16:21:31 by myuen             #+#    #+#             */
/*   Updated: 2024/10/24 16:21:32 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fractol.h"

int	ft_close(void *ptr)
{
	t_window	*win;

	win = (t_window *)ptr;
	if (win)
	{
		if (win->img_ptr != NULL)
			mlx_destroy_image(win->mlx_ptr, win->img_ptr);
		if (win->win_ptr != NULL)
			mlx_destroy_window(win->mlx_ptr, win->win_ptr);
		if (win->mlx_ptr != NULL)
		{
			mlx_destroy_display(win->mlx_ptr);
			free(win->mlx_ptr);
		}
	}
	exit(0);
	return (0);
}


void	ft_map_screen_to_plane(t_data *data, int screen_x,
		int screen_y, t_complex *z)
{
	z->real = data->math_x1
		+ (screen_x * (data->math_x2 - data->math_x1) / WIDTH);
	z->imag = data->math_y1
		+ (screen_y * (data->math_y2 - data->math_y1) / HEIGHT);
}
