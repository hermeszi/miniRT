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
	printf("-->REDRAW<--\n");
}

void	ft_clear_image(t_window *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			ft_draw_pixel(data, x, y, COLOR_BLACK);
			x++;
		}
		y++;
	}
}
