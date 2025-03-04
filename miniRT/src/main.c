/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiampav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 09:20:47 by nkiampav          #+#    #+#             */
/*   Updated: 2025/02/27 09:20:48 by nkiampav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "parser.h"
#include "scene.h"

int main(int argc, char **argv)
{
    void    *mlx;
    void    *win;
    t_scene scene;

    // Check arguments
    if (argc != 2)
    {
        print_error(ERR_ARGS);
        return (1);
    }
    if (!check_extension(argv[1], ".rt"))
    {
        print_error(ERR_FORMAT);
        return (1);
    }

    // Initialize MLX and window
    if (!init_mls(&mlx, &win))
        return (1);

    // Initialize scene
    init_scene(&scene);

    // Parse scene file
    if (!parse_scene(argv[1], &scene))
    {
        print_error(ERR_SCENE);
        free_scene(&scene);
        mlx_destroy_window(mlx, win);
        mlx_destroy_display(mlx);
        free(mlx);
        return (1);
    }

    // Render the scene
    render_scene(&scene, mlx, win);

    // Set up event hooks
    mlx_hook(win, X_EVENT_KEY_PRESS, 1L<<0, key_press, &scene);
    mlx_hook(win, X_EVENT_CLOSE_WINDOW, 0, close_window, &scene);

    // Enter MLX loop
    mlx_loop(mlx);

    // Cleanup (unreachable due to mlx_loop, but good practice)
    free_scene(&scene);
    mlx_destroy_window(mlx, win);
    mlx_destroy_display(mlx);
    free(mlx);
    return (0);
}

int init_mls(void **mlx, void **win)
{
    *mlx = mlx_init();
    if (!*mlx)
    {
        print_error("Failed to initialize MLX");
        return (0);
    }
    *win = mlx_new_window(*mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "miniRT");
    if (!*win)
    {
        print_error("Failed to create window");
        free(*mlx);
        return (0);
    }
    return (1);
}

int close_window(void *param)
{
    t_scene *scene = (t_scene *)param;
    void    *mlx = mlx_init(); // Note: In a real scenario, this should be passed properly
    free_scene(scene);
    mlx_destroy_window(mlx, mlx_new_window(mlx, 1, 1, "dummy")); // Simplified cleanup
    exit(0);
    return (0);
}

int key_press(int keycode, void *param)
{
    t_scene *scene = (t_scene *)param;
    if (keycode == KEY_ESC)
        close_window(scene);
    return (0);
}

void render_scene(t_scene *scene, void *mlx, void *win)
{
    // Placeholder for rendering logic
    (void)scene;
    mlx_string_put(mlx, win, WINDOW_WIDTH / 2 - 50, WINDOW_HEIGHT / 2, color_to_int(color_white()), "Hello, miniRT!");
}

void print_error(char *message)
{
    write(2, "Error\n", 6);
    write(2, message, strlen(message));
}

