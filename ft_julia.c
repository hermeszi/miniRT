/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_julia.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 22:10:31 by myuen             #+#    #+#             */
/*   Updated: 2024/10/24 22:10:37 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fractol.h"

static int	get_iterations(t_complex *z, t_complex *c)
{
	int	iter;

	iter = 0;
	while (iter < MAX_ITERATIONS)
	{
		if (ft_complex_magnitude_squared(*z) > 4.0)
			break ;
		*z = ft_complex_add(ft_complex_square(*z), *c);
		iter++;
	}
	return (iter);
}

void	ft_draw_julia(t_data *data)
{
	int			screen_x;
	int			screen_y;
	int			iter;
	t_complex	z;

	if (!data->img_ptr || !data->img_data)
		return ;
	screen_y = 0;
	while (screen_y < HEIGHT)
	{
		screen_x = 0;
		while (screen_x < WIDTH)
		{
			ft_map_screen_to_plane(data, screen_x, screen_y, &z);
			iter = get_iterations(&z, data->c);
			if (iter == MAX_ITERATIONS)
				ft_draw_pixel(data, screen_x, screen_y, data->base_color);
			else
				ft_draw_pixel(data, screen_x, screen_y,
					ft_get_color(data, iter, MAX_ITERATIONS));
			screen_x++;
		}
		screen_y++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_ptr, 0, 0);
}
/*
Classic Julia Set:
	c=−0.4+0.6i
	Produces a typical Julia fractal with complex, symmetrical patterns.
Swirling Spirals:
	c=0.355+0.355i
	Creates beautiful spiral patterns that are often seen in Julia sets.
Spider-like Pattern:
	c=−0.70176−0.3842i
	Produces a spider-web or filament-like structure.
Dragon-like Structures:
	c=−0.8+0.156i
	Generates dragon-shaped curves with intricate, jagged features.
Organic Coral Pattern:
	c=0.285+0.01i
	Forms coral-like, organic shapes with smooth curves and circular features.
Lightning Bolt Shapes:
	c=−0.4+0.6i
	Popular Julia constant that creates jagged, lightning-bolt-like patterns.
Brain Coral Structure:
	c=−0.7269+0.1889i
	Patterns like brain coral, with swirling, layered structures.
Double Spiral:
	c=0.37+0.1i
	Generates a visually pleasing double spiral pattern with radial symmetry.
Circular Clusters:
	c=−0.8+0.156i
	Forms concentric circles that look like clusters of orbs.
*/
