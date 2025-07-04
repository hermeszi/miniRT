/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngew <jngew@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 17:04:10 by myuen             #+#    #+#             */
/*   Updated: 2025/07/04 18:31:49 by jngew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

static long	parse_long(const char **str, int sign)
{
	long	result;

	result = 0;
	while (ft_isdigit(**str))
	{
		if (sign == 1 && result > (LONG_MAX - (**str - '0')) / 10)
			return (LONG_MAX);
		if (sign == -1 && - result < (LONG_MIN + (**str - '0')) / 10)
			return (LONG_MIN);
		result = result * 10 + (**str - '0');
		(*str)++;
	}
	return (result * sign);
}

long	ft_atoi_strict(const char *str, char **endptr)
{
	const char	*start_ptr;
	int			sign;
	long		result;

	start_ptr = str;
	while (ft_isspace(*str))
		str++;
	sign = 1;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	if (!ft_isdigit(*str))
	{
		*endptr = (char *)start_ptr;
		return (0);
	}
	result = parse_long(&str, sign);
	*endptr = (char *)str;
	return (result);
}

static double	parse_integer_part(const char **str, int *has_digit)
{
	double	result;

	result = 0.0;
	while (ft_isdigit(**str))
	{
		*has_digit = 1;
		result = result * 10.0 + (**str - '0');
		(*str)++;
	}
	return (result);
}

static double	parse_fractional_part(const char **str, int *has_digit)
{
	double	fraction;
	double	divisor;

	fraction = 0.0;
	if (**str == '.')
	{
		(*str)++;
		divisor = 1.0;
		while (ft_isdigit(**str))
		{
			*has_digit = 1;
			divisor /= 10.0;
			fraction += (**str - '0') * divisor;
			(*str)++;
		}
	}
	return (fraction);
}

double	ft_atof_strict(const char *str, char **endptr)
{
	const char	*start_ptr;
	double		result;
	int			sign;
	int			has_digit;

	start_ptr = str;
	has_digit = 0;
	while (ft_isspace(*str))
		str++;
	sign = 1;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	result = parse_integer_part(&str, &has_digit);
	result += parse_fractional_part(&str, &has_digit);
	if (!has_digit)
	{
		*endptr = (char *)start_ptr;
		return (0.0);
	}
	*endptr = (char *)str;
	return (sign * result);
}
