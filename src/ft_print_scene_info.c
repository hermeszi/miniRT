/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_scene_info.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 14:40:18 by jngew             #+#    #+#             */
/*   Updated: 2025/06/12 17:04:48 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

static void	print_objs(t_object *obj)
{
	int	index = 0;

	while (obj)
	{
		printf("Object %d: ", index++);
		if (obj->type == OBJ_SPHERE)
		{
			printf("Sphere — center ");
			print_vec3(obj->data.sphere.center);
			printf(", diameter %.2f, color ", obj->data.sphere.diameter);
			print_color(obj->data.sphere.color);
		}
		else if (obj->type == OBJ_PLANE)
		{
			printf("Plane — point ");
			print_vec3(obj->data.plane.position);
			printf(", normal ");
			print_vec3(obj->data.plane.normal);
			printf(", color ");
			print_color(obj->data.plane.color);
		}
		else if (obj->type == OBJ_CYLINDER)
		{
			printf("Cylinder — center ");
			print_vec3(obj->data.cylinder.center);
			printf(", orientation ");
			print_vec3(obj->data.cylinder.axis);
			printf(", diameter %.2f, height %.2f, color ",
				obj->data.cylinder.diameter, obj->data.cylinder.height);
			print_color(obj->data.cylinder.color);
		}
		else
		{
			printf("Unknown object type.");
		}
		printf("\n");
		obj = obj->next;
	}
	printf("\n--\n");
}

void	print_scene_info(t_scene *scene)
{
	printf("== Scene Overview ==\n");
	printf("Ambient: ratio %.2f, color ", scene->ambient.ratio);
	print_color(scene->ambient.color);
	printf("\n");
	printf("Camera: position ");
	print_vec3(scene->camera.position);
	printf(", direction ");
	print_vec3(scene->camera.orientation);
	printf(", FOV %d\n", scene->camera.fov);
	printf("Light: position ");
	print_vec3(scene->light.position);
	printf(", brightness %.2f, color ", scene->light.brightness);
	print_color(scene->light.color);
	printf("\n--\n");
	print_objs(scene->objects);
	printf("Total Objs: %d\n", scene->object_count);
	printf("== Scene Overview End ==\n\n");
}
