/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_scene.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngew <jngew@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 14:40:18 by jngew             #+#    #+#             */
/*   Updated: 2025/07/09 15:36:40 by jngew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

int	parse_ambient(char *line, t_scene *scene)
{
	char	**tokens;

	if (scene->ambient.ratio >= 0.0)
		return (print_error("Multiple ambient light definitions"));
	tokens = ft_split(line, ' ');
	if (!tokens)
		return (print_error("Memory allocation failed for tokens."));
	if (!tokens[1] || !tokens[2] || !tokens[3])
		return (pr_er(tokens, "Invalid ambient light: A <ratio> <R,G,B>"));
	scene->ambient.ratio = get_validated_double(tokens[1]);
	if (scene->ambient.ratio < 0.0 || scene->ambient.ratio > 1.0)
		return (pr_er(tokens, "Ambient ratio must be between 0.0 and 1.0"));
	if (parse_color(tokens[2], &scene->ambient.color) != 0)
		return (pr_er(tokens, "Invalid color for ambient light."));
	free_tokens(tokens);
	return (0);
}

int	parse_camera(char *line, t_scene *scene)
{
	char	**tokens;

	if (scene->camera.fov >= 0)
		return (print_error("Multiple camera definitions"));
	tokens = ft_split(line, ' ');
	if (!tokens)
		return (print_error("Memory allocation failed for tokens."));
	if (!tokens[1] || !tokens[2] || !tokens[3] || tokens[4])
		return (pr_er(tokens, "Invalid camera: C <x,y,z> <norm_vec> <fov>"));
	if (parse_vector(tokens[1], &scene->camera.position) != 0 ||
		parse_norm_vector(tokens[2], &scene->camera.orientation) != 0)
		return (pr_er(tokens, "Invalid vector in camera definition."));
	scene->camera.fov = get_validated_int(tokens[3]);
	if (scene->camera.fov < 0 || scene->camera.fov > 180)
		return (pr_er(tokens, "Camera FOV must be between 0 and 180"));
	build_camera_matrix(&scene->camera);
	free_tokens(tokens);
	return (0);
}

int	parse_light(char *line, t_scene *scene)
{
	char	**tokens;
	int		token_count;

	if (scene->light.brightness >= 0.0)
		return (print_error("Multiple light definitions"));
	tokens = ft_split(line, ' ');
	token_count = 0;
	while (tokens && tokens[token_count])
		token_count++;
	if (token_count != 3 && token_count != 4)
		return (pr_er(tokens, "Invalid light: L <pos> <brightness> [color]"));
	if (parse_vector(tokens[1], &scene->light.position) != 0)
		return (pr_er(tokens, "Invalid vector for light position."));
	scene->light.brightness = get_validated_double(tokens[2]);
	if (scene->light.brightness < 0.0 || scene->light.brightness > 1.0)
		return (pr_er(tokens, "Light brightness must be between 0.0 and 1.0"));
	if (token_count == 4)
	{
		if (parse_color(tokens[3], &scene->light.color) != 0)
			return (pr_er(tokens, "Invalid color for light."));
	}
	else
		scene->light.color = int_to_rgb(255, 255, 255);
	free_tokens(tokens);
	return (0);
}

int	parse_color(char *str, t_color *color)
{
	char	**rgb;

	rgb = ft_split(str, ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
		return (pr_er(rgb, "Invalid color format: must be R,G,B"));
	color->r = get_validated_int(rgb[0]);
	color->g = get_validated_int(rgb[1]);
	color->b = get_validated_int(rgb[2]);
	if (color->r > 255 || color->g > 255 || color->b > 255)
		return (pr_er(rgb, "Color values must be between 0 and 255"));
	free_tokens(rgb);
	return (0);
}
