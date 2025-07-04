/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_validation_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 18:29:14 by jngew             #+#    #+#             */
/*   Updated: 2025/07/04 19:49:41 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt_bonus.h"

double	get_validated_double(char *str)
{
	char	*endptr;
	double	result;

	if (!str)
		print_error_exit("Invalid number format: NULL string provided");
	result = ft_atof_strict(str, &endptr);
	if (endptr == str || *endptr != '\0')
		print_error_exit("Invalid double format in scene file");
	return (result);
}

int	get_validated_int(char *str)
{
	char	*endptr;
	long	result;

	if (!str)
		print_error_exit("Invalid integer format: NULL string provided");
	result = ft_atoi_strict(str, &endptr);
	if (endptr == str || *endptr != '\0')
		print_error_exit("Invalid integer format in scene file");
	if (result > INT_MAX || result < INT_MIN)
		print_error_exit("Integer out of range");
	return ((int)result);
}
