/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiampav <nkiampav@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 09:50:38 by nkiampav          #+#    #+#             */
/*   Updated: 2025/05/01 09:50:00 by nkiampav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	render(t_scene *scene)
{
	void	*img;
	char	*img_addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		x, y;
	t_color	pixel_color;

	img = mlx_new_image(scene->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	img_addr = mlx_get_data_addr(img, &bits_per_pixel, &line_length, &endian);

	for (y = 0; y < WINDOW_HEIGHT; y++)
	{
		for (x = 0; x < WINDOW_WIDTH; x++)
		{
			t_ray ray = camera_ray(
				scene->camera.position, 
				scene->camera.orientation, 
				scene->camera.fov, 
				(double)WINDOW_WIDTH / WINDOW_HEIGHT, 
				x, y
			);
			pixel_color = scene_trace_ray(scene, ray, 0);
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
	mlx_put_image_to_window(scene->mlx, scene->win, img, 0, 0);
	mlx_destroy_image(scene->mlx, img);
}

/*
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
*/
void	init_mlx(t_scene *scene)
{
	scene->mlx = mlx_init();
	if (!scene->mlx)
		print_error("Failed to initialize MiniLibX\n");
	scene->win = mlx_new_window(scene->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "miniRT");
	if (!scene->win)
		print_error("Failed to create window\n");
}

void	my_mlx_pixel_put(void *img, char *addr, int x, int y, int color,
			int bits_per_pixel, int line_length)
{
	char	*dst;
	(void)img;

	dst = addr + (y * line_length + x * (bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
