/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngew <jngew@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 18:02:19 by jngew             #+#    #+#             */
/*   Updated: 2025/07/09 16:05:24 by jngew            ###   ########.fr       */
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

char *clean_line(char *line)
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
        free(line);
        return (ft_strdup(""));
    }
    clean = malloc(ft_strlen(line) + 1);
    if (!clean)
    {
        free(line);
        print_error("Memory allocation failed in clean_line");
        return (NULL);
    }
    y = 0;
    collapse_whitespace(line, clean, x, &y);
    clean[y] = '\0';
    free(line);
    return (clean);
}


static int	parse_helper(char *line, t_scene *scene, int *obj_count)
{
	if (!ft_strncmp(line, "A ", 2))
		return (parse_ambient(line, scene));
	else if (!ft_strncmp(line, "C ", 2))
		return (parse_camera(line, scene));
	else if (!ft_strncmp(line, "L ", 2))
		return (parse_light(line, scene));
	else if (!ft_strncmp(line, "sp ", 3))
		return (parse_sphere(line, scene, obj_count));
	else if (!ft_strncmp(line, "pl ", 3))
		return (parse_plane(line, scene, obj_count));
	else if (!ft_strncmp(line, "cy ", 3))
		return (parse_cylinder(line, scene, obj_count));
	return (print_error("Invalid element identifier in scene file."));
}

int	parse_lines(int fd, t_scene *scene, int *obj_count)
{
	char	*line;
	char	*cleaned_line;
	int		status;

	status = 0;
	line = get_next_line(fd);
	while (line)
	{
		cleaned_line = clean_line(line);
		if (!cleaned_line)
			return (1);
		if (cleaned_line[0] != '\0')
		{
			status = parse_helper(cleaned_line, scene, obj_count);
		}
		free(cleaned_line);
		if (status != 0)
		{
			while ((line = get_next_line(fd)) != NULL)
				free(line);
			return (status);
		}
		line = get_next_line(fd);
	}
	return (0);
}
