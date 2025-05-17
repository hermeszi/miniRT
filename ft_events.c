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

int	ft_key_press(int keycode, t_window *win)
{
	if (keycode == ESC_KEY)
		ft_close(win);
	else if (keycode == ARROW_DOWN)
		printf("ARROW DOWN\n");
	else if (keycode == ARROW_UP)
		printf("ARROW UP\n");
	else if (keycode == ARROW_LEFT)
		printf("ARROW LEFT\n");
	else if (keycode == ARROW_RIGHT)
		printf("ARROW RGHT\n");
	else if (keycode == C_KEY)
		printf("KEY C\n");
	else if (keycode == V_KEY)
		printf("KEY V\n");
	else if (keycode == Z_KEY)
		printf("KEY Z\n");
	else if (keycode == X_KEY)
		printf("KEY X\n");
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
		printf("SCROLL UP\n");
	}
	else if (button == SCROLL_DOWN)
	{
		printf("SCROLL DOWN\n");
	}
	else if (button == LEFT_MOUSE_CLICK)
	{
		printf("LEFT MOUSR CLICK\n");
	}
	ft_redraw(data);
	return (0);
}
