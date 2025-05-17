/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 17:04:10 by myuen             #+#    #+#             */
/*   Updated: 2024/10/25 17:11:52 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fractol.h"

static double	parse_integer_part(const char **str)
{
	double	result;

	result = 0.0;
	while (ft_isdigit(**str))
	{
		result = result * 10.0 + (**str - '0');
		(*str)++;
	}
	return (result);
}

static double	parse_fractional_part(const char **str)
{
	double	fraction;
	double	divisor;

	fraction = 0.0;
	divisor = 1.0;
	if (**str == '.')
	{
		(*str)++;
		while (ft_isdigit(**str))
		{
			divisor /= 10.0;
			fraction += (**str - '0') * divisor;
			(*str)++;
		}
	}
	return (fraction);
}

int	ft_isvalid_float_str(const char *str)
{
	int	has_digit;
	int	has_decimal;

	has_digit = 0;
	has_decimal = 0;
	while (ft_isspace(*str))
		str++;
	if (*str == '+' || *str == '-')
		str++;
	while (*str)
	{
		if (ft_isdigit(*str))
			has_digit = 1;
		else if (*str == '.')
		{
			if (has_decimal)
				return (0);
			has_decimal = 1;
		}
		else
			return (0);
		str++;
	}
	return (has_digit);
}

double	ft_atof(const char *str)
{
	double	result;
	double	fraction;
	int		sign;

	result = 0.0;
	fraction = 0.0;
	sign = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	result = parse_integer_part(&str);
	fraction = parse_fractional_part(&str);
	return (sign * (result + fraction));
}
