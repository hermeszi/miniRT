/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngew <jngew@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 18:04:07 by jngew             #+#    #+#             */
/*   Updated: 2025/07/02 18:04:32 by jngew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

void	check_filename(char *file)
{
	int	len;

	len = ft_strlen(file);
	if (len < 3 || file[len - 3] != '.' || file[len - 2] != 'r'
		|| file [len - 1] != 't')
		print_error_exit ("Invalid file format");
}

void	init_scene(t_scene *scene)
{
	scene->ambient.ratio = -1.0;
	init_camera(&scene->camera);
	scene->light.brightness = -1.0;
	scene->background = hex_to_rgb(BACKGROUND_COLOR);
	scene->object_count = 0;
	scene->objects = NULL;
}

void	validate_scene(t_scene *scene)
{
	if (scene->ambient.ratio < 0)
		print_error_exit("Missing ambient light");
	if (scene->camera.fov < 0)
		print_error_exit("Missing camera");
	if (scene->light.brightness < 0)
		print_error_exit("Missing light source");
}

void	free_tokens(char **tokens)
{
	int	x;

	x = 0;
	while (tokens[x])
		free (tokens[x++]);
	free (tokens);
}

void	parse_norm_vector(char *str, t_vec3 *vec)
{
	parse_vector(str, vec);
	if (vec->x == 0 && vec->y == 0 && vec->z == 0)
		print_error_exit("Direction vector cannot be zero");
	*vec = vec3_norm(*vec);
}
