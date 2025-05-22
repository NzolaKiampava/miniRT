/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiampav <nkiampav@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 09:50:38 by nkiampav          #+#    #+#             */
/*   Updated: 2025/05/22 08:06:13 by nkiampav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	render(t_scene *scene)
{
	t_mlx_img	img_data;
	int	x;
	int	y;
	t_color	pixel_color;

	img_data.img = mlx_new_image(scene->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	img_data.addr = mlx_get_data_addr(img_data.img, &img_data.bits_per_pixel, &img_data.line_length, &img_data.endian);
	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			t_camera_params cam_params = {
				scene->camera.position,
				scene->camera.orientation,
				scene->camera.fov,
				(double)WINDOW_WIDTH / WINDOW_HEIGHT
			};
			t_pixel_coords pixel = {x, y};
			
			t_ray ray = camera_ray(cam_params, pixel);
			pixel_color = scene_trace_ray(scene, ray, 0);
			my_mlx_pixel_put(&img_data, x, y, color_to_int(pixel_color));
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(scene->mlx, scene->win, img_data.img, 0, 0);
	mlx_destroy_image(scene->mlx, img_data.img);
}

void	init_mlx(t_scene *scene)
{
	scene->mlx = mlx_init();
	if (!scene->mlx)
		print_error("Failed to initialize MiniLibX\n");
	scene->win = mlx_new_window(scene->mlx, WINDOW_WIDTH,
			WINDOW_HEIGHT, "miniRT");
	if (!scene->win)
		print_error("Failed to create window\n");
}

void	my_mlx_pixel_put(t_mlx_img	*img_data, int x, int y, int color)
{
	char	*dst;

	dst = img_data->addr + (y * img_data->line_length + x
			* (img_data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
