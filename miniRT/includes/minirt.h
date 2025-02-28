/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiampav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 09:18:56 by nkiampav          #+#    #+#             */
/*   Updated: 2025/02/27 09:19:01 by nkiampav         ###   ########.fr       */
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

# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 600
# define EPSILON 0.00001
# define MAX_RAY_DEPTH 5

/* Error  message */
# define ERR_ARGS "Invalid number of arguments\n"
# define ERR_FILE "Could not open file\n"
# define ERR_FORMAT "Invalid file format\n"
# define ERR_SCENE "Invalid scene configuration\n"
# define ERR_MEMORY "Memory allocation error\n"

/* Key codes */
# define KEY_ESC 53

/* Event codes */
# define X_EVENT_KEY_PRESS 2
# define X_EVENT_KEY_RELEASE 3
# define X_EVENT_MOUSE_PRESS 4
# define X_EVENT_MOUSE_RELEASE 5
# define X_EVENT_MOUSE_MOVE 6
# define X_EVENT_CLOSE_WINDOW 17

/* Function prototypes */
int     init_mls(void **mlx, void **win);
int     close_window(void *param);
int     key_press(int keycode, void *param);
void    render_scene(t_scene *scene, void *mlx, void *win);
void    my_mlx_pixel_put(void *img, char *addr, int x, int y, int color,
        int bits_per_pixel, int line_length);
bool    check_extension(char *filename, char *ext);
void    free_scene(t_scene *scene);
void    init_scene(t_scene *scene);
void    print_error(char *message);

#endif

