/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color_utils1_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 10:11:34 by jngew             #+#    #+#             */
/*   Updated: 2025/07/07 22:17:02 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

t_color	int_to_rgb(const int r, const int g, const int b)
{
	t_color	rgb;

	rgb.r = r;
	rgb.g = g;
	rgb.b = b;
	return (rgb);
}

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
