/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngew <jngew@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 18:04:07 by jngew             #+#    #+#             */
/*   Updated: 2025/07/09 17:22:13 by jngew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

void	check_filename(char *file)
{
	int	len;

	len = ft_strlen(file);
	if (len < 3 || file[len - 3] != '.' || file[len - 2] != 'r'
		|| file [len - 1] != 't')
	{
		print_error("Invalid file extension. Must be .rt");
		exit(EXIT_FAILURE);
	}
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

int	validate_scene(t_scene *scene)
{
	if (scene->ambient.ratio < 0)
		return (print_error("Missing ambient light 'A' in scene file."));
	if (scene->camera.fov < 0)
		return (print_error("Missing camera 'C' in scene file."));
	if (scene->light.brightness < 0)
		return (print_error("Missing light 'L' in scene file."));
	return (0);
}

void	free_tokens(char **tokens)
{
	int	x;

	if (!tokens)
		return ;
	x = 0;
	while (tokens[x])
		free (tokens[x++]);
	free (tokens);
}

int	parse_norm_vector(char *str, t_vec3 *vec)
{
	if (parse_vector(str, vec) != 0)
		return (1);
	if (vec->x == 0 && vec->y == 0 && vec->z == 0)
		return (print_error("Direction vector cannot be zero."));
	*vec = vec3_norm(*vec);
	return (0);
}
