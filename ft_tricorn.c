/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tricorn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 20:25:40 by myuen             #+#    #+#             */
/*   Updated: 2024/10/25 20:29:13 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fractol.h"

static int	get_iterations(t_complex *c)
{
	t_complex	z;
	int			iter;

	z.real = 0.0;
	z.imag = 0.0;
	iter = 0;
	while (iter < MAX_ITERATIONS)
	{
		if (ft_complex_magnitude_squared(z) > 4.0)
			break ;
		z = ft_complex_add(ft_complex_conjugate_square(z), *c);
		iter++;
	}
	return (iter);
}

void	ft_draw_tricorn(t_data *data)
{
	int			screen_x;
	int			screen_y;
	int			iter;
	t_complex	math_plane;

	if (!data->img_ptr || !data->img_data)
		return ;
	screen_y = 0;
	while (screen_y < HEIGHT)
	{
		screen_x = 0;
		while (screen_x < WIDTH)
		{
			ft_map_screen_to_plane(data, screen_x, screen_y, &math_plane);
			iter = get_iterations(&math_plane);
			if (iter == MAX_ITERATIONS)
				ft_draw_pixel(data, screen_x, screen_y, data->base_color);
			else
				ft_draw_pixel(data, screen_x, screen_y,
					ft_get_color(data, iter, MAX_ITERATIONS));
			screen_x++;
		}
		screen_y++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_ptr, 0, 0);
}
