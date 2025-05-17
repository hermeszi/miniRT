/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fractol.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 16:21:07 by myuen             #+#    #+#             */
/*   Updated: 2024/10/26 14:12:49 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FRACTOL_H
# define FT_FRACTOL_H

# include "mlx.h"
# include "libft.h"
# include "get_next_line.h"
# include <stdlib.h>
# include <math.h>
# include <string.h>
# include <stdio.h>
# include <errno.h>
/********************************************************/
/*									Constants			*/
/********************************************************/
# define WIDTH 800
# define HEIGHT 600
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

typedef enum	e_obj_type
{
    OBJ_PLANE,
    OBJ_SPHERE,
    OBJ_CYLINDER
} t_obj_type;

typedef struct	s_object
{
    t_obj_type	type;
    union
    {
        t_plane		plane;
        t_sphere	sphere;
        t_cylinder	cylinder;
    } data;
} t_object;

typedef struct	s_scene
{
    t_ambient		ambient;		// Ambient lighting (only one)
    t_camera		camera;			// Camera (only one)
    t_light			light;			// Light source (only one in mandatory part)
    t_object		*objects;		// Array of objects (planes, spheres, cylinders)
    unsigned int	object_count;	// Number of objects in the scene
} t_scene;

typedef struct	s_window
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	char	*img_data;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
} t_window;

/********************************************************/
/*							Set up and Utilites			*/
/********************************************************/
int			init_display(void *ptr);
int			ft_close(void *ptr);
void		ft_map_screen_to_plane(t_data *data, int screen_x,
				int screen_y, t_complex *z);
/********************************************************/
/*						Events Handling Functions	 	*/
/********************************************************/
int			ft_key_press(int keycode, t_data *data);
int			ft_mouse_event(int button, int x, int y, t_data *data);
/********************************************************/
/*						Zoom and Pan Functions			*/
/********************************************************/

/********************************************************/
/*							Image Functions				*/
/********************************************************/
void		ft_draw_pixel(t_data *data, int x, int y, int color);
void		ft_redraw(t_data *data);
void		ft_clear_image(t_data *data);
/********************************************************/
/*							Color Functions				*/
/********************************************************/
int			ft_get_color(t_data *data, int iterations, int max_iter);
void		ft_shift_color(int *color, int *color_index);

/********************************************************/
/*							LIBFT Functions				*/
/********************************************************/
double		ft_atof(const char *str);
int			ft_isvalid_float_str(const char *str);
/********************************************************/
/*						Print Messages Functions		*/
/********************************************************/

#endif
