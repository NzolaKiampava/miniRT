/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiampav <nkiampav@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 09:20:47 by nkiampav          #+#    #+#             */
/*   Updated: 2025/03/21 08:39:52 by nkiampav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	print_error(char *message)
{
	write(2, "Error\n", 6);
	write(2, message, strlen(message));
	exit(1);
}

bool	check_extension(char *filename, char *ext)
{
	char	*dot;

	if (!filename)
		return (false);
	
	dot = ft_strrchr(filename, '.');
	if (!dot)
		return (false);
	
	return (strcmp(dot, ext) == 0);
}

int	close_window(void *param)
{
	t_scene	*scene;

	scene = (t_scene *)param;
	
	// Free scene resources
	scene_free(scene);
	
	// Exit program
	exit(0);
	return (0);
}

int	key_press(int keycode, void *param)
{
	t_scene	*scene;

	scene = (t_scene *)param;
	
	if (keycode == KEY_ESC)
	{
		close_window(scene);
	}
	
	return (0);
}

void	init_mlx(t_scene *scene)
{
	scene->mlx = mlx_init();
	if (!scene->mlx)
		print_error("Failed to initialize MiniLibX\n");
	
	scene->win = mlx_new_window(scene->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "miniRT");
	if (!scene->win)
		print_error("Failed to create window\n");
}

// Utility function to put pixel in image
void	my_mlx_pixel_put(void *img, char *addr, int x, int y, int color,
			int bits_per_pixel, int line_length)
{
	char	*dst;
	(void)img;

	dst = addr + (y * line_length + x * (bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	render(t_scene *scene)
{
	void	*img;
	char	*img_addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		x, y;
	t_color	pixel_color;

	// Debugging
	printf("Number of objects in scene: %d\n", scene->num_objects);
	for (int i = 0; i < scene->num_objects; i++) {
		printf("Object %d, type: %d\n", i, scene->objects[i]->type);
	}

	printf("Camera position: (%.2f, %.2f, %.2f)\n", 
       scene->camera.position.x,
       scene->camera.position.y,
       scene->camera.position.z);
	printf("Camera orientation: (%.2f, %.2f, %.2f)\n", 
       scene->camera.orientation.x,
       scene->camera.orientation.y,
       scene->camera.orientation.z);
	// end debugging code.


	// Create image
	img = mlx_new_image(scene->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	img_addr = mlx_get_data_addr(img, &bits_per_pixel, &line_length, &endian);

	// Render each pixel
	for (y = 0; y < WINDOW_HEIGHT; y++)
	{
		for (x = 0; x < WINDOW_WIDTH; x++)
		{
			// Generate ray for this pixel
			t_ray ray = camera_ray(
				scene->camera.position, 
				scene->camera.orientation, 
				scene->camera.fov, 
				(double)WINDOW_WIDTH / WINDOW_HEIGHT, 
				x, y
			);

			// Trace ray and get color
			pixel_color = scene_trace_ray(scene, ray, 0);

			// Put pixel on image
			my_mlx_pixel_put(
				img, 
				img_addr, 
				x, y, 
				color_to_int(pixel_color), 
				bits_per_pixel, 
				line_length
			);
		}
	}

	// Display image
	mlx_put_image_to_window(scene->mlx, scene->win, img, 0, 0);
	mlx_destroy_image(scene->mlx, img);
}

int	main(int argc, char **argv)
{
	t_scene	scene;

	// Check arguments
	if (argc != 2)
		print_error(ERR_ARGS);

	// Check file extension
	if (!check_extension(argv[1], ".rt"))
		print_error(ERR_FILE);

	// Initialize scene
	scene_init(&scene);

	// Debugging
		// Adiciona uma esfera de teste
		/*
		t_sphere *sphere = sphere_create(vec3_create(0, 0, 0), 1.0, color_create(255, 0, 0));
		t_object *obj = object_create(OBJ_SPHERE, sphere);
		scene_add_object(&scene, obj);

		// Define a câmera manualmente
		scene.camera.position = vec3_create(0, 0, 10);
		scene.camera.orientation = vec3_create(0, 0, -1);
		scene.camera.fov = 70;
		*/
	// end Debugging

	// Parse scene file
	if (parse_scene(argv[1], &scene) != 0)
		print_error(ERR_SCENE);
	printf("Scene parsed. Number of objects: %d\n", scene.num_objects);
	
	// Initialize MiniLibX
	init_mlx(&scene);

	// Render scene
	render(&scene);

	// Set up event hooks
	mlx_hook(scene.win, X_EVENT_KEY_PRESS, 1L<<0, key_press, &scene);
	mlx_hook(scene.win, X_EVENT_CLOSE_WINDOW, 0, close_window, &scene);

	// Start MiniLibX loop
	mlx_loop(scene.mlx);

	// This line will never be reached, but good practice
	return (0);
}
