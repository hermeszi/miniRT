/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_validation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngew <jngew@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 18:29:14 by jngew             #+#    #+#             */
/*   Updated: 2025/07/09 15:57:46 by jngew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

int	get_validated_double(char *str, double *result_out)
{
	char	*endptr;

	if (!str)
		return (print_error("Invalid number format: NULL string provided"));
	*result_out = ft_atof_strict(str, &endptr);
	if (endptr == str || *endptr != '\0')
		return (print_error("Invalid double format in scene file"));
	return (0);
}

int	get_validated_int(char *str, int *result_out)
{
	char	*endptr;
	long	result;

	if (!str)
		return (print_error("Invalid integer format: NULL string provided"));
	result = ft_atoi_strict(str, &endptr);
	if (endptr == str || *endptr != '\0')
		return (print_error("Invalid integer format in scene file"));
	if (result > INT_MAX || result < INT_MIN)
		return (print_error("Integer out of range"));
	*result_out = (int)result;
	return (0);
}
