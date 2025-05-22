/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiampav <nkiampav@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 12:08:04 by nkiampav          #+#    #+#             */
/*   Updated: 2025/05/22 15:56:39 by nkiampav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	scene_init(t_scene *scene)
{
	scene->ambient.ratio = 0.2;
	scene->ambient.color = color_create(255, 255, 255);
	scene->camera.position = vec3_create(-50, 0, 20);
	scene->camera.orientation = vec3_create(0, 0, 1);
	scene->camera.fov = 70;
	scene->objects = NULL;
	scene->num_objects = 0;
	scene->max_objects = 0;
	scene->lights = NULL;
	scene->num_lights = 0;
	scene->max_lights = 0;
	scene->lights = NULL;
	scene->num_lights = 0;
	scene->max_lights = 0;
	scene->mlx = NULL;
	scene->win = NULL;
	scene->selected_obj_index = 0;
	scene->rotation_mode = false;
	scene->resize_height_mode = false;
}

// If no space, allocate initial array or expand
int	scene_add_object(t_scene *scene, t_object *obj)
{
	t_object	**new_objects;

	if (scene->max_objects == 0)
	{
		scene->objects = malloc(sizeof(t_object *) * 10);
		if (!scene->objects)
			return (-1);
		scene->max_objects = 10;
	}
	else if (scene->num_objects >= scene->max_objects)
	{
		new_objects = realloc(scene->objects,
				sizeof(t_object *) * (scene->max_objects + 10));
		if (!new_objects)
			return (-1);
		scene->objects = new_objects;
		scene->max_objects += 10;
	}
	scene->objects[scene->num_objects] = obj;
	scene->num_objects++;
	return (0);
}

// If no space, allocate initial array or expand
int	scene_add_light(t_scene *scene, t_light light)
{
	t_light	*new_lights;

	if (scene->max_lights == 0)
	{
		scene->lights = malloc(sizeof(t_light) * 5);
		if (!scene->lights)
			return (-1);
		scene->max_lights = 5;
	}
	else if (scene->num_lights >= scene->max_lights)
	{
		new_lights = realloc(scene->lights,
				sizeof(t_light) * (scene->max_lights + 5));
		if (!new_lights)
			return (-1);
		scene->lights = new_lights;
		scene->max_lights += 5;
	}
	scene->lights[scene->num_lights] = light;
	scene->num_lights++;
	return (0);
}

// Maximum recursion depth
// Find closest intersection
	// Calculate lighting for the hit point
// Background color if no intersection - Sky blue
t_color	scene_trace_ray(t_scene *scene, t_ray ray, int depth)
{
	t_hit_info	hit;
	t_color		color;

	if (depth > MAX_RAY_DEPTH)
		return (color_create(0, 0, 0));
	if (ray_intersect_any(ray, (void **)scene->objects,
			scene->num_objects, &hit))
	{
		color = scene_calculate_lighting(scene, hit);
		return (color);
	}
	return (color_create(135, 206, 235));
}
