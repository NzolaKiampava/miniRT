/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting_calculus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiampav <nkiampav@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:46:27 by nkiampav          #+#    #+#             */
/*   Updated: 2025/05/22 16:15:12 by nkiampav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_color	calculate_ambient_lighting(t_scene *scene, t_color object_color)
{
	t_color	ambient_color;

	ambient_color = color_multiply_colors(object_color,
			scene->ambient.color);
	ambient_color = color_multiply(ambient_color, scene->ambient.ratio);
	return (ambient_color);
}

t_color	calculate_diffuse_lighting(t_light light, t_hit_info hit,
	t_vec3 light_dir)
{
	t_color	diffuse_color;
	double	diffuse_intensity;

	diffuse_intensity = fmax(vec3_dot(hit.normal, light_dir), 0.0);
	diffuse_color = color_multiply_colors(hit.color, light.color);
	diffuse_color = color_multiply(diffuse_color,
			diffuse_intensity * light.brightness);
	return (diffuse_color);
}

t_color	calculate_specular_lighting(t_light light, t_hit_info hit,
	t_vec3 light_dir, t_vec3 camera_pos)
{
	t_color	specular_color;
	t_vec3	view_dir;
	t_vec3	reflect_dir;
	double	specular_intensity;

	view_dir = vec3_normalize(vec3_subtract(camera_pos, hit.point));
	reflect_dir = vec3_reflect(vec3_multiply(light_dir, -1), hit.normal);
	specular_intensity = pow(fmax(vec3_dot(view_dir,
					reflect_dir), 0.0), 32);
	specular_color = color_multiply(light.color,
			specular_intensity * light.brightness);
	return (specular_color);
}

t_color	process_single_light(t_scene *scene, t_hit_info hit, int light_index)
{
	t_color	light_contribution;
	t_vec3	light_dir;
	double	light_distance;
	t_light	current_light;

	light_contribution = color_create(0, 0, 0);
	current_light = scene->lights[light_index];
	light_dir = vec3_normalize(vec3_subtract(current_light.position,
				hit.point));
	light_distance = vec3_length(vec3_subtract(current_light.position,
				hit.point));
	if (!scene_is_in_shadow(scene, hit.point, light_dir, light_distance))
	{
		light_contribution = color_add(light_contribution,
				calculate_diffuse_lighting(current_light, hit, light_dir));
		light_contribution = color_add(light_contribution,
				calculate_specular_lighting(current_light, hit,
					light_dir, scene->camera.position));
	}
	return (light_contribution);
}

t_color	scene_calculate_lighting(t_scene *scene, t_hit_info hit)
{
	t_color	final_color;
	t_color	lc;
	int		i;

	final_color = calculate_ambient_lighting(scene, hit.color);
	i = 0;
	while (i < scene->num_lights)
	{
		lc = process_single_light(scene, hit, i);
		final_color = color_add(final_color, lc);
		i++;
	}
	return (color_clamp(final_color));
}
