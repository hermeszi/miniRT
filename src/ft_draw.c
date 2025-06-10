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

#include "ft_minirt.h"

void	set_pixel(t_display *data, int x, int y, int color)
{
	int	pixel_offset;

	if (x >= 0 && x < data->width && y >= 0 && y < data->height)
	{
		pixel_offset = (y * data->line_len) + (x * (data->bpp / 8));
		*(unsigned int *)(data->img_data + pixel_offset) = color;
	}
	else
		perror("pixel out of bound\n");
}

void	clear_image(t_display *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			set_pixel(data, x, y, COLOR_BLACK);
			x++;
		}
		y++;
	}
}