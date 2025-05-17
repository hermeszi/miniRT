# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/24 10:00:00 by myuen             #+#    #+#              #
#    Updated: 2024/09/28 16:31:52 by myuen            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Variables
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
AR = ar rcs
RM = rm -f

# Source Files
GNL_SRC = get_next_line.c get_next_line_utils.c

# Object Files
GNL_OBJ = $(GNL_SRC:.c=.o)

# Output Library Name
NAME = lib_gnl.a

# Header Files
GNL_HDR = get_next_line.h

# All Target (Builds lib_gnl.a)
all: $(NAME)
	@echo "📖 $(NAME) built successfully!"

# Rule to create lib_gnl.a
$(NAME): $(GNL_OBJ)
	$(AR) $@ $(GNL_OBJ)
	@echo "📦 $(NAME) created!"

# Rule to create object files
%.o: %.c $(GNL_HDR)
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "🛠️  $@ created"

# Clean up object files
clean:
	$(RM) $(GNL_OBJ)
	@echo "🧹 OBJs files cleaned!"

# Clean up all files (object files and library)
fclean: clean
	$(RM) $(NAME)
	@echo "🗑️  $(NAME) deleted!"

# Rebuild all
re: fclean all
	@echo "🔄 Rebuild complete!"

.PHONY: all clean fclean re

