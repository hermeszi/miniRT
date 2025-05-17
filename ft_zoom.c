/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_zoom.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 16:22:17 by myuen             #+#    #+#             */
/*   Updated: 2024/10/24 16:22:19 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fractol.h"

void	ft_zoom_in(t_data *data)
{
	double	range_x;
	double	range_y;
	double	new_x1;
	double	new_y1;

	if (data->zoom_factor >= 1)
		data->zoom_factor = ZOOM_FACTOR;
	range_x = data->math_x2 - data->math_x1;
	range_y = data->math_y2 - data->math_y1;
	new_x1 = data->math_x1 + (range_x - (range_x * data->zoom_factor)) / 2;
	new_y1 = data->math_y1 + (range_y - (range_y * data->zoom_factor)) / 2;
	if (ft_valid_range(new_x1, new_x1 + (range_x * data->zoom_factor),
			new_y1, new_y1 + (range_y * data->zoom_factor)))
	{
		data->math_x1 = new_x1;
		data->math_x2 = new_x1 + (range_x * data->zoom_factor);
		data->math_y1 = new_y1;
		data->math_y2 = new_y1 + (range_y * data->zoom_factor);
	}
}

void	ft_zoom_out(t_data *data)
{
	double	range_x;
	double	range_y;
	double	new_x1;
	double	new_y1;

	if (data->zoom_factor >= 1)
		data->zoom_factor = ZOOM_FACTOR;
	range_x = data->math_x2 - data->math_x1;
	range_y = data->math_y2 - data->math_y1;
	new_x1 = data->math_x1 - (range_x - (range_x * data->zoom_factor)) / 2;
	new_y1 = data->math_y1 - (range_y - (range_y * data->zoom_factor)) / 2;
	if (ft_valid_range(new_x1, new_x1 + (range_x * data->zoom_factor),
			new_y1, new_y1 + (range_y * data->zoom_factor)))
	{
		data->math_x1 = new_x1;
		data->math_x2 = new_x1 + (range_x / data->zoom_factor);
		data->math_y1 = new_y1;
		data->math_y2 = new_y1 + (range_y / data->zoom_factor);
	}
}
