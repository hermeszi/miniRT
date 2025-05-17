/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_events.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 16:20:49 by myuen             #+#    #+#             */
/*   Updated: 2024/10/24 16:20:51 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fractol.h"

int	ft_key_press(int keycode, t_data *data)
{
	if (keycode == ESC_KEY)
		ft_close(data);
	else if (keycode == ARROW_DOWN)
		ft_pan_down(data);
	else if (keycode == ARROW_UP)
		ft_pan_up(data);
	else if (keycode == ARROW_LEFT)
		ft_pan_left(data);
	else if (keycode == ARROW_RIGHT)
		ft_pan_right(data);
	else if (keycode == C_KEY)
		ft_shift_color(&(data->current_color), &(data->current_color_index));
	else if (keycode == V_KEY)
		ft_shift_color(&(data->base_color), &(data->base_color_index));
	else if (keycode == SPACE_KEY)
		ft_set_aspect_ratio(data);
	else if (keycode == Z_KEY)
		ft_zoom_in(data);
	else if (keycode == X_KEY)
		ft_zoom_out(data);
	ft_redraw(data);
	return (0);
}

int	ft_mouse_event(int button, int x, int y, t_data *data)
{
	double	plane_x;
	double	plane_y;

	plane_x = data->math_x1 + x * (data->math_x2 - data->math_x1) / WIDTH;
	plane_y = data->math_y1 + y * (data->math_y2 - data->math_y1) / HEIGHT;
	if (button == SCROLL_UP)
	{
		ft_set_center(data, plane_x, plane_y);
		ft_zoom_in(data);
	}
	else if (button == SCROLL_DOWN)
	{
		ft_set_center(data, plane_x, plane_y);
		ft_zoom_out(data);
	}
	else if (button == LEFT_MOUSE_CLICK)
	{
		ft_set_center(data, plane_x, plane_y);
	}
	ft_redraw(data);
	return (0);
}
