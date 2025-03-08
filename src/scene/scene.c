/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiampav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 12:08:04 by nkiampav          #+#    #+#             */
/*   Updated: 2025/03/05 12:08:05 by nkiampav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	scene_init(t_scene *scene)
{
	// Initialize scene with default values
	scene->ambient.ratio = 0.2;
	scene->ambient.color = color_create(255, 255, 255);
	
	// Initialize camera with default values
	scene->camera.position = vec3_create(-50, 0, 20);
	scene->camera.orientation = vec3_create(0, 0, 1);
	scene->camera.fov = 70;
	
	// Initialize objects and lights arrays
	scene->objects = NULL;
	scene->num_objects = 0;
	scene->max_objects = 0;
	
	scene->lights = NULL;
	scene->num_lights = 0;
	scene->max_lights = 0;
	
	// MiniLibX pointers
	scene->mlx = NULL;
	scene->win = NULL;
}

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
		mlx_destroy_display(scene->mlx);
}

int	scene_add_object(t_scene *scene, t_object *obj)
{
	t_object	**new_objects;

	// If no space, allocate initial array or expand
	if (scene->max_objects == 0)
	{
		scene->objects = malloc(sizeof(t_object *) * 10);
		if (!scene->objects)
			return (-1);
		scene->max_objects = 10;
	}
	else if (scene->num_objects >= scene->max_objects)
	{
		// Expand array when full
		new_objects = realloc(scene->objects, 
			sizeof(t_object *) * (scene->max_objects + 10));
		if (!new_objects)
			return (-1);
		scene->objects = new_objects;
		scene->max_objects += 10;
	}

	// Add object
	scene->objects[scene->num_objects] = obj;
	scene->num_objects++;

	return (0);
}

int	scene_add_light(t_scene *scene, t_light light)
{
	t_light	*new_lights;

	// If no space, allocate initial array or expand
	if (scene->max_lights == 0)
	{
		scene->lights = malloc(sizeof(t_light) * 5);
		if (!scene->lights)
			return (-1);
		scene->max_lights = 5;
	}
	else if (scene->num_lights >= scene->max_lights)
	{
		// Expand array when full
		new_lights = realloc(scene->lights, 
			sizeof(t_light) * (scene->max_lights + 5));
		if (!new_lights)
			return (-1);
		scene->lights = new_lights;
		scene->max_lights += 5;
	}

	// Add light
	scene->lights[scene->num_lights] = light;
	scene->num_lights++;

	return (0);
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

t_color	scene_trace_ray(t_scene *scene, t_ray ray, int depth)
{
	t_hit_info	hit;
	t_color		color;

	// Maximum recursion depth
	if (depth > MAX_RAY_DEPTH)
		return (color_create(0, 0, 0));

	// Find closest intersection
	if (ray_intersect_any(ray, (void **)scene->objects, scene->num_objects, &hit))
	{
		// Calculate lighting for the hit point
		color = scene_calculate_lighting(scene, hit);
		return (color);
	}

	// Background color if no intersection
	return (color_create(135, 206, 235)); // Sky blue
}

t_color	scene_calculate_lighting(t_scene *scene, t_hit_info hit)
{
	t_color		final_color;
	t_color		ambient_color;
	int			i;
	t_vec3		light_dir;
	double		light_distance;
	double		diffuse_intensity;

	// Ambient lighting
	ambient_color = color_multiply(scene->ambient.color, 
		color_to_scalar(hit.color) * scene->ambient.ratio);

	// Initialize with ambient color
	final_color = ambient_color;

	// Iterate through light sources
	for (i = 0; i < scene->num_lights; i++)
	{
		// Calculate light direction and distance
		light_dir = vec3_normalize(
			vec3_subtract(scene->lights[i].position, hit.point)
		);
		light_distance = vec3_length(
			vec3_subtract(scene->lights[i].position, hit.point)
		);

		// Check if point is in shadow
		if (!scene_is_in_shadow(scene, hit.point, light_dir, light_distance))
		{
			// Calculate diffuse lighting
			diffuse_intensity = fmax(vec3_dot(hit.normal, light_dir), 0.0);
			final_color = color_add(final_color, 
				color_multiply(scene->lights[i].color, 
					color_to_scalar(hit.color) * 
					scene->lights[i].brightness * diffuse_intensity)
			);
		}
	}

	return (color_clamp(final_color));
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