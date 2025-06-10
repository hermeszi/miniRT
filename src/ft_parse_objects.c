/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_objects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngew <jngew@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 14:51:34 by jngew             #+#    #+#             */
/*   Updated: 2025/06/10 11:45:27 by jngew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

void	parse_sphere(char *line, t_scene *scene, int *obj_count)
{
	char	**tokens;

	tokens = ft_split(line, ' ');
	if (!tokens || !tokens[1] || !tokens[2] || !tokens[3] || tokens[4])
		print_error ("Invalid sphere format");
	if (*obj_count == 0)
	{
		scene->objects = malloc(sizeof(t_object) * 100);
		if (!scene->objects)
			print_error ("Memory allocation failed for objects");
	}
	scene->objects[*obj_count].type = OBJ_SPHERE;
	parse_vector(tokens[1], &scene->objects[*obj_count].data.sphere.center);
	scene->objects[*obj_count].data.sphere.diameter = ft_atof(tokens[2]);
	if (scene->objects[*obj_count].data.sphere.diameter <= 0)
		print_error ("Sphere diameter must be positive");
	parse_color(tokens[3], &scene->objects[*obj_count].data.sphere.color);
	free_tokens(tokens);
	(*obj_count)++;
}

void	parse_plane(char *line, t_scene *scene, int *obj_count)
{
	char	**tokens;

	tokens = ft_split(line, ' ');
	if (!tokens || !tokens[1] || !tokens[2] || !tokens[3] || tokens[4])
		print_error ("Invalid plane format");
	if (*obj_count == 0)
	{
		scene->object_count = malloc(sizeof(t_object) * 100);
		if (!scene->objects)
			print_error ("Memory allocation failed for objects");
	}
	scene->objects[*obj_count].type = OBJ_PLANE;
	parse_vector(tokens[1], &scene->objects[*obj_count].data.plane.position);
	parse_norm_vector(tokens[2], &scene->objects[*obj_count].data.plane.normal);
	parse_color(tokens[3], &scene->objects[*obj_count].data.plane.color);
	free_tokens(tokens);
	(*obj_count)++;
}

void	parse_cylinder(char *line, t_scene *scene, int *obj_count)
{
	char	**tokens;

	tokens = ft_split(line, ' ');
	if (!tokens || !tokens[1] || !tokens[2] || !tokens[3] || !tokens[4] || !tokens[5] || tokens[6])
		print_error ("Invalid cylinder format");
	if (*obj_count == 0)
	{
		scene->objects = malloc(sizeof(t_object) * 100);
		if (!scene->objects)
			print_error ("Memory allocation failed for objects");
	}
	scene->objects[*obj_count].type = OBJ_CYLINDER;
	parse_vector(tokens[1], &scene->objects[*obj_count].data.cylinder.center);
	parse_norm_vector(tokens[2], &scene->objects[*obj_count].data.cylinder.axis);
	scene->objects[*obj_count].data.cylinder.diameter = ft_atof(tokens[3]);
	if (scene->objects[*obj_count].data.cylinder.diameter <= 0)
		print_error ("Cylinder diameter must be positive");
	scene->objects[*obj_count].data.cylinder.height = ft_atof(tokens[4]);
	if (scene->objects[*obj_count].data.cylinder.height <= 0)
		print_error ("Cylinder height must be positive");
	parse_color(tokens[5], &scene->objects[*obj_count].data.cylinder.color);
	free_tokens(tokens);
	(*obj_count)++;
}
