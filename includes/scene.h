/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiampav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 09:20:08 by nkiampav          #+#    #+#             */
/*   Updated: 2025/02/27 09:20:09 by nkiampav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "vector.h"
# include "color.h"
# include "objects.h"
# include <mlx.h>

typedef struct  s_camera
{
    t_vec3  position;
    t_vec3  orientation;
    double  fov;
}   t_camera;

typedef struct  s_light
{
    t_vec3  position;
    double  brightness;
    t_color color;
}   t_light;

typedef struct  s_ambient
{
    double  ratio;
    t_color color;
}   t_ambient;

typedef struct  s_scene
{
    t_ambient   ambient;
    t_camera    camera;
    t_light     *lights;
    int         num_lights;
    t_object    **objects;
    int         num_objects;
    int         max_objects;
    int         max_lights;
    void        *mlx;               // mlx connection  pointer
    void        *win;               // window pointer
}   t_scene;    


// Scene initialization and management
void    scene_init(t_scene *scene);
void    scene_free(t_scene *scene);
int     scene_add_object(t_scene *scene, t_object *obj);
int     scene_add_light(t_scene *scene, t_light light);

// Scene rendering
t_color scene_trace_ray(t_scene *scene, t_ray ray, int depth);
t_color scene_calculate_lighting(t_scene *scene, t_hit_info hit);
int scene_is_in_shadow(t_scene *scene, t_vec3 point, t_vec3 light_dir, double light_distance);

// Scene transformations
void    scene_rotate_camera(t_scene *scene, t_vec3 rotation);
void    scene_translate_camera(t_scene *scene, t_vec3 translation);

#endif
