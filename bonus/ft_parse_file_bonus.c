/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_file_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 11:54:14 by jngew             #+#    #+#             */
/*   Updated: 2025/07/09 21:14:19 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt_bonus.h"

static int	process_line_content(char *line, t_scene *scene, int *obj_count)
{
	char	*cleaned_line;
	int		status;

	cleaned_line = clean_line(line);
	if (cleaned_line && cleaned_line[0] != '\0')
	{
		status = parse_helper(cleaned_line, scene, obj_count);
		if (status != 0)
		{
			free(cleaned_line);
			return (status);
		}
	}
	free(cleaned_line);
	return (0);
}

int	read_and_parse_scene(int fd, t_scene *scene)
{
	char	*line;
	int		obj_count;
	int		status;

	obj_count = 0;
	line = get_next_line(fd);
	if (!line)
		return (print_error("Scene file is empty or could not be read."));
	while (line != NULL)
	{
		status = process_line_content(line, scene, &obj_count);
		free(line);
		if (status != 0)
		{
			cleanup_remaining_lines(fd, get_next_line(fd));
			return (status);
		}
		line = get_next_line(fd);
	}
	scene->object_count = obj_count;
	return (validate_scene(scene));
}

static t_scene	*handle_file_operations(char *file, int fd, t_scene *scene)
{
	int	obj_count;

	check_filename(file);
	init_scene(scene);
	obj_count = 0;
	if (parse_lines(fd, scene, &obj_count) != 0 || validate_scene(scene) != 0)
	{
		close(fd);
		free_scene(scene);
		return (NULL);
	}
	if (close(fd) == -1)
	{
		free_scene(scene);
		return (print_error("Failed to close file"), NULL);
	}
	scene->object_count = obj_count;
	return (scene);
}

t_scene	*parse_file(char *file)
{
	int		fd;
	t_scene	*scene;

	scene = ft_calloc(1, sizeof(t_scene));
	if (!scene)
	{
		print_error("Scene memory allocation failed");
		return (NULL);
	}
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		free(scene);
		return (print_error("Could not open scene file"), NULL);
	}
	return (handle_file_operations(file, fd, scene));
}
