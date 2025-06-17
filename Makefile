# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: myuen <myuen@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/24 16:22:28 by myuen             #+#    #+#              #
#    Updated: 2025/06/17 16:34:30 by myuen            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= miniRT
BONUS_NAME  = miniRT_bonus
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g -pedantic

# Get system name for platform detection
UNAME_S     = $(shell uname -s)

# Directories
LIBFT_DIR   = ./libft
GNL_DIR     = ./ft_gnl
OBJ_DIR     = ./obj
SRC_DIR     = ./src

# Platform-specific MLX settings
MLX_DIR     = ./mlx_linux
MLX_URL     = https://github.com/42paris/minilibx-linux.git

ifeq ($(UNAME_S), Linux)
    MLXFLAGS    = -L$(MLX_DIR) -lmlx -L/usr/lib/X11 -lXext -lX11 -lm -lz
    MLX_INCLUDES = -I/usr/include -I$(MLX_DIR)
else ifeq ($(UNAME_S), Darwin)
    MLXFLAGS    = -L$(MLX_DIR) -lmlx -L/opt/X11/lib -lXext -lX11 -framework OpenGL -framework AppKit
    MLX_INCLUDES = -I/opt/X11/include -I$(MLX_DIR)
else
    $(error Unsupported platform: $(UNAME_S))
endif

# Library Names
LIBFT       = $(LIBFT_DIR)/libft.a
GNL         = $(GNL_DIR)/get_next_line.o $(GNL_DIR)/get_next_line_utils.o
MLX         = $(MLX_DIR)/libmlx.a

# Include paths
INCLUDES    = -I. -I$(LIBFT_DIR) -I$(GNL_DIR) $(MLX_INCLUDES)

# Libraries
LIBS        = -L$(LIBFT_DIR) -lft $(MLXFLAGS)

# Source files
SRCS = src/ft_minirt.c \
       src/ft_init_app.c \
       src/ft_hooks.c \
       src/ft_free_all.c \
       src/ft_draw.c \
       src/ft_render.c \
       src/ft_parse_file.c \
	   src/ft_parse_linked.c \
       src/ft_parse_objects.c \
       src/ft_parse_scene.c \
       src/ft_minirt_utils.c \
       src/ft_message.c \
       src/ft_atof.c \
       src/ft_vec_calculations.c \
	   src/ft_vec_utils.c \
	   src/ft_color.c \
	   src/ft_viewport.c \
	   src/ft_ray.c \
	   src/ft_print_scene_info.c \
	   src/ft_intersect_sphere.c \
	   src/ft_intersect_plane.c \
	   src/ft_matrix_utils.c \
	   src/ft_camera_setup.c \
	   src/ft_camera_transform.c

BONUS_SRCS =

# Object files
OBJS        = $(SRCS:src/%.c=$(OBJ_DIR)/%.o)
BONUS_OBJS  = $(BONUS_SRCS:src/%.c=$(OBJ_DIR)/%.o)

# Header files
HEADERS     = ft_minirt.h

# Default target
all: $(NAME)

# Executable build rules
$(NAME): $(LIBFT) $(GNL) $(MLX) $(OBJ_DIR) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(GNL) $(LIBS) -o $(NAME)

bonus: $(BONUS_NAME)

$(BONUS_NAME): $(LIBFT) $(GNL) $(MLX) $(OBJ_DIR) $(BONUS_OBJS)
	$(CC) $(CFLAGS) $(BONUS_OBJS) $(GNL) $(LIBS) -o $(BONUS_NAME)

# Build dependencies
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(GNL):
	$(MAKE) -C $(GNL_DIR)

# Automatically clone & build MLX if missing
$(MLX):
	@if [ ! -d "$(MLX_DIR)" ]; then \
		echo "Cloning MLX for $(UNAME_S)..."; \
		git clone $(MLX_URL) $(MLX_DIR); \
	fi; \
	if [ ! -f "$(MLX)" ]; then \
		make -C $(MLX_DIR); \
	fi

# Create obj/ directory
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Compile source files
$(OBJ_DIR)/%.o: src/%.c $(HEADERS) | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Cleaning
clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(GNL_DIR) clean
	@if [ -d "$(MLX_DIR)" ]; then $(MAKE) -C $(MLX_DIR) clean; fi
	rm -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) -C $(GNL_DIR) fclean
	rm -f $(NAME) $(BONUS_NAME)

re: fclean all

.PHONY: all clean fclean re bonus