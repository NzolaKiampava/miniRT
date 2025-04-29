/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiampav <nkiampav@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 12:20:15 by nkiampav          #+#    #+#             */
/*   Updated: 2025/04/09 13:57:26 by nkiampav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

/**
 * Parse ambient lighting from the scene file
 * Format: A ratio R,G,B
 * Returns 0 on success, -1 on error
 */
int	parse_ambient(char **elements, t_scene *scene)
{
	int			count;
	t_color		color;
	double		ratio;

	count = count_elements(elements);
	if (count != 3)
		return (print_error("Invalid ambient lighting format\n"), -1);
	ratio = parse_double(elements[1]);
	color = parse_color(elements[2]);
	if (ratio < 0.0 || ratio > 1.0 || !validate_color_values(color))
		return (print_error("Invalid ambient parameters\n"), -1);
	scene->ambient.ratio = ratio;
	scene->ambient.color = color;
	return (0);
}

/**
 * Parse camera from the scene file
 * Format: C x,y,z nx,ny,nz fov
 * Returns 0 on success, -1 on error
 */
int	parse_camera(char **elements, t_scene *scene)
{
	int			count;
	t_vec3		position;
	t_vec3		orientation;
	double		fov;

	count = count_elements(elements);
	if (count != 4)
		return (print_error("Invalid camera format\n"), -1);
	position = parse_vector(elements[1]);
	orientation = parse_vector(elements[2]);
	fov = parse_double(elements[3]);
	if (!validate_vector_normalized(orientation) || fov <= 0 || fov >= 180)
		return (print_error("Invalid camera parameters\n"), -1);
	orientation = vec3_normalize(orientation);
	scene->camera.position = position;
	scene->camera.orientation = orientation;
	scene->camera.fov = fov;
	return (0);
}

/**
 * Parse light from the scene file
 * Format: L x,y,z brightness [R,G,B]
 * Returns 0 on success, -1 on error
 */
int	parse_light(char **elements, t_scene *scene)
{
	int			count;
	t_light		light;

	count = count_elements(elements);
	if (count != 3 && count != 4)
		return (print_error("Invalid light format\n"), -1);
	light.position = parse_vector(elements[1]);
	light.brightness = parse_double(elements[2]);
	if (count == 4)
		light.color = parse_color(elements[3]);
	else
		light.color = color_create(255, 255, 255);
	if (light.brightness < 0.0 || light.brightness > 1.0
		|| !validate_color_values(light.color))
		return (print_error("Invalid light parameters\n"), -1);
	if (scene_add_light(scene, light) < 0)
		return (print_error(ERR_MEMORY), -1);
	return (0);
}
