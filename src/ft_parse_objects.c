/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_objects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 14:51:34 by jngew             #+#    #+#             */
/*   Updated: 2025/06/12 20:04:31 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

void	parse_sphere(char *line, t_scene *scene, int *obj_count)
{
	char		**tokens;
	t_object	*new_obj;

	tokens = ft_split(line, ' ');
	if (!tokens || !tokens[1] || !tokens[2] || !tokens[3] || tokens[4])
		print_error_exit ("Invalid sphere format");
	new_obj = ft_calloc(sizeof(t_object), 1);
	if (!new_obj)
		print_error_exit("Memory allocation failed for objects");
	new_obj->type = OBJ_SPHERE;
	parse_vector(tokens[1], &new_obj->data.sphere.center);
	new_obj->data.sphere.diameter = ft_atof(tokens[2]);
	if (new_obj->data.sphere.diameter <= 0)
		print_error_exit ("Sphere diameter must be positive");
	new_obj->data.sphere.radius = new_obj->data.sphere.diameter / 2;
	parse_color(tokens[3], &new_obj->data.sphere.color);
	new_obj->x = *obj_count;
	(*obj_count)++;
	object_add_end(&scene->objects, new_obj);
	free_tokens(tokens);
}

void	parse_plane(char *line, t_scene *scene, int *obj_count)
{
	char		**tokens;
	t_object	*new_obj;

	tokens = ft_split(line, ' ');
	if (!tokens || !tokens[1] || !tokens[2] || !tokens[3] || tokens[4])
		print_error_exit ("Invalid plane format");
	new_obj = ft_calloc(sizeof(t_object), 1);
	if (!new_obj)
		print_error_exit("Memory allocation failed for objects");
	new_obj->type = OBJ_PLANE;
	parse_vector(tokens[1], &new_obj->data.plane.position);
	parse_norm_vector(tokens[2], &new_obj->data.plane.normal);
	parse_color(tokens[3], &new_obj->data.plane.color);
	new_obj->x = *obj_count;
	(*obj_count)++;
	object_add_end(&scene->objects, new_obj);
	free_tokens(tokens);
}

void	parse_cylinder(char *line, t_scene *scene, int *obj_count)
{
	char		**tokens;
	t_object	*new_obj;

	tokens = ft_split(line, ' ');
	if (!tokens || !tokens[1] || !tokens[2] || !tokens[3] || !tokens[4] || !tokens[5] || tokens[6])
		print_error_exit ("Invalid cylinder format");
	new_obj = ft_calloc(sizeof(t_object), 1);
	if (!new_obj)
		print_error_exit("Memory allocation failed for objects");
	new_obj->type = OBJ_CYLINDER;
	parse_vector(tokens[1], &new_obj->data.cylinder.center);
	parse_norm_vector(tokens[2], &new_obj->data.cylinder.axis);
	new_obj->data.cylinder.diameter = ft_atof(tokens[3]);
	if (new_obj->data.cylinder.diameter <= 0)
		print_error_exit ("Cylinder diameter must be positive");
	new_obj->data.cylinder.height = ft_atof(tokens[4]);
	if (new_obj->data.cylinder.height <= 0)
		print_error_exit ("Cylinder height must be positive");
	parse_color(tokens[5], &new_obj->data.cylinder.color);
	new_obj->x = *obj_count;
	(*obj_count)++;
	object_add_end(&scene->objects, new_obj);
	free_tokens(tokens);
}
