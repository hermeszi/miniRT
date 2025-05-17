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
# define MANDELBROT 1
# define JULIA 2
# define TRICORN 3

# define MAX_ITERATIONS 100

# define WIDTH 800
# define HEIGHT 600

# define ZOOM_FACTOR 0.95
# define PAN_FACTOR 0.01
# define MIN_RANGE 0.000001
# define MAX_RANGE 30.0
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
typedef struct s_complex
{
	double	real;
	double	imag;
}	t_complex;

typedef struct s_data
{
	void				*mlx_ptr;
	void				*win_ptr;
	void				*img_ptr;
	char				*img_data;
	int					bits_per_pixel;
	int					size_line;
	int					endian;
	double				zoom_factor;
	double				math_x1;
	double				math_x2;
	double				math_y1;
	double				math_y2;
	int					fractal_type;
	int					current_color;
	int					base_color;
	int					current_color_index;
	int					base_color_index;
	struct s_complex	*c;
	void				(*draw_fractal)(struct s_data *data);
}	t_data;
/********************************************************/
/*							Set up and Utilites			*/
/********************************************************/
int			ft_close(void *ptr);
int			ft_valid_range(double new_x1, double new_x2,
				double new_y1, double new_y2);
void		ft_set_aspect_ratio(t_data *data);
int			ft_process_fractal(t_data *data, const int argc, const char **argv);
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
void		ft_zoom_out(t_data *data);
void		ft_zoom_in(t_data *data);
void		ft_set_center(t_data *data, double new_center_x,
				double new_center_y);
void		ft_pan_left(t_data *data);
void		ft_pan_right(t_data *data);
void		ft_pan_up(t_data *data);
void		ft_pan_down(t_data *data);
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
/*						Fractal Drawing Functions		*/
/********************************************************/
void		ft_draw_mandelbrot(t_data *data);
void		ft_draw_julia(t_data *data);
void		ft_draw_tricorn(t_data *data);
/********************************************************/
/*						Complex Number Operations		*/
/********************************************************/
t_complex	ft_complex_add(t_complex a, t_complex b);
t_complex	ft_complex_multiply(t_complex a, t_complex b);
t_complex	ft_complex_square(t_complex a);
t_complex	ft_complex_conjugate_square(t_complex a);
double		ft_complex_magnitude_squared(t_complex a);
/********************************************************/
/*							LIBFT Functions				*/
/********************************************************/
double		ft_atof(const char *str);
int			ft_isvalid_float_str(const char *str);
/********************************************************/
/*						Print Messages Functions		*/
/********************************************************/
void		ft_print_control(void);
void		ft_print_usage(const char *program_name);
void		ft_print_julia_suggestions(void);
#endif
