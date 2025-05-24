/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiampav <nkiampav@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 08:44:26 by nkiampav          #+#    #+#             */
/*   Updated: 2025/05/24 16:05:28 by nkiampav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

//Handles object resizing
void	handle_resize(int keycode, t_scene *scene)
{
	t_object	*obj;
	double		step;

	if (scene->num_objects == 0 || scene->selected_obj_index < 0)
		return ;
	obj = scene->objects[scene->selected_obj_index];
	step = 0.1;
	if (obj->type == OBJ_SPHERE)
		resize_sphere((t_sphere *)obj->data, keycode, step);
	else if (obj->type == OBJ_CYLINDER)
		resize_cylinder((t_cylinder *)obj->data, keycode, step, scene);
	render(scene);
}

//Resizes a sphere object
void	resize_sphere(t_sphere *sphere, int keycode, double step)
{
	if (keycode == KEY_PLUS)
		sphere->diameter += step * 2;
	else if (keycode == KEY_MINUS && sphere->diameter > step * 2)
		sphere->diameter -= step * 2;
}

//Resizes a cylinder object
void	resize_cylinder(t_cylinder *cylinder, int keycode, double step,
				t_scene *scene)
{
	if (keycode == KEY_PLUS)
	{
		if (scene->resize_height_mode)
			cylinder->height += step;
		else
			cylinder->diameter += step;
	}
	else if (keycode == KEY_MINUS)
	{
		if (scene->resize_height_mode)
		{
			if (cylinder->height > step)
				cylinder->height -= step;
		}
		else if (cylinder->diameter > step)
			cylinder->diameter -= step;
	}
}

//Selects the next object in the scene for manipulation
void	select_next_object(t_scene *scene)
{
	scene->selected_obj_index = (scene->selected_obj_index + 1)
		% scene->num_objects;
	render(scene);
}
