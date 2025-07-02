/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngew <jngew@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 18:02:19 by jngew             #+#    #+#             */
/*   Updated: 2025/07/02 18:30:30 by jngew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

static int	skip_whitespace(const char *line)
{
	int	x;

	x = 0;
	while (line[x] && (line[x] == ' ' || line[x] == '\t'))
		x++;
	return (x);
}

static void	collapse_whitespace(const char *line, char *clean, int x, int *y)
{
	while (line[x])
	{
		if (line[x] == ' ' || line[x] == '\t')
		{
			clean[(*y)++] = ' ';
			while (line[x] && (line[x] == ' ' || line[x] == '\t'))
				x++;
		}
		else
			clean[(*y)++] = line[x++];
	}
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
	x = skip_whitespace(line);
	if (!line[x])
	{
		free (line);
		return (ft_strdup(""));
	}
	clean = malloc(ft_strlen(line) + 1);
	if (!clean)
		print_error_exit ("Memory allocation failed");
	y = 0;
	collapse_whitespace(line, clean, x, &y);
	clean[y] = '\0';
	free (line);
	return (clean);
}

static void	parse_helper(char *line, t_scene *scene, int *obj_count)
{
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
			continue ;
		}
		parse_helper(line, scene, obj_count);
		free (line);
		line = get_next_line(fd);
		if (line)
			line = clean_line(line);
	}
	scene->object_count = *obj_count;
}
