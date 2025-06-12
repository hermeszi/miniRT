/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngew <jngew@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 11:54:14 by jngew             #+#    #+#             */
/*   Updated: 2025/06/12 16:18:56 by jngew            ###   ########.fr       */
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
	scene->camera.fov = -1;
	scene->light.brightness = -1.0;
	scene->object_count = 0;
	scene->objects = NULL;
}

void	validate_scene(t_scene *scene)
{
	if (scene->ambient.ratio < 0)
		print_error_exit("Missing ambient light");
	if (scene->camera.fov <= 0)
		print_error_exit("Missing camera");
	if (scene->light.brightness < 0)
		print_error_exit("Missing light source");
}

char	*clean_line(char *line)
{
	char	*clean;
	int		x;
	int		y;

	if (!line)
		return (NULL);
	x = 0;
	while (line[x] && line[x] != '\n')
		x++;
	line[x] = '\0';
	x = 0;
	while (line[x] && (line[x] == ' ' || line[x] == '\t'))
		x++;
	if (!line[x])
	{
		free (line);
		return (ft_strdup(""));
	}
	clean = malloc(ft_strlen(line) + 1);
	if (!clean)
		print_error_exit ("Memory allocation failed");
	y = 0;
	while (line[x])
	{
		if (line[x] == ' ' || line[x] == '\t')
		{
			clean[y++] = ' ';
			while (line[x] && (line[x] == ' ' || line[x] == '\t'))
				x++;
		}
		else
			clean[y++] = line[x++];
	}
	clean[y] = '\0';
	free (line);
	return (clean);
}

void	parse_lines(int fd, char *line, t_scene *scene, int *obj_count)
{
	while (line)
	{
		if (line[0] == '\0')
		{
			free (line);
			line = get_next_line(fd);
			if (line)
				line = clean_line(line);
			continue;
		}
		if (!ft_strncmp(line, "A ", 2))
			parse_ambient(line, scene);
		else if (!ft_strncmp(line, "C ", 2))
			parse_camera(line, scene);
		else if (!ft_strncmp(line, "L ", 2))
			parse_light(line, scene);
		else if (!ft_strncmp(line, "sp ", 3))
			parse_sphere(line, scene, obj_count);
		else if (!ft_strncmp(line, "pl ", 3))
			parse_plane(line, scene, obj_count);
		else if (!ft_strncmp(line, "cy ", 3))
			parse_cylinder(line, scene, obj_count);
		else
			print_error_exit("Invalid element identifier");
		free (line);
		line = get_next_line(fd);
		if (line)
			line = clean_line(line);
	}
	scene->object_count = *obj_count;
}

void	free_tokens(char **tokens)
{
	int	x;

	x = 0;
	while (tokens[x])
		free (tokens[x++]);
	free (tokens);
}

void	parse_vector(char *str, t_vec3 *vec)
{
	char	**coords;

	coords = ft_split(str, ',');
	if (!coords || !coords[0] || !coords[1] || !coords[2] || coords[3])
	{
		if (coords)
			free_tokens(coords);
		print_error_exit ("Invalid vector format (x,y,z)");
	}
	vec->x = ft_atof(coords[0]);
	vec->y = ft_atof(coords[1]);
	vec->z = ft_atof(coords[2]);
	free_tokens(coords);
}

void	parse_norm_vector(char *str, t_vec3 *vec)
{
	parse_vector(str, vec);
	if (vec->x == 0 && vec->y == 0 && vec->z == 0)
		print_error_exit("Direction vector cannot be zero");
	*vec = vec3_norm(*vec);
}

t_scene	*parse_file(char *file)
{
	int		fd;
	int		obj_count;
	char	*line;
	t_scene	*scene;

	scene = malloc(sizeof(t_scene));
	if (!scene)
		print_error_exit("Scene memory allocation failed");
	obj_count = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		print_error_exit("Could not open scene file");
	check_filename(file);
	init_scene(scene);
	line = get_next_line(fd);
	if (!line)
		print_error_exit("Empty file");
	line = clean_line(line);
	parse_lines(fd, line, scene, &obj_count);
	validate_scene(scene);
	if (close(fd) == -1)
		print_error_exit ("Failed to close file");
	return (scene);
}
