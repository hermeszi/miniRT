/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_validation2_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngew <jngew@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 19:13:08 by jngew             #+#    #+#             */
/*   Updated: 2025/07/10 19:13:42 by jngew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt_bonus.h"

static int	check_dot_and_digits(const char *str, int i, int *has_dot)
{
	int	has_digit_after_dot;

	has_digit_after_dot = 0;
	while (str[i])
	{
		if (str[i] == '.')
		{
			if (*has_dot)
				return (0);
			*has_dot = 1;
		}
		else if (ft_isdigit(str[i]))
		{
			if (*has_dot)
				has_digit_after_dot = 1;
		}
		else
			return (0);
		i++;
	}
	if (*has_dot && !has_digit_after_dot)
		return (0);
	return (1);
}

static int	is_valid_number(const char *str)
{
	int	i;
	int	has_dot;

	i = 0;
	has_dot = 0;
	if (!str || !*str)
		return (0);
	if (str[i] == '-')
		i++;
	if (!ft_isdigit(str[i]))
		return (0);
	return (check_dot_and_digits(str, i, &has_dot));
}

static int	check_comma_pattern(const char *str)
{
	int	i;

	if (!str || !*str)
		return (1);
	if (str[0] == ',' || str[ft_strlen(str) - 1] == ',')
		return (1);
	i = 0;
	while (str[i] && str[i + 1])
	{
		if (str[i] == ',' && str[i + 1] == ',')
			return (1);
		i++;
	}
	return (0);
}

static int	validate_number_parts(char **parts)
{
	int	i;

	i = 0;
	while (parts[i])
	{
		if (!is_valid_number(parts[i]))
			return (0);
		i++;
	}
	return (i == 3);
}

int	check_invalid_commas(const char *str)
{
	char	**parts;
	int		valid;

	if (check_comma_pattern(str))
		return (1);
	parts = ft_split(str, ',');
	if (!parts)
		return (1);
	valid = validate_number_parts(parts);
	free_tokens(parts);
	return (!valid);
}
