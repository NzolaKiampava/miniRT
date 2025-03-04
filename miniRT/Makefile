NAME = miniRT

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -Iincludes
LDFLAGS = -L/usr/local/lib -lmlx -framework OpenGL -framework AppKit

# Source and object files
SRC_DIR = src
OBJ_DIR = obj
SOURCES = $(SRC_DIR)/main.c \
          $(SRC_DIR)/parser/parser.c \
          $(SRC_DIR)/parser/parse_objects.c \
          $(SRC_DIR)/parser/parse_scene.c \
          $(SRC_DIR)/vector/vector_ops.c \
          $(SRC_DIR)/vector/vector_utils.c \
          $(SRC_DIR)/ray/ray.c \
          $(SRC_DIR)/ray/intersect.c \
          $(SRC_DIR)/objects/sphere.c \
          $(SRC_DIR)/objects/plane.c \
          $(SRC_DIR)/objects/cylinder.c \
          $(SRC_DIR)/render/render.c \
          $(SRC_DIR)/render/lighting.c \
          $(SRC_DIR)/utils/color.c \
          $(SRC_DIR)/utils/error.c
OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Header files
INCLUDES = -Iincludes

# Rules
all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR) $(OBJ_DIR)/parser $(OBJ_DIR)/vector $(OBJ_DIR)/ray \
	$(OBJ_DIR)/objects $(OBJ_DIR)/render $(OBJ_DIR)/utils

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
