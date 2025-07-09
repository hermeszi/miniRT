/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngew <jngew@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:14:39 by jngew             #+#    #+#             */
/*   Updated: 2025/07/09 18:14:57 by jngew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt_bonus.h"

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

static void	process_clean_line(char *line, char *clean, int start, int *y)
{
	collapse_whitespace(line, clean, start, y);
	clean[*y] = '\0';
	free(line);
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
		free(line);
		return (ft_strdup(""));
	}
	clean = malloc(ft_strlen(line) + 1);
	if (!clean)
	{
		free(line);
		return (print_error("Memory allocation failed in clean_line"), NULL);
	}
	y = 0;
	process_clean_line(line, clean, x, &y);
	return (clean);
}

void	cleanup_remaining_lines(int fd, char *line)
{
	while (line != NULL)
	{
		free(line);
		line = get_next_line(fd);
	}
}
