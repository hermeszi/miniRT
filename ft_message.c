/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_message.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 14:13:00 by myuen             #+#    #+#             */
/*   Updated: 2024/10/26 14:13:07 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fractol.h"

void	ft_print_control(void)
{
	printf("Controls:\n");
	printf("  - Press 'C' to cycle through render colors\n");
	printf("  - Press 'B' to cycle through base colors\n");
	printf("  - Press SPACE to reset the view\n");
	printf("  - Press 'Z' to zoom in\n");
	printf("  - Press 'X' to zoom out\n");
	printf("  - Use Arrow keys to pan\n");
	printf("  - Left-click to center the view\n");
	printf("  - Use mouse wheel to zoom in or out\n");
}

void	ft_print_usage(const char *program_name)
{
	printf("Error: Not enough arguments.\n");
	printf("*--------------42 Fractol---------------*\n");
	printf("* Usage: %s [-m | -j | -t]   \t*\n", program_name);
	printf("* Examples:                           \t*\n");
	printf("*   Mandelbrot: %s -m        \t*\n", program_name);
	printf("*   Julia Set : %s -j 0.4 0.6\t*\n", program_name);
	printf("*---------------------------------------*\n");
}

void	ft_print_julia_suggestions(void)
{
	printf("--- Suggested values for the Julia set ---\n");
	printf("\tClassic Julia Set:\n");
	printf("\t  -0.4	0.6\n");
	printf("\tSwirling Spirals:\n");
	printf("\t  0.355	0.355\n");
	printf("\tSpider-like Pattern:\n");
	printf("\t  -0.70176	0.3842\n");
	printf("\tDragon-like Structures:\n");
	printf("\t  -0.8	0.156\n");
	printf("\tOrganic Coral Pattern:\n");
	printf("\t  0.285	0.01\n");
	printf("\tLightning Bolt Shapes:\n");
	printf("\t  c = -0.4	0.6\n");
	printf("\tBrain Coral Structure:\n");
	printf("\t  -0.7269	0.1889\n");
	printf("\tDouble Spiral:\n");
	printf("\t  0.37	0.1\n");
	printf("\tCircular Clusters:\n");
	printf("\t  -0.8	0.156\n");
	printf("--- ---------------------------------- ---\n\n");
}
