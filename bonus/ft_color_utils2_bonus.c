/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color_utils2_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 10:11:34 by jngew             #+#    #+#             */
/*   Updated: 2025/07/07 22:18:10 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

t_color	color_add(t_color c1, t_color c2)
{
	t_color	res;

	res.r = fmin(c1.r + c2.r, 255.0);
	res.g = fmin(c1.g + c2.g, 255.0);
	res.b = fmin(c1.b + c2.b, 255.0);
	return (res);
}

t_color	color_scale(t_color c, double factor)
{
	t_color	res;

	res.r = c.r * factor;
	res.g = c.g * factor;
	res.b = c.b * factor;
	return (res);
}

t_color	color_mult(t_color c1, t_color c2)
{
	t_color	res;

	res.r = (unsigned int)(((c1.r / 255.0) * (c2.r / 255.0)) * 255.0);
	res.g = (unsigned int)(((c1.g / 255.0) * (c2.g / 255.0)) * 255.0);
	res.b = (unsigned int)(((c1.b / 255.0) * (c2.b / 255.0)) * 255.0);
	return (res);
}

t_color	invert_color(t_color c)
{
	t_color	inv;

	inv.r = 255 - c.r;
	inv.g = 255 - c.g;
	inv.b = 255 - c.b;
	return (inv);
}
