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

#include "ft_minirt_bonus.h"

void	set_pixel(t_display *u_data, int x, int y, int color)
{
	int	pixel_offset;

	if (x >= 0 && x < u_data->width && y >= 0 && y < u_data->height)
	{
		pixel_offset = (y * u_data->line_len) + (x * (u_data->bpp / 8));
		*(unsigned int *)(u_data->img_u_data + pixel_offset) = color;
	}
}

void	clear_image(t_display *u_data)
{
	int	x;
	int	y;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			set_pixel(u_data, x, y, COLOR_BLACK);
			x++;
		}
		y++;
	}
}
