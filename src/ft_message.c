/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_message.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 14:13:00 by myuen             #+#    #+#             */
/*   Updated: 2025/06/12 16:36:14 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

void	print_error_exit(char *message)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(message, 2);
	exit (EXIT_FAILURE);
}

void	print_vec3(t_vec3 v)
{
	printf("(%.2f, %.2f, %.2f)", v.x, v.y, v.z);
}

void	print_color(t_color c)
{
	printf("(%d, %d, %d)", c.r, c.g, c.b);
}
