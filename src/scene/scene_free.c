/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiampav <nkiampav@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:41:42 by nkiampav          #+#    #+#             */
/*   Updated: 2025/05/22 16:43:00 by nkiampav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// Free all objects in the scene
void	scene_free_objects(t_scene *scene)
{
	int	i;

	if (!scene->objects)
		return ;
	i = 0;
	while (i < scene->num_objects)
	{
		object_free(scene->objects[i]);
		scene->objects[i] = NULL;
		i++;
	}
	free(scene->objects);
	scene->objects = NULL;
}

// Free all lights in the scene
void	scene_free_lights(t_scene *scene)
{
	if (!scene->lights)
		return ;
	free(scene->lights);
	scene->lights = NULL;
}

// Free MLX resources (window and display)
void	scene_free_mlx(t_scene *scene)
{
	if (scene->win && scene->mlx)
		mlx_destroy_window(scene->mlx, scene->win);
	if (scene->mlx)
	{
		mlx_destroy_display(scene->mlx);
		free(scene->mlx);
		scene->mlx = NULL;
	}
}

// Main scene cleanup function
void	scene_free(t_scene *scene)
{
	if (!scene)
		return ;
	scene_free_objects(scene);
	scene_free_lights(scene);
	scene_free_mlx(scene);
}
