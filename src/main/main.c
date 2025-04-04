/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiampav <nkiampav@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 09:20:47 by nkiampav          #+#    #+#             */
/*   Updated: 2025/04/04 11:06:11 by nkiampav         ###   ########.fr       */
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
	scene_free(scene);
	exit(0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_scene	scene;

	if (argc != 2)
		print_error(ERR_ARGS);
	if (!check_extension(argv[1], ".rt"))
		print_error(ERR_FILE);
	scene_init(&scene);
	if (parse_scene(argv[1], &scene) != 0)
		print_error(ERR_SCENE);
	printf("Scene parsed. Number of objects: %d\n", scene.num_objects);
	init_mlx(&scene);
	render(&scene);
	mlx_hook(scene.win, X_EVENT_KEY_PRESS, 1L<<0, key_press, &scene);
	mlx_hook(scene.win, X_EVENT_CLOSE_WINDOW, 0, close_window, &scene);
	mlx_loop(scene.mlx);
	return (0);
}
