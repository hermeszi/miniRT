# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::   #
#    Makefile                                           :+:      :+:    :+:   #
#                                                     +:+ +:+         +:+     #
#    By: myuen <myuen@student.42.fr>                +#+  +:+       +#+        #
#                                                 +#+#+#+#+#+   +#+           #
#    Created: 2024/10/24 16:22:28 by myuen             #+#    #+#             #
#    Updated: 2025/06/09 21:25:16 by myuen            ###   ########.fr       #
#                                                                              #
# **************************************************************************** #

NAME = miniRT
BONUS_NAME = miniRT_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror -g

# Directories
LIBFT_DIR = ./libft
GNL_DIR = ./ft_gnl
MLX_DIR = ./mlx_linux
OBJ_DIR = ./obj
SRC_DIR = ./src

# Library Names
LIBFT = $(LIBFT_DIR)/libft.a
GNL = $(GNL_DIR)/get_next_line.o $(GNL_DIR)/get_next_line_utils.o
MLX = $(MLX_DIR)/libmlx.a

# Include paths
INCLUDES = -I. -I$(LIBFT_DIR) -I$(GNL_DIR) -I$(MLX_DIR)

# Libraries
LIBS = -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

# Source files
SRCS = src/ft_minirt.c \
	src/ft_init_app.c \
	src/ft_hooks.c \
	src/ft_free_all.c \
	src/ft_draw.c \
	src/ft_render.c \
	src/ft_parse_file.c \
	src/ft_minirt_utils.c \
	src/ft_message.c \
	src/ft_atof.c

BONUS_SRCS = 

# Object files (moved to obj/ directory)
OBJS = $(SRCS:src/%.c=$(OBJ_DIR)/%.o)
BONUS_OBJS = $(BONUS_SRCS:src/%.c=$(OBJ_DIR)/%.o)

# Header files
HEADERS = ft_minirt.h

all: $(NAME)

$(NAME): $(LIBFT) $(GNL) $(MLX) $(OBJ_DIR) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(GNL) $(LIBS) -o $(NAME)

bonus: $(BONUS_NAME)

$(BONUS_NAME): $(LIBFT) $(GNL) $(MLX) $(OBJ_DIR) $(BONUS_OBJS)
	$(CC) $(CFLAGS) $(BONUS_OBJS) $(GNL) $(LIBS) -o $(BONUS_NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(GNL):
	$(MAKE) -C $(GNL_DIR)

$(MLX):
	$(MAKE) -C $(MLX_DIR)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Compile .c files to .o files in obj/ directory
$(OBJ_DIR)/%.o: src/%.c $(HEADERS) | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(GNL_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean
	rm -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) -C $(GNL_DIR) fclean
	$(MAKE) -C $(MLX_DIR) clean
	rm -f $(NAME) $(BONUS_NAME)

re: fclean all

.PHONY: all clean fclean re bonus