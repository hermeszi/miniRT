/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 16:20:35 by myuen             #+#    #+#             */
/*   Updated: 2024/10/24 16:20:41 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fractol.h"

void	ft_draw_pixel(t_data *data, int x, int y, int color)
{
	int	pixel_offset;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		pixel_offset = (y * data->size_line) + (x * (data->bits_per_pixel / 8));
		*(unsigned int *)(data->img_data + pixel_offset) = color;
	}
	else
		perror("pixel out of bound");
}

void	ft_redraw(t_data *data)
{
	if (data->fractal_type == MANDELBROT)
		ft_draw_mandelbrot(data);
	else if (data->fractal_type == JULIA)
		ft_draw_julia(data);
	else if (data->fractal_type == TRICORN)
		ft_draw_tricorn(data);
	else
		perror("No valid Fractal Selection");
}

void	ft_clear_image(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			ft_draw_pixel(data, x, y, data->base_color);
			x++;
		}
		y++;
	}
}
