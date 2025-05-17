/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 21:15:05 by myuen             #+#    #+#             */
/*   Updated: 2024/10/25 16:07:50 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fractol.h"

int	ft_get_color(t_data *data, int iterations, int max_iter)
{
	double	brightness;

	if (iterations == max_iter)
		return (data->base_color);
	brightness = (double)iterations / max_iter;
	return (data->current_color * brightness);
}

void	ft_shift_color(int *color, int *color_index)
{
	const int		colors[] = {
		COLOR_WHITE,
		COLOR_GREY,
		COLOR_RED,
		COLOR_GREEN,
		COLOR_BLUE,
		COLOR_YELLOW,
		COLOR_ORANGE,
		COLOR_MAGENTA,
		COLOR_CYAN,
		COLOR_BLACK
	};
	int				color_count;

	color_count = sizeof(colors) / sizeof(colors[0]);
	*color_index = (*color_index + 1) % color_count;
	*color = colors[*color_index];
}
