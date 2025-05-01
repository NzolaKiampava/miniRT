/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiampav <nkiampav@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 12:08:04 by nkiampav          #+#    #+#             */
/*   Updated: 2025/05/01 09:54:33 by nkiampav         ###   ########.fr       */
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

	scene->lights = NULL;
	scene->num_lights = 0;
	scene->max_lights = 0;
	
	// MiniLibX pointers
	scene->mlx = NULL;
	scene->win = NULL;

	// Initialize object manipulation
	scene->selected_obj_index = 0;          // select first object by default
	scene->rotation_mode = false;
	scene->resize_height_mode = false;
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

t_color scene_calculate_lighting(t_scene *scene, t_hit_info hit)
{
    t_color final_color = color_create(0, 0, 0);
    t_color ambient_color;
    t_color diffuse_color;
	t_color	specular_color;
    t_vec3 light_dir;
    double light_distance;
    double diffuse_intensity;
	double	Specular_intensity;
    int i;

    // Ambient lighting: Apply ambient light to the object's color
    ambient_color = color_multiply_colors(hit.color, scene->ambient.color);
    ambient_color = color_multiply(ambient_color, scene->ambient.ratio);
    final_color = ambient_color;
	
    // Diffuse lighting
    for (i = 0; i < scene->num_lights; i++)
    {
        // Calculate light direction and distance
        light_dir = vec3_normalize(vec3_subtract(scene->lights[i].position, hit.point));
        light_distance = vec3_length(vec3_subtract(scene->lights[i].position, hit.point));

        // Check if point is in shadow
        if (!scene_is_in_shadow(scene, hit.point, light_dir, light_distance))
        {
            // Calculate diffuse lighting
            diffuse_intensity = fmax(vec3_dot(hit.normal, light_dir), 0.0);

            // Combine object color with light color
            diffuse_color = color_multiply_colors(hit.color, scene->lights[i].color);
            diffuse_color = color_multiply(diffuse_color, diffuse_intensity * scene->lights[i].brightness);

            final_color = color_add(final_color, diffuse_color);

			// Specular (Phone model)
			t_vec3	view_dir = vec3_normalize(vec3_subtract(scene->camera.position, hit.point));
			t_vec3	reflect_dir = vec3_reflect(vec3_multiply(light_dir, -1), hit.normal);
			Specular_intensity = pow(fmax(vec3_dot(view_dir, reflect_dir), 0.0), 32);   // shininess = 32
			specular_color = color_multiply(scene->lights[i].color, Specular_intensity * scene->lights[i].brightness);
			final_color = color_add(final_color, specular_color);
		}
    }
    return color_clamp(final_color);
}
