/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_message.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngew <jngew@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 14:13:00 by myuen             #+#    #+#             */
/*   Updated: 2025/07/09 14:56:53 by jngew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

void	print_error_exit(char *message)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(message, 2);
	exit (EXIT_FAILURE);
}

int	print_error(char *message)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(message, 2);
	return (1);
}

int	pr_er(char **tokens, char *msg)
{
	free_tokens(tokens);
	return (print_error(msg));
}

void	print_vec3(t_vec3 v)
{
	printf("(%.2f, %.2f, %.2f)", v.x, v.y, v.z);
}

void	print_color(t_color c)
{
	printf("(%d, %d, %d)", c.r, c.g, c.b);
}
