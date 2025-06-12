/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_scene_info.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 14:40:18 by jngew             #+#    #+#             */
/*   Updated: 2025/06/12 18:54:41 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

static void	print_sphere(t_sphere sphere, int index)
{
	printf("Object%3d: Sphere   — center ", index);
	print_vec3(sphere.center);
	printf(", diameter %.2f, color ", sphere.diameter);
	print_color(sphere.color);
	printf("\n");
}

static void	print_plane(t_plane plane, int index)
{
	printf("Object%3d: Plane    — point ", index);
	print_vec3(plane.position);
	printf(", normal ");
	print_vec3(plane.normal);
	printf(", color ");
	print_color(plane.color);
	printf("\n");
}

static void	print_cylinder(t_cylinder cylinder, int index)
{
	printf("Object%3d: Cylinder — center ", index);
	print_vec3(cylinder.center);
	printf(", orientation ");
	print_vec3(cylinder.axis);
	printf(", diameter %.2f, height %.2f, color ",
		cylinder.diameter, cylinder.height);
	print_color(cylinder.color);
	printf("\n");
}

static void	print_object(t_object *obj, int index)
{
	if (obj->type == OBJ_SPHERE)
		print_sphere(obj->data.sphere, index);
	else if (obj->type == OBJ_PLANE)
		print_plane(obj->data.plane, index);
	else if (obj->type == OBJ_CYLINDER)
		print_cylinder(obj->data.cylinder, index);
	else
		printf("Object %d: Unknown object type.\n", index);
}

static void	print_objs(t_object *obj)
{
	int	index;

	index = 0;
	while (obj)
	{
		print_object(obj, index++);
		obj = obj->next;
	}
	printf("\n--\n");
}

void	print_scene_info(t_scene *scene)
{
	printf("== Scene Overview ==\n");
	printf("Ambient: ratio    %.2f, color ", scene->ambient.ratio);
	print_color(scene->ambient.color);
	printf("\n");
	printf("Camera : position ");
	print_vec3(scene->camera.position);
	printf(", direction ");
	print_vec3(scene->camera.orientation);
	printf(", FOV %d\n", scene->camera.fov);
	printf("Light  : position ");
	print_vec3(scene->light.position);
	printf(", brightness %.2f, color ", scene->light.brightness);
	print_color(scene->light.color);
	printf("\n--\n");
	print_objs(scene->objects);
	printf("Total Objs: %d\n", scene->object_count);
	printf("== Scene Overview End ==\n\n");
}
