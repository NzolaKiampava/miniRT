/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiampav <nkiampav@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 09:18:56 by nkiampav          #+#    #+#             */
/*   Updated: 2025/05/01 10:44:04 by nkiampav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include <stdbool.h>
# include <string.h>
# include <errno.h>
# include <float.h>

# include "libft.h"
# include "vector.h"
# include "ray.h"
# include "color.h"
# include "objects.h"
# include "scene.h"
# include "parser.h"

# define WINDOW_WIDTH 1000
# define WINDOW_HEIGHT 900
# define EPSILON 0.00001
# define MAX_RAY_DEPTH 5

/* Error  message */
# define ERR_ARGS "Invalid number of arguments\n"
# define ERR_FILE "Could not open file\n"
# define ERR_FORMAT "Invalid file format\n"
# define ERR_SCENE "Invalid scene configuration\n"
# define ERR_MEMORY "Memory allocation error\n"

/* Key codes */
# define KEY_ESC 65307
# define KEY_LEFT 65361
# define KEY_UP 65362
# define KEY_RIGHT 65363
# define KEY_DOWN 65364
# define KEY_TAB 65289
# define KEY_R 114
# define KEY_PLUS 61
# define KEY_MINUS 45
# define KEY_H 104

/* Event codes */
# define X_EVENT_KEY_PRESS 2
# define X_EVENT_KEY_RELEASE 3
# define X_EVENT_MOUSE_PRESS 4
# define X_EVENT_MOUSE_RELEASE 5
# define X_EVENT_MOUSE_MOVE 6
# define X_EVENT_CLOSE_WINDOW 17

/* Function prototypes */
void	init_mlx(t_scene *scene);
int     close_window(void *param);
int     key_press(int keycode, void *param);
void    render_scene(t_scene *scene, void *mlx, void *win);
void	render(t_scene *scene);
void    my_mlx_pixel_put(void *img, char *addr, int x, int y, int color,
        int bits_per_pixel, int line_length);
bool    check_extension(char *filename, char *ext);
void    print_error(char *message);

// Help Functions
void    display_help(void);
void	display_object_info(t_scene *scene);

// new functions added
void	select_next_object(t_scene *scene);
void	toggle_rotation_mode(t_scene *scene);
void	handle_arrow_keys(int keycode, t_scene *scene);
void	apply_translation(t_object *obj, int keycode, double step);
void	apply_rotation(t_object *obj, int keycode, double step);
void	handle_resize(int keycode, t_scene *scene);
void	resize_sphere(t_sphere *sphere, int keycode, double step);
void	resize_cylinder(t_cylinder *cylinder, int keycode, double step, t_scene *scene);
void	toggle_resize_mode(t_scene *scene);

#endif

