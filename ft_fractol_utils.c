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
	t_data	*data;

	data = (t_data *)ptr;
	if (data)
	{
		if (data->win_ptr != NULL)
			mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		if (data->img_ptr != NULL)
			mlx_destroy_image(data->mlx_ptr, data->img_ptr);
		if (data->mlx_ptr != NULL)
		{
			mlx_destroy_display(data->mlx_ptr);
			free(data->mlx_ptr);
		}
	}
	exit(0);
	return (0);
}

int	ft_valid_range(double new_x1, double new_x2, \
			double new_y1, double new_y2)
{
	if (isnan(new_x1) || isnan(new_x2) || isnan(new_y1) || isnan(new_y2) || \
		isinf(new_x1) || isinf(new_x2) || isinf(new_y1) || isinf(new_y2))
	{
		printf("Error: NaN or Inf numerical values.\n");
		return (0);
	}
	if (fabs(new_x1) > MAX_RANGE || fabs(new_x2) > MAX_RANGE || \
		fabs(new_y1) > MAX_RANGE || fabs(new_y2) > MAX_RANGE)
	{
		printf("Reached maximum zoom.\n");
		return (0);
	}
	if ((new_x2 - new_x1) < MIN_RANGE || (new_y2 - new_y1) < MIN_RANGE)
	{
		printf("Reached mininum zoom.\n");
		return (0);
	}
	return (1);
}

void	ft_set_aspect_ratio(t_data *data)
{
	double	ratio;

	data->math_x1 = -2.0;
	data->math_x2 = 2.0;
	data->math_y1 = -2.0;
	data->math_y2 = 2.0;
	ratio = (double)WIDTH / HEIGHT;
	data->math_x1 = (data->math_y1 * ratio);
	data->math_x2 = (data->math_y2 * ratio);
	data->math_y1 = -2.0;
	data->math_y2 = 2.0;
}

void	ft_map_screen_to_plane(t_data *data, int screen_x,
		int screen_y, t_complex *z)
{
	z->real = data->math_x1
		+ (screen_x * (data->math_x2 - data->math_x1) / WIDTH);
	z->imag = data->math_y1
		+ (screen_y * (data->math_y2 - data->math_y1) / HEIGHT);
}
