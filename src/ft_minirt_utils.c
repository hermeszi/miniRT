/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minirt_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 16:21:31 by myuen             #+#    #+#             */
/*   Updated: 2025/06/12 15:34:29 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

int	rgb_to_int(t_color c)
{
	return ((c.r << 16) | (c.g << 8) | c.b);
}

double	degrees_to_radians(double degrees)
{
	return (degrees * M_PI / 180.0);
}
