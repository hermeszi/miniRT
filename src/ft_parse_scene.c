/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_scene.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngew <jngew@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 14:40:18 by jngew             #+#    #+#             */
/*   Updated: 2025/07/04 18:44:08 by jngew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

void	parse_ambient(char *line, t_scene *scene)
{
	char	**tokens;

	if (scene->ambient.ratio >= 0.0)
		print_error_exit("Multiple ambient light definitions");
	tokens = ft_split(line, ' ');
	if (!tokens || !tokens[1] || !tokens[2] || tokens[3])
		print_error_exit("Invalid ambient light format: A <ratio> <R,G,B>");
	scene->ambient.ratio = get_validated_double(tokens[1]);
	if (scene->ambient.ratio < 0.0 || scene->ambient.ratio > 1.0)
		print_error_exit("Ambient ratio must be between 0.0 and 1.0");
	parse_color(tokens[2], &scene->ambient.color);
	free_tokens(tokens);
}

void	parse_camera(char *line, t_scene *scene)
{
	char	**tokens;

	if (scene->camera.fov >= 0)
		print_error_exit("Multiple camera definitions");
	tokens = ft_split(line, ' ');
	if (!tokens || !tokens[1] || !tokens[2] || !tokens[3] || tokens[4])
		print_error_exit("Invalid camera format: C <x,y,z> <norm_vec> <fov>");
	parse_vector(tokens[1], &scene->camera.position);
	parse_norm_vector(tokens[2], &scene->camera.orientation);
	scene->camera.fov = get_validated_int(tokens[3]);
	if (scene->camera.fov < 0 || scene->camera.fov > 180)
		print_error_exit("Camera FOV must be between 0 and 180");
	build_camera_matrix(&scene->camera);
	free_tokens(tokens);
}

void	parse_light(char *line, t_scene *scene)
{
	char	**tokens;
	int		token_count;

	if (scene->light.brightness >= 0.0)
		print_error_exit("Multiple light definitions");
	tokens = ft_split(line, ' ');
	token_count = 0;
	while (tokens[token_count])
		token_count++;
	if (token_count != 3 && token_count != 4)
		print_error_exit("Invalid light format: L <pos> <brightness> [color]");
	parse_vector(tokens[1], &scene->light.position);
	scene->light.brightness = get_validated_double(tokens[2]);
	if (scene->light.brightness < 0.0 || scene->light.brightness > 1.0)
		print_error_exit("Light brightness must be between 0.0 and 1.0");
	if (token_count == 4)
		parse_color(tokens[3], &scene->light.color);
	else
		scene->light.color = int_to_rgb(255, 255, 255);
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
		print_error_exit("Invalid color format: must be R,G,B");
	}
	color->r = get_validated_int(rgb[0]);
	color->g = get_validated_int(rgb[1]);
	color->b = get_validated_int(rgb[2]);
	if (color->r > 255 || color->g > 255 || color->b > 255
		|| color->r < 0 || color->g < 0 || color->b < 0)
		print_error_exit("Color values must be between 0 and 255");
	free_tokens(rgb);
}
