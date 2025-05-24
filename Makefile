# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nkiampav <nkiampav@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/05 10:11:29 by nkiampav          #+#    #+#              #
#    Updated: 2025/05/24 16:39:24 by nkiampav         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Target name
NAME		= miniRT

# Compiler and flags
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g

# Directories
SRC_DIR		= src
OBJ_DIR		= obj
INC_DIR		= includes
MINILIBX_DIR	= minilibx-linux

# MLX Flags and Libraries
MLXFLAGS	= -L$(MINILIBX_DIR) -lmlx -lXext -lX11 -lm

# Math library
MATHFLAGS	= -lm

# Source files - explicitly listed without wildcards
SRCS		= $(SRC_DIR)/main/main.c \
			  $(SRC_DIR)/main/help.c \
			  $(SRC_DIR)/main/key_handler.c \
			  $(SRC_DIR)/main/resize.c \
			  $(SRC_DIR)/parser/parser.c \
			  $(SRC_DIR)/parser/parser_objects.c \
			  $(SRC_DIR)/parser/parser_object_utils.c \
			  $(SRC_DIR)/parser/parser_scene.c \
			  $(SRC_DIR)/parser/parser_utils.c \
			  $(SRC_DIR)/parser/parser_utils_2.c \
			  $(SRC_DIR)/parser/parser_validates.c \
			  $(SRC_DIR)/vector/vec3_optns.c \
			  $(SRC_DIR)/vector/vec3_extreme.c \
			  $(SRC_DIR)/vector/vector_utils.c \
			  $(SRC_DIR)/vector/vector.c \
			  $(SRC_DIR)/vector/vec3_rotate.c \
			  $(SRC_DIR)/ray/ray.c \
			  $(SRC_DIR)/ray/cylinder_calculus.c \
			  $(SRC_DIR)/ray/intersect_utils.c \
			  $(SRC_DIR)/ray/intersect.c \
			  $(SRC_DIR)/objects/sphere.c \
			  $(SRC_DIR)/objects/plane.c \
			  $(SRC_DIR)/objects/cylinder.c \
			  $(SRC_DIR)/objects/objects.c \
			  $(SRC_DIR)/objects/object_utils.c \
			  $(SRC_DIR)/render/render.c \
			  $(SRC_DIR)/render/render_utils.c \
			  $(SRC_DIR)/scene/scene.c \
			  $(SRC_DIR)/scene/scene_utils.c \
			  $(SRC_DIR)/scene/scene_free.c \
			  $(SRC_DIR)/scene/lighting_calculus.c \
			  $(SRC_DIR)/color/color_rgb.c \
			  $(SRC_DIR)/color/color_utils.c \
			  $(SRC_DIR)/color/color.c \
			  $(SRC_DIR)/utils/utils.c

OBJS		= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Header files - explicitly listed
INCS		= $(INC_DIR)/minirt.h \
			  $(INC_DIR)/parser.h \
			  $(INC_DIR)/vector.h \
			  $(INC_DIR)/ray.h \
			  $(INC_DIR)/objects.h \
			  $(INC_DIR)/scene.h \
			  $(INC_DIR)/color.h

# Libft
LIBFT_DIR	= libft
LIBFT		= $(LIBFT_DIR)/libft.a
LIBFT_FLAGS	= -L$(LIBFT_DIR) -lft

# Rules
all: $(LIBFT) $(MINILIBX_DIR)/libmlx.a $(NAME)

# Rule to build libft
$(LIBFT):
	@echo "🔨 Compiling libft..."
	@make -C $(LIBFT_DIR)

$(MINILIBX_DIR)/libmlx.a:
	@echo "🔨 Compiling MinilibX..."
	@make -C $(MINILIBX_DIR)

$(NAME): $(OBJS)
	@echo "🔨 Compiling $(NAME)..."
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFT_FLAGS) $(MLXFLAGS) $(MATHFLAGS)
	@echo "✅ Compilation complete!"

# Compile source files to object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCS)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -I$(INC_DIR) -I$(MINILIBX_DIR) -I$(LIBFT_DIR) -c $< -o $@

# Clean object files
clean:
	@echo "🧹 Cleaning object files..."
	@rm -rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean
	@if [ -d $(MINILIBX_DIR) ] && [ -f $(MINILIBX_DIR)/Makefile ]; then \
		make -C $(MINILIBX_DIR) clean; \
	fi
	@echo "✅ Object files cleaned!"

# Full clean
fclean: clean
	@echo "🧹 Removing executable..."
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@echo "✅ Executable removed!"

# Rebuild
re: fclean all

# Bonus target (if needed)
bonus: all

# Phony targets
.PHONY: all clean fclean re bonus

# Helpful information
help:
	@echo "Available targets:"
	@echo "  all     : Build the project"
	@echo "  clean   : Remove object files"
	@echo "  fclean  : Remove object files and executable"
	@echo "  re      : Rebuild the project"