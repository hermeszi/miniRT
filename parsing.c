/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngew <jngew@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 11:54:14 by jngew             #+#    #+#             */
/*   Updated: 2025/06/04 12:39:04 by jngew            ###   ########.fr       */
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

void	parse_lines(int fd, char *line, t_scene, int *obj_count)
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
	}
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
