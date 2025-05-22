/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiampav <nkiampav@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 09:20:08 by nkiampav          #+#    #+#             */
/*   Updated: 2025/05/01 12:22:59 by nkiampav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "vector.h"
# include "color.h"
# include "objects.h"
# include <mlx.h>

typedef struct s_camera
{
	t_vec3	position;
	t_vec3	orientation;
	double	fov;
}	t_camera;

typedef struct s_light
{
	t_vec3	position;
	double	brightness;
	t_color	color;
}	t_light;

typedef struct s_ambient
{
	double	ratio;
	t_color	color;
}	t_ambient;

// new typedef implemented
typedef struct s_ray_casting
{
	t_vec3	viewport_u;
	t_vec3	viewport_v;
	t_vec3	viewport_lower_left;
	t_vec3	horizontal;
	t_vec3	vertical;
	t_vec3	origin;
	double	aspect_ratio;
	double	viewport_height;
	double	viewport_width;
}	t_ray_casting;

typedef struct s_mlx_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_mlx_img;

typedef struct s_scene
{
	t_ambient	ambient;
	t_camera	camera;
	t_object	**objects;
	t_light		*lights;
	int			num_lights;
	int			max_lights;
	int			num_objects;
	int			max_objects;
	void		*mlx;
	void		*win;
	t_mlx_img	img;
	int			selected_obj_index;
	bool		rotation_mode;
	bool		resize_height_mode;
}	t_scene;

// Scene initialization and management
void	scene_init(t_scene *scene);
void	scene_free(t_scene *scene);
int		scene_add_object(t_scene *scene, t_object *obj);
int		scene_add_light(t_scene *scene, t_light light);

// Scene rendering
t_color	scene_trace_ray(t_scene *scene, t_ray ray, int depth);
t_color	scene_calculate_lighting(t_scene *scene, t_hit_info hit);
int		scene_is_in_shadow(t_scene *scene, t_vec3 point,
			t_vec3 light_dir, double light_distance);

// Scene transformations
void	scene_rotate_camera(t_scene *scene, t_vec3 rotation);
void	scene_translate_camera(t_scene *scene, t_vec3 translation);

#endif
