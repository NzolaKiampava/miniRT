/*
#include "../../includes/minirt.h"

int	parse_line(char **elements, t_scene *scene)
{
	if (!elements[0])
		return (0);
	if (ft_strcmp(elements[0], "A") == 0)
		return (parse_ambient(elements, scene));
	else if (ft_strcmp(elements[0], "C") == 0)
		return (parse_camera(elements, scene));
	else if (ft_strcmp(elements[0], "L") == 0)
		return (parse_light(elements, scene));
	else if (ft_strcmp(elements[0], "sp") == 0)
		return (parse_sphere(elements, scene));
	else if (ft_strcmp(elements[0], "pl") == 0)
		return (parse_plane(elements, scene));
	else if (ft_strcmp(elements[0], "cy") == 0)
		return (parse_cylinder(elements, scene));
	else
		return (print_error("Unknown element type\n"), -1);
}
int	parse_scene(char *filename, t_scene *scene)
{
	int	fd;
	int	ret;

	if (!check_extension(filename, ".rt"))
		return (print_error(ERR_FORMAT), -1);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (print_error(ERR_FILE), -1);
	scene_init(scene);
	ret = process_file(fd, scene);
	if (ret == 0)
		ret = validate_scene(scene);
	return (ret);
}
int	validate_scene(t_scene *scene)
{
	if (fabs(vec3_length(scene->camera.orientation) - 1.0) > EPSILON)
		scene->camera.orientation = vec3_normalize(scene->camera.orientation);
	if (scene->camera.fov <= 0 || scene->camera.fov >= 180)
		return (print_error("Invalid camera FOV\n"), -1);
	return (0);
}
static int	create_and_add_sphere(t_scene *scene, t_vec3 center,
					double diameter, t_color color)
{
	t_sphere	*sphere;
	t_object	*obj;

	sphere = sphere_create(center, diameter, color);
	if (!sphere)
		return (print_error(ERR_MEMORY), -1);
	obj = object_create(OBJ_SPHERE, sphere);
	if (!obj)
	{
		free(sphere);
		return (print_error(ERR_MEMORY), -1);
	}
	if (add_object_to_scene(scene, obj) == -1)
	{
		object_free(obj);
		return (print_error(ERR_MEMORY), -1);
	}
	return (0);
}
int	parse_sphere(char **line, t_scene *scene)
{
	t_vec3	center;
	double	diameter;
	t_color	color;

	if (count_elements(line) != 4)
		return (print_error("Invalid sphere format\n"), -1);
	center = parse_vector(line[1]);
	diameter = ft_atof(line[2]);
	color = parse_color(line[3]);
	if (validate_sphere_params(diameter, color) == -1)
		return (-1);
	return (create_and_add_sphere(scene, center, diameter, color));
}
static int	create_and_add_plane(t_scene *scene, t_vec3 point,
					t_vec3 normal, t_color color)
{
	t_plane		*plane;
	t_object	*obj;

	plane = plane_create(point, normal, color);
	if (!plane)
		return (print_error(ERR_MEMORY), -1);
	obj = object_create(OBJ_PLANE, plane);
	if (!obj)
	{
		free(plane);
		return (print_error(ERR_MEMORY), -1);
	}
	if (add_object_to_scene(scene, obj) == -1)
	{
		object_free(obj);
		return (print_error(ERR_MEMORY), -1);
	}
	return (0);
}
int	parse_plane(char **line, t_scene *scene)
{
	t_vec3	point;
	t_vec3	normal;
	t_color	color;

	if (count_elements(line) != 4)
		return (print_error("Invalid plane format\n"), -1);
	point = parse_vector(line[1]);
	normal = parse_vector(line[2]);
	color = parse_color(line[3]);
	if (validate_plane_params(normal, color) == -1)
		return (-1);
	return (create_and_add_plane(scene, point, normal, color));
}
int	parse_cylinder(char **line, t_scene *scene)
{
	t_cylinder	params;

	if (count_elements(line) != 6)
		return (print_error("Invalid cylinder format\n"), -1);
	params.center = parse_vector(line[1]);
	params.axis = parse_vector(line[2]);
	params.diameter = ft_atof(line[3]);
	params.height = ft_atof(line[4]);
	params.color = parse_color(line[5]);
	if (validate_cylinder_params(params.axis, params.diameter,
			params.height, params.color) == -1)
		return (-1);
	return (create_add_cylinder(scene, params));
}

int	parse_ambient(char **elements, t_scene *scene)
{
	int			count;
	t_color		color;
	double		ratio;

	count = count_elements(elements);
	if (count != 3)
		return (print_error("Invalid ambient lighting format\n"), -1);
	ratio = ft_atof(elements[1]);
	color = parse_color(elements[2]);
	if (ratio < 0.0 || ratio > 1.0 || !validate_color_values(color))
		return (print_error("Invalid ambient parameters\n"), -1);
	scene->ambient.ratio = ratio;
	scene->ambient.color = color;
	return (0);
}
int	parse_camera(char **elements, t_scene *scene)
{
	int			count;
	t_vec3		position;
	t_vec3		orientation;
	double		fov;

	count = count_elements(elements);
	if (count != 4)
		return (print_error("Invalid camera format\n"), -1);
	position = parse_vector(elements[1]);
	orientation = parse_vector(elements[2]);
	fov = ft_atof(elements[3]);
	if (!validate_vector_normalized(orientation) || fov <= 0 || fov >= 180)
		return (print_error("Invalid camera parameters\n"), -1);
	orientation = vec3_normalize(orientation);
	scene->camera.position = position;
	scene->camera.orientation = orientation;
	scene->camera.fov = fov;
	return (0);
}
int	parse_light(char **elements, t_scene *scene)
{
	int			count;
	t_light		light;

	count = count_elements(elements);
	if (count != 3 && count != 4)
		return (print_error("Invalid light format\n"), -1);
	light.position = parse_vector(elements[1]);
	light.brightness = ft_atof(elements[2]);
	if (count == 4)
		light.color = parse_color(elements[3]);
	else
		light.color = color_create(255, 255, 255);
	if (light.brightness < 0.0 || light.brightness > 1.0
		|| !validate_color_values(light.color))
		return (print_error("Invalid light parameters\n"), -1);
	if (scene_add_light(scene, light) < 0)
		return (print_error(ERR_MEMORY), -1);
	return (0);
}
int	create_add_cylinder(t_scene *scene, t_cylinder params)
{
	t_cylinder	*cylinder;
	t_object	*obj;

	cylinder = cylinder_create(params);
	if (!cylinder)
		return (print_error(ERR_MEMORY), -1);
	obj = object_create(OBJ_CYLINDER, cylinder);
	if (!obj)
	{
		free(cylinder);
		return (print_error(ERR_MEMORY), -1);
	}
	if (add_object_to_scene(scene, obj) == -1)
	{
		object_free(obj);
		return (print_error(ERR_MEMORY), -1);
	}
	return (0);
}
int	add_object_to_scene(t_scene *scene, t_object *obj)
{
	t_object	**new_objects;
	int			i;

	new_objects = malloc(sizeof(t_object *) * (scene->num_objects + 1));
	if (!new_objects)
		return (-1);
	i = 0;
	while (i < scene->num_objects)
	{
		new_objects[i] = scene->objects[i];
		i++;
	}
	new_objects[i] = obj;
	if (scene->objects)
		free(scene->objects);
	scene->objects = new_objects;
	scene->num_objects++;
	return (0);
}


*/