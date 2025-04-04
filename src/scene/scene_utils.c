/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiampav <nkiampav@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 11:09:39 by nkiampav          #+#    #+#             */
/*   Updated: 2025/04/04 11:12:09 by nkiampav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	scene_free(t_scene *scene)
{
	int	i;

	// Free objects
	if (scene->objects)
	{
		for (i = 0; i < scene->num_objects; i++)
		{
			if (scene->objects[i])
			{
				object_free(scene->objects[i]);
				scene->objects[i] = NULL;
			}
		}
		free(scene->objects);
		scene->objects = NULL;
	}

	// Free lights
	if (scene->lights)
	{
		free(scene->lights);
		scene->lights = NULL;
	}

	// Close MiniLibX window and connection
	if (scene->win && scene->mlx)
		mlx_destroy_window(scene->mlx, scene->win);
	if (scene->mlx)
	{
		mlx_destroy_display(scene->mlx);
		free(scene->mlx);
	}
}

void	scene_rotate_camera(t_scene *scene, t_vec3 rotation)
{
	// Rotate camera orientation vector
	scene->camera.orientation = vec3_rotate_x(scene->camera.orientation, rotation.x);
	scene->camera.orientation = vec3_rotate_y(scene->camera.orientation, rotation.y);
	scene->camera.orientation = vec3_rotate_z(scene->camera.orientation, rotation.z);
}

void	scene_translate_camera(t_scene *scene, t_vec3 translation)
{
	// Translate camera position
	scene->camera.position = vec3_add(scene->camera.position, translation);
}

int	scene_is_in_shadow(t_scene *scene, t_vec3 point, t_vec3 light_dir, double light_distance)
{
	t_ray		shadow_ray;
	t_hit_info	shadow_hit;

	// Create shadow ray slightly offset from surface to avoid self-intersection
	shadow_ray.origin = vec3_add(point, vec3_multiply(light_dir, EPSILON));
	shadow_ray.direction = light_dir;

	// Check for intersection with any object
	if (ray_intersect_any(shadow_ray, (void **)scene->objects, scene->num_objects, &shadow_hit))
	{
		// If intersection exists and is closer than the light source
		if (shadow_hit.t < light_distance)
			return (1);
	}

	return (0);
}