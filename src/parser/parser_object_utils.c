/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_object_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiampav <nkiampav@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 12:59:34 by nkiampav          #+#    #+#             */
/*   Updated: 2025/04/09 13:59:23 by nkiampav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int create_add_cylinder(t_scene *scene, t_vec3 center, t_vec3 axis,
				double diameter, double height, t_color color)
{
	t_cylinder  *cylinder;
	t_object    *obj;

	cylinder = cylinder_create(center, axis, diameter, height, color);
	if (!cylinder)
		return (print_error(ERR_MEMORY), -1);
	obj = object_create(OBJ_CYLINDER, cylinder);
	if (!obj)
	{
		free(cylinder);
		return (print_error(ERR_MEMORY), -1);
	}
	if (add_object_to_scene(scene, obj) == -1)
	{
		object_free(obj);
		return (print_error(ERR_MEMORY), -1);
	}
	return (0);
}

int	add_object_to_scene(t_scene *scene, t_object *obj)
{
	t_object	**new_objects;
	int		i;
	new_objects = malloc(sizeof(t_object *) * (scene->num_objects + 1));
	if (!new_objects)
		return (-1);
	i = 0;
	while (i < scene->num_objects)
	{
		new_objects[i] = scene->objects[i];
		i++;
	}
	new_objects[i] = obj;
	if (scene->objects)
		free(scene->objects);
	scene->objects = new_objects;
	scene->num_objects++;
	return (0);
}
