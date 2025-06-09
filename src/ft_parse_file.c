/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 17:46:22 by myuen             #+#    #+#             */
/*   Updated: 2025/06/09 21:30:30 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

t_scene	*parse_rt_file(char *filename)
{
	t_scene		*scene;
	int			fd;
	char		*line;

	scene = malloc(sizeof(t_scene));
	if (!scene)
		return (NULL);
	//init_scene(scene);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		print_error("Could not open file.");
		exit(EXIT_FAILURE);
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s",line);
		free(line);
	}
	close(fd);
	return (scene);
}