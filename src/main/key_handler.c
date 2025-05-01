/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiampav <nkiampav@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 10:15:48 by nkiampav          #+#    #+#             */
/*   Updated: 2025/05/01 11:27:35 by nkiampav         ###   ########.fr       */
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
	if (keycode == KEY_H)
	{
		if (scene->num_objects > 0 && 
			scene->selected_obj_index >= 0 && 
			scene->selected_obj_index < scene->num_objects)
		{
			t_object *obj = scene->objects[scene->selected_obj_index];
			if (obj->type == OBJ_CYLINDER)
			{
				toggle_resize_mode(scene);
			}
			else
			{
				printf("Height toggle only applies to cylinders\n");
			}
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
		toggle_rotation_mode(scene);
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
 * Selects the next object in the scene for manipulation
 * @param scene Scene pointer
 */
void	select_next_object(t_scene *scene)
{
	scene->selected_obj_index = (scene->selected_obj_index + 1) 
		% scene->num_objects;
	/*
    printf("Selected object %d (Type: %d)\n", 
		scene->selected_obj_index, 
		scene->objects[scene->selected_obj_index]->type);
    */
	render(scene);
}

/**
 * Toggles between rotation and translation mode
 * @param scene Scene pointer
 */
void	toggle_rotation_mode(t_scene *scene)
{
	scene->rotation_mode = !scene->rotation_mode;
	//printf("%s mode activated\n", scene->rotation_mode ? "Rotation" : "Translation");
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
	step = 1.0; // Default step for translation/rotation
	
	if (scene->rotation_mode)
	{
		// Rotation mode - only for planes and cylinders (not spheres)
		if (obj->type == OBJ_SPHERE)
		{
			printf("Cannot rotate a sphere\n");
			return ;
		}
		apply_rotation(obj, keycode, step);
	}
	else
	{
		// Translation mode
		apply_translation(obj, keycode, step);
	}
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

/**
 * Handles object resizing
 * @param keycode The key code
 * @param scene Scene pointer
 */
void	handle_resize(int keycode, t_scene *scene)
{
	t_object	*obj;
	double		step;

	if (scene->num_objects == 0 || scene->selected_obj_index < 0)
		return ;
	obj = scene->objects[scene->selected_obj_index];
	step = 0.1; // Default step for resizing
	
	if (obj->type == OBJ_SPHERE)
		resize_sphere((t_sphere *)obj->data, keycode, step);
	else if (obj->type == OBJ_CYLINDER)
		resize_cylinder((t_cylinder *)obj->data, keycode, step, scene);
	
	render(scene);
}

/**
 * Resizes a sphere object
 * @param sphere Sphere to resize
 * @param keycode The key code
 * @param step Step size for resizing
 */
void	resize_sphere(t_sphere *sphere, int keycode, double step)
{
	if (keycode == KEY_PLUS)
		sphere->diameter += step * 2;
	else if (keycode == KEY_MINUS && sphere->diameter > step * 2)
		sphere->diameter -= step * 2;
	
	//printf("Sphere diameter: %.2f\n", sphere->diameter);
}

/**
 * Resizes a cylinder object
 * @param cylinder Cylinder to resize
 * @param keycode The key code
 * @param step Step size for resizing
 */
void	resize_cylinder(t_cylinder *cylinder, int keycode, double step, t_scene *scene)
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
	/*
	printf("Cylinder diameter: %.2f, height: %.2f\n", 
		cylinder->diameter, cylinder->height);
    */
}

/**
 * Toggles between height and diameter resize mode for cylinders
 * @param scene Scene pointer
 */
void	toggle_resize_mode(t_scene *scene)
{
	scene->resize_height_mode = !scene->resize_height_mode;
	/*
    printf("Resize mode: %s\n", 
		scene->resize_height_mode ? "Height" : "Diameter");
    */
}