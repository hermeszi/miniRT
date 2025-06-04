/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngew <jngew@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 11:54:14 by jngew             #+#    #+#             */
/*   Updated: 2025/06/04 14:41:10 by jngew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_error(char *msg)
{
	ft_putendl_fd(msg, 2);
	exit (EXIT_FAILURE);
}

void	check_filename(char *file)
{
	int	len;

	len = ft_strlen(file);
	if (len < 3 || file[len - 3] != '.' || file[len - 2] != 'r'
		|| file [len - 1] != 't')
		print_error ("Error: Invalid file format");
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
		print_error("Error: Missing ambient light");
	if (scene->camera.fov <= 0)
		print_error("Error: Missing camera");
	if (scene->light.brightness < 0)
		print_error("Error: Missing light source");
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
		print_error ("Error: Memory allocation failed");
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
		else if (!ft_strncmp(line, "C ", 2))
		else if (!ft_strncmp(line, "L ", 2))
		else if (!ft_strncmp(line, "sp ", 3))
		else if (!ft_strncmp(line, "pl ", 3))
		else if (!ft_strncmp(line, "cy ", 3))
		else
			print_error("Error: Invalid element identifier");
		free (line);
		line = get_next_line(fd);
		if (line)
			line = clean_line(line);
	}
	scene->object_count = *obj_count;
}

t_scene	*parse_file(char *file, t_scene *scene)
{
	int		fd;
	int		obj_count;
	char	*line;

	obj_count = 0;
	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		print_error("Error: Could not open scene file");
	check_filename(file);
	init_scene(scene);
	line = get_next_line(fd);
	if (!line)
		print_error("Error: Empty file");
	line = clean_line(line);
	parse_lines(fd, line, scene, &obj_count);
	validate_scene(scene);
	if (close(fd) == -1)
		print_error ("Error: Failed to close file");
}
