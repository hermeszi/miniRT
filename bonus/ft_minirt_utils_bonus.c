/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minirt_utils_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 16:21:31 by myuen             #+#    #+#             */
/*   Updated: 2025/07/04 19:49:19 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt_bonus.h"

int	rgb_to_int(t_color c)
{
	return ((c.r << 16) | (c.g << 8) | c.b);
}

t_color	hex_to_rgb(int hex)
{
	t_color	c;

	c.r = (hex >> 16) & 0xFF;
	c.g = (hex >> 8) & 0xFF;
	c.b = hex & 0xFF;
	return (c);
}

t_color	invert_color(t_color c)
{
	t_color	inv;

	inv.r = 255 - c.r;
	inv.g = 255 - c.g;
	inv.b = 255 - c.b;
	return (inv);
}

double	degrees_to_radians(double degrees)
{
	return (degrees * M_PI / 180.0);
}
