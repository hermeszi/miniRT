/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_message.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngew <jngew@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 14:13:00 by myuen             #+#    #+#             */
/*   Updated: 2025/06/10 11:38:28 by jngew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

void	print_error(char *message)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(message, 2);
	exit (EXIT_FAILURE);
}
