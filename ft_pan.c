/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pan.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 17:46:22 by myuen             #+#    #+#             */
/*   Updated: 2024/10/24 16:21:42 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fractol.h"

void	ft_set_center(t_data *data, double new_center_x, double new_center_y)
{
	double	range_x;
	double	range_y;

	range_x = data->math_x2 - data->math_x1;
	range_y = data->math_y2 - data->math_y1;
	if (ft_valid_range(new_center_x - range_x / 2,
			new_center_x + range_x / 2,
			new_center_y - range_y / 2,
			new_center_y + range_y / 2))
	{
		data->math_x1 = new_center_x - range_x / 2;
		data->math_x2 = new_center_x + range_x / 2;
		data->math_y1 = new_center_y - range_y / 2;
		data->math_y2 = new_center_y + range_y / 2;
	}
}

void	ft_pan_left(t_data *data)
{
	double	shift;
	double	new_x1;
	double	new_x2;

	shift = (data->math_x2 - data->math_x1) * PAN_FACTOR;
	new_x1 = data->math_x1 - shift;
	new_x2 = data->math_x2 - shift;
	if (ft_valid_range(new_x1, new_x2, data->math_y1, data->math_y2))
	{
		data->math_x1 = new_x1;
		data->math_x2 = new_x2;
	}
}

void	ft_pan_right(t_data *data)
{
	double	shift;
	double	new_x1;
	double	new_x2;

	shift = (data->math_x2 - data->math_x1) * PAN_FACTOR;
	new_x1 = data->math_x1 + shift;
	new_x2 = data->math_x2 + shift;
	if (ft_valid_range(new_x1, new_x2, data->math_y1, data->math_y2))
	{
		data->math_x1 = new_x1;
		data->math_x2 = new_x2;
	}
}

void	ft_pan_up(t_data *data)
{
	double	shift;
	double	new_y1;
	double	new_y2;

	shift = (data->math_y2 - data->math_y1) * PAN_FACTOR;
	new_y1 = data->math_y1 - shift;
	new_y2 = data->math_y2 - shift;
	if (ft_valid_range(data->math_x1, data->math_x2, new_y1, new_y2))
	{
		data->math_y1 = new_y1;
		data->math_y2 = new_y2;
	}
}

void	ft_pan_down(t_data *data)
{
	double	shift;
	double	new_y1;
	double	new_y2;

	shift = (data->math_y2 - data->math_y1) * PAN_FACTOR;
	new_y1 = data->math_y1 + shift;
	new_y2 = data->math_y2 + shift;
	if (ft_valid_range(data->math_x1, data->math_x2, new_y1, new_y2))
	{
		data->math_y1 = new_y1;
		data->math_y2 = new_y2;
	}
}
