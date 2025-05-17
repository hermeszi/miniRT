/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_fractal.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 18:34:05 by myuen             #+#    #+#             */
/*   Updated: 2025/05/17 18:36:05 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fractol.h"

static int	process_julia_args(t_data *data, const int argc, const char **argv)
{
	data->fractal_type = JULIA;
	if (argc != 4)
	{
		printf("Using default Julia parameters.\n");
		data->c->real = -0.4;
		data->c->imag = 0.6;
		return (0);
	}
	else if (!ft_isvalid_float_str(argv[2]) || !ft_isvalid_float_str(argv[3]))
	{
		printf("Error: Julia parameters should be valid floats.\n");
		return (1);
	}
	data->c->real = ft_atof(argv[2]);
	data->c->imag = ft_atof(argv[3]);
	if ((data->c->real < -2.0 || data->c->real > 2.0)
		|| (data->c->imag < -2.0 || data->c->imag > 2.0))
	{
		printf("Julia parameters should be floats between -2.0 and 2.0\n");
		return (1);
	}
	return (0);
}

static int	set_fractal_type(t_data *data, const char *arg,
		const int argc, const char **argv)
{
	if (ft_strncmp(arg, "-m", 3) == 0)
	{
		data->fractal_type = MANDELBROT;
		data->draw_fractal = ft_draw_mandelbrot;
	}
	else if (ft_strncmp(arg, "-j", 3) == 0)
	{
		if (process_julia_args(data, argc, argv) != 0)
		{
			ft_print_julia_suggestions();
			return (1);
		}
		data->draw_fractal = ft_draw_julia;
	}
	else if (ft_strncmp(arg, "-t", 3) == 0)
	{
		data->fractal_type = TRICORN;
		data->draw_fractal = ft_draw_tricorn;
	}
	else
	{
		printf("Invalid argument or fractal type.\n\tUse -m, -j, or -t.\n");
		return (1);
	}
	return (0);
}

int	ft_process_fractal(t_data *data, const int argc, const char **argv)
{
	if (argc < 2)
	{
		ft_print_usage((const char *)argv[0]);
		return (1);
	}
	return (set_fractal_type(data, argv[1], argc, argv));
}
