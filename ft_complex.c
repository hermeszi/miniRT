/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_complex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 16:33:03 by myuen             #+#    #+#             */
/*   Updated: 2024/10/25 16:33:06 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fractol.h"

t_complex	ft_complex_add(t_complex a, t_complex b)
{
	t_complex	result;

	result.real = a.real + b.real;
	result.imag = a.imag + b.imag;
	return (result);
}

t_complex	ft_complex_multiply(t_complex a, t_complex b)
{
	t_complex	result;

	result.real = (a.real * b.real) - (a.imag * b.imag);
	result.imag = (a.real * b.imag) + (a.imag * b.real);
	return (result);
}

t_complex	ft_complex_square(t_complex a)
{
	t_complex	result;

	result.real = (a.real * a.real) - (a.imag * a.imag);
	result.imag = (a.real + a.real) * a.imag;
	return (result);
}

t_complex	ft_complex_conjugate_square(t_complex a)
{
	t_complex	result;

	result.real = (a.real * a.real) - (a.imag * a.imag);
	result.imag = -(2 * a.real * a.imag);
	return (result);
}

double	ft_complex_magnitude_squared(t_complex a)
{
	return (a.real * a.real + a.imag * a.imag);
}
