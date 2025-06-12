/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minirt.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 16:21:07 by myuen             #+#    #+#             */
/*   Updated: 2024/10/26 14:12:49 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MINIRT_H
# define FT_MINIRT_H

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
# define WIN_WIDTH 200
# define WIN_HEIGHT 200
# define VIEWPORT_DISTANCE 1.0
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
typedef enum	e_obj_type
{
    OBJ_PLANE,
    OBJ_SPHERE,
    OBJ_CYLINDER
} t_obj_type;

typedef struct	s_vec3
{
	double	x;
	double	y;
	double	z;
} t_vec3;

typedef struct	s_color		// RGB color (0-255 range)
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
} t_color;

typedef struct	s_ambient
{
	double	ratio;	// Range [0.0, 1.0]
	t_color	color;	// RGB (0-255)
} t_ambient;

typedef struct	s_camera
{
	t_vec3	position;	// Position coordinates
	t_vec3	orientation;// Normalized direction vector [-1,1]
	int		fov;		// Field of view in degrees [0,180]
} t_camera;

typedef struct	s_light
{
	t_vec3	position;	// Light position
	double	brightness;	// Light brightness ratio [0.0, 1.0]
	t_color	color;		// RGB (0-255) - unused in mandatory part
} t_light;

typedef struct	s_plane
{
	t_vec3	position;	// Point in the plane
	t_vec3	normal;		// Normalized normal vector [-1,1]
	t_color	color;		// RGB (0-255)
} t_plane;

typedef struct	s_sphere
{
	t_vec3	center;		// Center coordinates
	double	diameter;	// Sphere diameter
	t_color	color;		// RGB (0-255)
} t_sphere;

typedef struct	s_cylinder
{
	t_vec3	center;		// Center coordinates
	t_vec3	axis;		// Normalized axis vector [-1,1]
	double	diameter;	// Cylinder diameter
	double	height;		// Cylinder height
	t_color	color;		// RGB (0-255)
} t_cylinder;

typedef struct	s_object
{
    t_obj_type	type;
    union
    {
        t_plane		plane;
        t_sphere	sphere;
        t_cylinder	cylinder;
    } data;
	int				x;
	struct s_object	*next;
} t_object;

typedef struct	s_scene
{
    t_ambient		ambient;		// Ambient lighting (only one)
    t_camera		camera;			// Camera (only one)
    t_light			light;			// Light source (only one in mandatory part)
    t_object		*objects;		// Linked list of objects (planes, spheres, cylinders)
    unsigned int	object_count;	// Number of objects in the scene
} t_scene;

typedef struct	s_display
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	char	*img_data;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
} t_display;

typedef struct	s_ray
{
	t_vec3		origin;
	t_vec3		direction;
}	t_ray;

typedef struct s_hit
{
	int			hit;		// A boolean flag: 1 if there was a hit, 0 otherwise.
	double		t;			// The distance from the ray's origin to the hit point.
	t_vec3		point;		// The (x, y, z) coordinates of the intersection point.
	t_vec3		normal;		// The surface normal vector at the hit point.
	t_object	*object;	// A pointer to the specific object that was hit.
}	t_hit;

typedef struct	s_viewport //canvas
{
	double	width;		// Viewport width
	double	height;     // Viewport height
	double	distance;   // Distance from camera to viewport
} t_viewport;

typedef struct	s_main
{
	t_scene		*scene;
	t_display	*display;
	t_viewport	viewport;

} t_main;

/********************************************************/
/*							Init						*/
/********************************************************/
void	init_app(t_main *app, char *filename);
void	init_hooks(t_main *app);

/********************************************************/
/*						Events Handling Functions	 	*/
/********************************************************/
void	render_scene(t_main *app);
void	set_pixel(t_display *display, int x, int y, int color);

/********************************************************/
/*							Render 						*/
/********************************************************/
t_vec3	pixel_to_viewport(int screen_x, int screen_y, t_viewport viewport);
t_ray	create_ray(t_vec3 origin, t_vec3 direction);

/********************************************************/
/*							Utilites					*/
/********************************************************/
int		rgb_to_int(t_color c);
double	degrees_to_radians(double degrees);

/********************************************************/
/*							Hooks						*/
/********************************************************/
int		key_hook(int keycode, t_main *app);
int		mouse_hook(int button, int x, int y, t_main *app);
int		close_hook(t_main *app);

/********************************************************/
/*							Frees						*/
/********************************************************/
void	free_scene(t_scene *scene);
void	free_all(t_main *app);

/********************************************************/
/*							LIBFT Functions				*/
/********************************************************/
int	ft_isvalid_float_str(const char *str);
double	ft_atof(const char *str);

/********************************************************/
/*						Print Messages Functions		*/
/********************************************************/
void	print_error_exit(char *msg);

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
t_vec3		vec3_cross(t_vec3 v1, t_vec3 v2);
t_vec3		vec3_new(double x, double y, double z);
double		vec3_dot(t_vec3 v1, t_vec3 v2);
t_vec3		vec3_mult_vec3(t_vec3 v1, t_vec3 v2);
t_color		color_mult(t_color c1, t_color c2);

/********************************************************/
/*					Colour Functions					*/
/********************************************************/
t_color		int_to_rgb(const int r, const int g, const int b);
t_color		color_add(t_color c1, t_color c2);
t_color		color_scale(t_color c, double factor);
t_color		color_mult(t_color c1, t_color c2);
t_color		calculate_shading(t_hit *hit, t_scene *scene, int in_shadow);

#endif
