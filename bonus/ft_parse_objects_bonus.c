/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_objects_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 14:51:34 by jngew             #+#    #+#             */
/*   Updated: 2025/07/04 19:49:27 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt_bonus.h"

void	parse_sphere(char *line, t_scene *scene, int *obj_count)
{
	char		**tokens;
	t_object	*new_obj;

	tokens = ft_split(line, ' ');
	if (!tokens || !tokens[1] || !tokens[2] || !tokens[3] || tokens[4])
		print_error_exit("Invalid format: <center> <diameter> <color>");
	new_obj = ft_calloc(sizeof(t_object), 1);
	if (!new_obj)
		print_error_exit("Memory allocation failed for objects");
	new_obj->type = OBJ_SPHERE;
	parse_vector(tokens[1], &new_obj->u_data.sphere.center);
	new_obj->u_data.sphere.diameter = get_validated_double(tokens[2]);
	if (new_obj->u_data.sphere.diameter <= 0)
		print_error_exit("Sphere diameter must be positive");
	new_obj->u_data.sphere.radius = new_obj->u_data.sphere.diameter / 2;
	parse_color(tokens[3], &new_obj->u_data.sphere.color);
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
		print_error_exit("Invalid format: <point> <normal> <color>");
	new_obj = ft_calloc(sizeof(t_object), 1);
	if (!new_obj)
		print_error_exit("Memory allocation failed for objects");
	new_obj->type = OBJ_PLANE;
	parse_vector(tokens[1], &new_obj->u_data.plane.position);
	parse_norm_vector(tokens[2], &new_obj->u_data.plane.normal);
	parse_color(tokens[3], &new_obj->u_data.plane.color);
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
	if (!tokens || !tokens[1] || !tokens[2] || !tokens[3] || !tokens[4]
		|| !tokens[5] || tokens[6])
		print_error_exit("Invalid format: <center> <axis> <dia> <h> <color>");
	new_obj = ft_calloc(sizeof(t_object), 1);
	if (!new_obj)
		print_error_exit("Memory allocation failed for objects");
	new_obj->type = OBJ_CYLINDER;
	parse_vector(tokens[1], &new_obj->u_data.cylinder.center);
	parse_norm_vector(tokens[2], &new_obj->u_data.cylinder.axis);
	new_obj->u_data.cylinder.diameter = get_validated_double(tokens[3]);
	if (new_obj->u_data.cylinder.diameter <= 0)
		print_error_exit("Cylinder diameter must be positive");
	new_obj->u_data.cylinder.height = get_validated_double(tokens[4]);
	if (new_obj->u_data.cylinder.height <= 0)
		print_error_exit("Cylinder height must be positive");
	parse_color(tokens[5], &new_obj->u_data.cylinder.color);
	new_obj->x = *obj_count;
	(*obj_count)++;
	object_add_end(&scene->objects, new_obj);
	free_tokens(tokens);
}
