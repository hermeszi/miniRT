/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minirt_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 16:21:07 by myuen             #+#    #+#             */
/*   Updated: 2025/07/04 19:48:01 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MINIRT_BONUS_H
# define FT_MINIRT_BONUS_H

# include "mlx.h"
# include "libft.h"
# include "get_next_line.h"
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>
# include <string.h>
# include <stdio.h>
# include <errno.h>
/********************************************************/
/*									Constants			*/
/********************************************************/
# define WIN_WIDTH 600
# define WIN_HEIGHT 400
# define VIEWPORT_DISTANCE 1.2
# define BACKGROUND_COLOR 0x0099CCFF //0x00FFFFFF
# define ATTENUATION_CONSTANT 0.7
# define ATTENUATION_LINEAR 0.05
# define ATTENUATION_QUADRATIC 0.005
# define EPSILON 1e-6
# define CHECKER_SCALE 1.0
/********************************************************/
/*								Color Definitions		*/
/********************************************************/
# define COLOR_BLACK 0x000000
# define COLOR_WHITE 0x00FFFFFF
# define COLOR_GREY 0x808080
# define COLOR_RED 0x00FF0000
# define COLOR_GREEN 0x0000FF00
# define COLOR_BLUE 0x000000FF
# define COLOR_YELLOW 0x00FFFF00
# define COLOR_MAGENTA 0x00FF00FF
# define COLOR_CYAN 0x0000FFFF
# define COLOR_ORANGE 0xFFA500
/********************************************************/
/*									Key Binding			*/
/********************************************************/
# define SCROLL_UP 4
# define SCROLL_DOWN 5
# define LEFT_MOUSE_CLICK 1
# define ESC_KEY 65307
# define C_KEY 99
# define V_KEY 98
# define SPACE_KEY 32
# define Z_KEY 122
# define X_KEY 120
# define ARROW_LEFT 65361
# define ARROW_UP 65362
# define ARROW_RIGHT 65363
# define ARROW_DOWN 65364
/********************************************************/
/*									Structures			*/
/********************************************************/
typedef enum e_obj_type
{
	OBJ_PLANE,
	OBJ_SPHERE,
	OBJ_CYLINDER
}	t_obj_type;

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

typedef struct s_mat3
{
	t_vec3	col[3];
}	t_mat3;
// col[0]=right (x), col[1]=up (y), col[2]=forward (z)

typedef struct s_quadratic
{
	double	a;
	double	b;
	double	c;
	double	t;
	t_vec3	oc;
}	t_quadratic;

typedef struct s_color
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
}	t_color;
// RGB color (0-255 range)

typedef struct s_ambient
{
	double	ratio;
	t_color	color;
}	t_ambient;

typedef struct s_camera
{
	t_vec3	position;
	int		fov;
	t_vec3	orientation;
	t_vec3	up;
	t_vec3	right;
	t_mat3	rotation;
}	t_camera;

typedef struct s_light
{
	t_vec3	position;
	double	brightness;
	t_color	color;
}	t_light;

typedef struct s_plane
{
	t_vec3	position;
	t_vec3	normal;
	t_color	color;
}	t_plane;

typedef struct s_sphere
{
	t_vec3	center;
	double	diameter;
	double	radius;
	t_color	color;
}	t_sphere;

typedef struct s_cylinder
{
	t_vec3	center;
	t_vec3	axis;
	double	diameter;
	double	height;
	t_color	color;
}	t_cylinder;

typedef struct s_cyl_cal
{
	t_vec3	oc;
	double	a;
	double	b;
	double	c;
	double	discriminant;
	double	t1;
	double	t2;
}	t_cyl_cal;

typedef struct s_object
{
	t_obj_type		type;
	union
	{
		t_plane		plane;
		t_sphere	sphere;
		t_cylinder	cylinder;
	} u_data;
	int				x;
	struct s_object	*next;
}	t_object;

typedef struct s_scene
{
	t_ambient		ambient;
	t_camera		camera;
	t_light			light;
	t_object		*objects;
	t_color			background;
	unsigned int	object_count;
}	t_scene;

typedef struct s_display
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	char	*img_u_data;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_display;

typedef struct s_ray
{
	t_vec3		origin;
	t_vec3		direction;
}	t_ray;

typedef struct s_hit
{
	int			hit;
	double		t;
	t_vec3		point;
	t_vec3		normal;
	t_color		color;
	t_object	*object;
}	t_hit;

typedef struct s_viewport
{
	double	width;
	double	height;
	double	distance;
	double	fov_rad;
	double	aspect_ratio;
	double	half_scale;
}	t_viewport;

typedef struct s_main
{
	t_scene		*scene;
	t_display	*display;
	t_viewport	viewport;

}	t_main;

/********************************************************/
/*							Init						*/
/********************************************************/
int			init_app(t_main *app, char *filename);
void		init_hooks(t_main *app);

/********************************************************/
/*							Matrix						*/
/********************************************************/
t_vec3		mat3_multiply_vec3(t_mat3 m, t_vec3 v);
t_mat3		mat3_from_vectors(t_vec3 right, t_vec3 up, t_vec3 forward);

/********************************************************/
/*							Camera						*/
/********************************************************/
void		init_camera(t_camera *camera);
void		build_camera_matrix(t_camera *camera);
t_vec3		pixel_to_viewport(t_viewport *viewport, int screen_x, int screen_y);
t_ray		create_ray(t_camera *camera, t_viewport *viewport, \
					int pixel_x, int pixel_y);
