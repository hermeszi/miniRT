/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_objects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngew <jngew@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 14:51:34 by jngew             #+#    #+#             */
/*   Updated: 2025/07/09 16:05:47 by jngew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

int	parse_sphere(char *line, t_scene *scene, int *obj_count)
{
	char		**tokens;
	t_object	*new_obj;
	double		diameter;

	tokens = ft_split(line, ' ');
	if (!tokens)
		return (print_error("Memory allocation failed."));
	if (!tokens[1] || !tokens[2] || !tokens[3] || tokens[4])
		return (pr_er(tokens, "Invalid sphere: sp <center> <diameter> <color>"));
	new_obj = ft_calloc(1, sizeof(t_object));
	if (!new_obj)
		return (pr_er(tokens, "Memory allocation failed for sphere object."));
	new_obj->type = OBJ_SPHERE;
	if (parse_vector(tokens[1], &new_obj->u_data.sphere.center) != 0 ||
		parse_color(tokens[3], &new_obj->u_data.sphere.color) != 0)
	{
		free(new_obj);
		return (pr_er(tokens, "Invalid data in sphere definition."));
	}
	if (get_validated_double(tokens[2], &diameter) != 0)
	{
		free(new_obj);
		return (pr_er(tokens, "Invalid diameter for sphere."));
	}
	if (diameter <= 0)
	{
		free(new_obj);
		return (pr_er(tokens, "Sphere diameter must be positive"));
	}
	new_obj->u_data.sphere.diameter = diameter;
	new_obj->u_data.sphere.radius = diameter / 2.0;
	object_add_end(&scene->objects, new_obj);
	(*obj_count)++;
	free_tokens(tokens);
	return (0);
}

int	parse_plane(char *line, t_scene *scene, int *obj_count)
{
	char		**tokens;
	t_object	*new_obj;

	tokens = ft_split(line, ' ');
	if (!tokens)
		return (print_error("Memory allocation failed for tokens."));
	if (!tokens[1] || !tokens[2] || !tokens[3] || tokens[4])
		return (pr_er(tokens, "Invalid: <point> <normal> <color>"));
	new_obj = ft_calloc(1, sizeof(t_object));
	if (!new_obj)
		return (pr_er(tokens, "Memory allocation failed for plane"));
	new_obj->type = OBJ_PLANE;
	if (parse_vector(tokens[1], &new_obj->u_data.plane.position) != 0
		|| parse_norm_vector(tokens[2], &new_obj->u_data.plane.normal) != 0
		|| parse_color(tokens[3], &new_obj->u_data.plane.color) != 0)
	{
		free(new_obj);
		return (pr_er(tokens, "Invalid data in plane definition."));
	}
	new_obj->x = *obj_count;
	object_add_end(&scene->objects, new_obj);
	(*obj_count)++;
	free_tokens(tokens);
	return (0);
}

int	parse_cylinder(char *line, t_scene *scene, int *obj_count)
{
	char		**tokens;
	t_object	*new_obj;
	double		diameter;
	double		height;

	tokens = ft_split(line, ' ');
	if (!tokens)
		return (print_error("Memory allocation failed for tokens."));
	if (!tokens[1] || !tokens[2] || !tokens[3] || !tokens[4]
		|| !tokens[5] || tokens[6])
		return (pr_er(tokens, "Invalid format: cy <center> <axis> <dia> <h> <color>"));
	new_obj = ft_calloc(1, sizeof(t_object));
	if (!new_obj)
		return (pr_er(tokens, "Memory allocation failed for cylinder object."));
	new_obj->type = OBJ_CYLINDER;
	if (parse_vector(tokens[1], &new_obj->u_data.cylinder.center) != 0
		|| parse_norm_vector(tokens[2], &new_obj->u_data.cylinder.axis) != 0
		|| parse_color(tokens[5], &new_obj->u_data.cylinder.color) != 0)
	{
		free(new_obj);
		return (pr_er(tokens, "Invalid data in cylinder definition."));
	}
	if (get_validated_double(tokens[3], &diameter) != 0
		|| get_validated_double(tokens[4], &height) != 0)
	{
		free(new_obj);
		return (pr_er(tokens, "Invalid number for cylinder dimensions."));
	}
	if (diameter <= 0)
	{
		free(new_obj);
		return (pr_er(tokens, "Cylinder diameter must be positive"));
	}
	if (height <= 0)
	{
		free(new_obj);
		return (pr_er(tokens, "Cylinder height must be positive"));
	}
	new_obj->u_data.cylinder.diameter = diameter;
	new_obj->u_data.cylinder.height = height;
	new_obj->x = *obj_count;
	object_add_end(&scene->objects, new_obj);
	(*obj_count)++;
	free_tokens(tokens);
	return (0);
}
