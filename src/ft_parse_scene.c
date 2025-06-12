/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_scene.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 14:40:18 by jngew             #+#    #+#             */
/*   Updated: 2025/06/12 19:22:08 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

void	parse_ambient(char *line, t_scene *scene)
{
	char	**tokens;

	if (scene->ambient.ratio >= 0)
		print_error_exit ("Multiple ambient light definitions");
	tokens = ft_split(line, ' ');
	if (!tokens || !tokens[1] || !tokens[2] || tokens[3])
		print_error_exit ("Invalid ambient light format (A ratio R,G,B)");
	scene->ambient.ratio = ft_atof(tokens[1]);
	if (scene->ambient.ratio < 0.0 || scene->ambient.ratio > 1.0)
		print_error_exit ("Ambient ratio must be between 0.0 and 1.0");
	parse_color(tokens[2], &scene->ambient.color);
	free_tokens(tokens);
}

void	parse_camera(char *line, t_scene *scene)
{
	char	**tokens;

	if (scene->camera.fov >= 0)
		print_error_exit ("Multiple camera definitions");
	tokens = ft_split(line, ' ');
	if (!tokens || !tokens[1] || !tokens[2] || !tokens[3] || tokens[4])
		print_error_exit ("Invalid camera format");
	parse_vector(tokens[1], &scene->camera.position);
	parse_norm_vector(tokens[2], &scene->camera.orientation);
	scene->camera.fov = ft_atoi(tokens[3]);
	if (scene->camera.fov < 0 || scene->camera.fov > 180)
		print_error_exit("Camera FOV must be between 0 and 180");
	free_tokens(tokens);
}

void	parse_light(char *line, t_scene *scene)
{
	char	**tokens;
	int		token_count;

	if (scene->light.brightness >= 0)
		print_error_exit ("Multiple light definitions");
	tokens = ft_split(line, ' ');
	if (!tokens || !tokens[1] || !tokens[2])
		print_error_exit("Invalid light format");
	token_count = 0;
	while (tokens[token_count])
		token_count++;
	parse_vector(tokens[1], &scene->light.position);
	scene->light.brightness = ft_atof(tokens[2]);
	if (scene->light.brightness < 0.0 || scene->light.brightness > 1.0)
		print_error_exit ("Light brightness must be between 0.0 and 1.0");
	if (token_count > 3)
		parse_color(tokens[3], &scene->light.color);
	else
	{
		scene->light.color.r = 255;
		scene->light.color.g = 255;
		scene->light.color.b = 255;
	}
	free_tokens(tokens);
}

void	parse_color(char *str, t_color *color)
{
	char	**rgb;

	rgb = ft_split(str, ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
	{
		if (rgb)
			free_tokens(rgb);
		print_error_exit ("Invalid color format (R,G,B)");
	}
	color->r = ft_atoi(rgb[0]);
	color->g = ft_atoi(rgb[1]);
	color->b = ft_atoi(rgb[2]);
	if (color->r > 255 ||  color->g > 255 ||  color->b > 255)
		print_error_exit ("Color values must be between 0 and 255");
	free_tokens(rgb);
}