t_vec3		camera_to_world_direction(t_camera *camera, t_vec3 viewport_dir);

/********************************************************/
/*						Draw MLX Functions			 	*/
/********************************************************/
void		set_pixel(t_display *display, int x, int y, int color);
void		clear_image(t_display *u_data);

/********************************************************/
/*						Intercept Objects				*/
/********************************************************/
t_hit		intersect_sphere(t_ray ray, t_sphere sphere);
t_hit		intersect_plane(t_ray ray, t_plane plane);
t_hit		intersect_cylinder(t_ray ray, t_cylinder cylinder);
void		get_body_hit(t_hit *hit, double t, t_ray ray, t_cylinder cyl);
void		get_cap_hit(t_hit *hit, double t, t_ray ray, t_cylinder cyl);
int			is_within_height(double t, t_ray ray, t_cylinder cyl);
double		intersect_caps(t_ray ray, t_cylinder cyl);

/********************************************************/
/*						Lights							*/
/********************************************************/
t_color		calculate_point_light(t_hit *hit, t_scene *scene);

/********************************************************/
/*							Render 						*/
/********************************************************/
void		render_scene(t_main *app);
void		draw_scene(t_main *app);
t_color		trace_ray(t_ray ray, t_scene *scene);
t_color		get_hit_color(t_hit *closest_hit, t_scene *scene);

/********************************************************/
/*							Utilites					*/
/********************************************************/
t_color		int_to_rgb(const int r, const int g, const int b);
int			rgb_to_int(t_color c);
t_color		hex_to_rgb(int hex);
double		degrees_to_radians(double degrees);
t_color		invert_color(t_color c);

/********************************************************/
/*							Hooks						*/
/********************************************************/
int			key_hook(int keycode, t_main *app);
int			mouse_hook(int button, int x, int y, t_main *app);
int			close_hook(t_main *app);

/********************************************************/
/*							Frees						*/
/********************************************************/
void		free_scene(t_scene *scene);
void		free_all(t_main *app);

/********************************************************/
/*							LIBFT Functions				*/
/********************************************************/
long		ft_atoi_strict(const char *str, char **endptr);
double		ft_atof_strict(const char *str, char **endptr);
double		get_validated_double(char *str);
int			get_validated_int(char *str);

/********************************************************/
/*						Print Messages Functions		*/
/********************************************************/
void		print_error_exit(char *msg);
void		print_color(t_color c);
void		print_vec3(t_vec3 v);
void		print_scene_info(t_scene *scene);

/********************************************************/
/*					Parse Functions						*/
/********************************************************/
void		check_filename(char *file);
void		init_scene(t_scene *scene);
void		validate_scene(t_scene *scene);
char		*clean_line(char *line);
void		parse_lines(int fd, char *line, t_scene *scene, int *obj_count);
void		free_tokens(char **tokens);
void		parse_vector(char *str, t_vec3 *vec);
void		parse_norm_vector(char *str, t_vec3 *vec);
t_scene		*parse_file(char *file);

/********************************************************/
/*				Parse Linked List Functions				*/
/********************************************************/
t_object	*last_obj(t_object *lst);
int			num_of_obj(t_object *lst);
void		object_add_end(t_object **lst, t_object *new);
void		free_objects(t_object *lst);

/********************************************************/
/*					Parse Objects Functions				*/
/********************************************************/
void		parse_sphere(char *line, t_scene *scene, int *obj_count);
void		parse_plane(char *line, t_scene *scene, int *obj_count);
void		parse_cylinder(char *line, t_scene *scene, int *obj_count);

/********************************************************/
/*					Parse Scene Functions				*/
/********************************************************/
void		parse_ambient(char *line, t_scene *scene);
void		parse_camera(char *line, t_scene *scene);
void		parse_light(char *line, t_scene *scene);
void		parse_color(char *str, t_color *color);

/********************************************************/
/*					Vector Functions					*/
/********************************************************/
double		vec3_length(t_vec3 v);
t_vec3		vec3_norm(t_vec3 v);
t_vec3		vec3_add(t_vec3 v1, t_vec3 v2);
t_vec3		vec3_sub(t_vec3 v1, t_vec3 v2);
t_vec3		vec3_multiply(t_vec3 v, double scalar);
t_vec3		vec3_divide(t_vec3 v, double scalar);
t_vec3		vec3_cross(t_vec3 v1, t_vec3 v2);
t_vec3		vec3_new(double x, double y, double z);
double		vec3_dot(t_vec3 v1, t_vec3 v2);
t_vec3		vec3_mult_vec3(t_vec3 v1, t_vec3 v2);
t_vec3		get_stable_tangent(t_vec3 normal);

/********************************************************/
/*					Colour Functions					*/
/********************************************************/
t_color		color_add(t_color c1, t_color c2);
t_color		color_scale(t_color c, double factor);
t_color		color_mult(t_color c1, t_color c2);
t_color		calculate_shading(t_hit *hit, t_scene *scene, int in_shadow);

/********************************************************/
/*					Bonus - Checker						*/
/********************************************************/
t_color		get_plane_checker_color(t_hit hit, t_plane plane);
t_color		get_sphere_checker_color(t_hit hit, t_sphere sphere);

#endif
