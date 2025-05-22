/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiampav <nkiampav@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 09:50:38 by nkiampav          #+#    #+#             */
/*   Updated: 2025/05/22 08:42:02 by nkiampav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static t_mlx_img	init_image(t_scene *scene)
{
	t_mlx_img	img_data;

	img_data.img = mlx_new_image(scene->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	img_data.addr = mlx_get_data_addr(img_data.img, &img_data.bits_per_pixel,
			&img_data.line_length, &img_data.endian);
	return (img_data);
}

static t_color	render_pixel(t_scene *scene, int x, int y)
{
	t_camera_params	cam_params;
	t_pixel_coords	pixel;
	t_ray			ray;

	cam_params.origin = scene->camera.position;
	cam_params.direction = scene->camera.orientation;
	cam_params.fov = scene->camera.fov;
	cam_params.aspect_ratio = (double)WINDOW_WIDTH / WINDOW_HEIGHT;
	pixel.x = x;
	pixel.y = y;
	ray = camera_ray(cam_params, pixel);
	return (scene_trace_ray(scene, ray, 0));
}

static void	render_row(t_scene *scene, t_mlx_img *img_data, int y)
{
	int		x;
	t_color	pixel_color;

	x = 0;
	while (x < WINDOW_WIDTH)
	{
		pixel_color = render_pixel(scene, x, y);
		my_mlx_pixel_put(img_data, x, y, color_to_int(pixel_color));
		x++;
	}
}

static void	display_image(t_scene *scene, t_mlx_img *img_data)
{
	mlx_put_image_to_window(scene->mlx, scene->win, img_data->img, 0, 0);
	mlx_destroy_image(scene->mlx, img_data->img);
}

void	render(t_scene *scene)
{
	t_mlx_img	img_data;
	int			y;

	img_data = init_image(scene);
	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		render_row(scene, &img_data, y);
		y++;
	}
	display_image(scene, &img_data);
}
