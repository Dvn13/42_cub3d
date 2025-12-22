NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror
MLX_DIR = ./mlx
MLX_LIB = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -L$(MLX_DIR) -Lmlx -lmlx -lXext -lX11 -lm

SRCDIR = src
OBJDIR = obj
INCDIR = include

SOURCES = src/main.c \
		  src/core/engine.c \
		  src/core/engine_init.c \
		  src/core/engine_error.c \
		  src/entities/character.c \
		  src/entities/texture.c \
		  src/entities/world.c \
		  src/entities/world_parsing.c \
		  src/entities/world_utils.c \
		  src/entities/world_validation.c \
		  src/graphics/ray_tracer.c \
		  src/graphics/ray_calculation.c \
		  src/graphics/renderer.c \
		  src/graphics/renderer_core.c \
		  src/graphics/render_drawing.c \
		  src/input/keyboard.c \
		  src/input/mouse.c \
		  src/input/movement.c \
		  src/input/rotation.c \
		  src/input/collision.c \
		  src/input/hooks.c \
		  src/utils/string_utils.c \
		  src/utils/string_array_utils.c \
		  src/utils/string_manipulation.c \
		  src/utils/memory_utils.c

OBJECTS = $(SOURCES:%.c=$(OBJDIR)/%.o)

INCLUDES = -I$(INCDIR) -Imlx

all: $(NAME)

$(NAME): $(MLX_LIB) $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $(MLX_FLAGS) -o $(NAME)

$(MLX_LIB):
	@make -C $(MLX_DIR)

$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
