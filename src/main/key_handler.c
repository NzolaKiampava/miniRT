/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiampav <nkiampav@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 10:15:48 by nkiampav          #+#    #+#             */
/*   Updated: 2025/05/09 08:55:23 by nkiampav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

/**
 * Handles keyboard input for key H (toggle resize mode for cylinder)
 * and displays help information
 * @param keycode The key code
 * @param scene Scene pointer
 */
void	handle_key_h(int keycode, t_scene *scene)
{
	t_object	*obj;

	if (keycode == KEY_H)
	{
		if (scene->num_objects > 0
			&& scene->selected_obj_index >= 0
			&& scene->selected_obj_index < scene->num_objects)
		{
			obj = scene->objects[scene->selected_obj_index];
			if (obj->type == OBJ_CYLINDER)
				scene->resize_height_mode = !scene->resize_height_mode;
			else
				printf("Height toggle only applies to cylinders\n");
		}
		else
		{
			printf("No object selected\n");
		}
	}
}

/**
* Handles key press events for object manipulation
* @param keycode The key code
* @param param Scene pointer (cast to t_scene*)
* @return Always returns 0
*/
int	key_press(int keycode, void *param)
{
	t_scene	*scene;

	scene = (t_scene *)param;
	if (keycode == KEY_ESC)
	{
		scene_free(scene);
		exit(0);
	}
	else if (keycode == KEY_TAB)
		select_next_object(scene);
	else if (keycode == KEY_R)
		scene->rotation_mode = !scene->rotation_mode;
	else if (keycode == KEY_H)
		handle_key_h(keycode, scene);
	else if (keycode == KEY_LEFT || keycode == KEY_RIGHT
		|| keycode == KEY_UP || keycode == KEY_DOWN)
		handle_arrow_keys(keycode, scene);
	else if (keycode == KEY_PLUS || keycode == KEY_MINUS)
		handle_resize(keycode, scene);
	display_object_info(scene);
	return (0);
}

/**
* Handles arrow key inputs for object manipulation
* @param keycode The key code
* @param scene Scene pointer
*/
void	handle_arrow_keys(int keycode, t_scene *scene)
{
	t_object	*obj;
	double		step;

	if (scene->num_objects == 0 || scene->selected_obj_index < 0)
		return ;
	obj = scene->objects[scene->selected_obj_index];
	step = 1.0;
	if (scene->rotation_mode)
	{
		if (obj->type == OBJ_SPHERE)
		{
			printf("Cannot rotate a sphere\n");
			return ;
		}
		apply_rotation(obj, keycode, step);
	}
	else
		apply_translation(obj, keycode, step);
	render(scene);
}

/**
* Applies translation to an object based on key input
* @param obj Object to translate
* @param keycode The key code
* @param step Step size for translation
*/
void	apply_translation(t_object *obj, int keycode, double step)
{
	t_vec3	translation;

	translation = vec3_create(0, 0, 0);
	if (keycode == KEY_LEFT)
		translation.x = -step;
	else if (keycode == KEY_RIGHT)
		translation.x = step;
	else if (keycode == KEY_UP)
		translation.y = step;
	else if (keycode == KEY_DOWN)
		translation.y = -step;
	object_translate(obj, translation);
}

/**
* Applies rotation to an object based on key input
* @param obj Object to rotate
* @param keycode The key code
* @param step Step size for rotation (in degrees)
*/
void	apply_rotation(t_object *obj, int keycode, double step)
{
	t_vec3	rotation;

	rotation = vec3_create(0, 0, 0);
	if (keycode == KEY_LEFT)
		rotation.y = step;
	else if (keycode == KEY_RIGHT)
		rotation.y = -step;
	else if (keycode == KEY_UP)
		rotation.x = step;
	else if (keycode == KEY_DOWN)
		rotation.x = -step;
	object_rotate(obj, rotation);
}
