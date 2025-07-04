/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_file_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 11:54:14 by jngew             #+#    #+#             */
/*   Updated: 2025/07/04 19:49:22 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt_bonus.h"

void	parse_vector(char *str, t_vec3 *vec)
{
	char	**coords;

	coords = ft_split(str, ',');
	if (!coords || !coords[0] || !coords[1] || !coords[2] || coords[3])
	{
		if (coords)
			free_tokens(coords);
		print_error_exit("Invalid vector format: must be x,y,z");
	}
	vec->x = get_validated_double(coords[0]);
	vec->y = get_validated_double(coords[1]);
	vec->z = get_validated_double(coords[2]);
	free_tokens(coords);
}

static void	read_and_parse_scene(int fd, t_scene *scene)
{
	char	*line;
	int		obj_count;

	obj_count = 0;
	line = get_next_line(fd);
	if (!line)
		print_error_exit("Empty file");
	line = clean_line(line);
	parse_lines(fd, line, scene, &obj_count);
	validate_scene(scene);
}

t_scene	*parse_file(char *file)
{
	int		fd;
	t_scene	*scene;

	scene = malloc(sizeof(t_scene));
	if (!scene)
		print_error_exit("Scene memory allocation failed");
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		free(scene);
		print_error_exit("Could not open scene file");
	}
	check_filename(file);
	init_scene(scene);
	read_and_parse_scene(fd, scene);
	if (close(fd) == -1)
		print_error_exit("Failed to close file");
	return (scene);
}
