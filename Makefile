NAME = cub3D
NAME_BONUS = cub3D_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror
MLX_DIR = ./mlx
MLX_LIB = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -L$(MLX_DIR) -Lmlx -lmlx -lXext -lX11 -lm

SRCDIR = src
BONUSDIR = bonus
OBJDIR = obj
OBJDIR_BONUS = obj_bonus
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

BONUS_SOURCES = bonus/main_bonus.c \
				bonus/core/engine_bonus.c \
				bonus/core/engine_init_bonus.c \
				bonus/core/engine_error_bonus.c \
				bonus/entities/character_bonus.c \
				bonus/entities/texture_bonus.c \
				bonus/entities/world_bonus.c \
				bonus/entities/world_parsing_bonus.c \
				bonus/entities/world_utils_bonus.c \
				bonus/entities/world_validation_bonus.c \
				bonus/graphics/ray_tracer_bonus.c \
				bonus/graphics/ray_calculation_bonus.c \
				bonus/graphics/renderer_bonus.c \
				bonus/graphics/renderer_core_bonus.c \
				bonus/graphics/render_drawing_bonus.c \
				bonus/input/keyboard_bonus.c \
				bonus/input/mouse_bonus.c \
				bonus/input/movement_bonus.c \
				bonus/input/rotation_bonus.c \
				bonus/input/collision_bonus.c \
				bonus/input/hooks_bonus.c \
				bonus/utils/string_utils_bonus.c \
				bonus/utils/string_array_utils_bonus.c \
				bonus/utils/string_manipulation_bonus.c \
				bonus/utils/memory_utils_bonus.c

OBJECTS = $(SOURCES:%.c=$(OBJDIR)/%.o)

BONUS_OBJECTS = $(BONUS_SOURCES:%.c=$(OBJDIR)/%.o)

INCLUDES = -I$(INCDIR) -Imlx

all: $(NAME)

$(NAME): $(MLX_LIB) $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $(MLX_FLAGS) -o $(NAME)

$(MLX_LIB):
	@make -C $(MLX_DIR)

$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(MLX_LIB) $(BONUS_OBJECTS)
	$(CC) $(CFLAGS) $(BONUS_OBJECTS) $(MLX_FLAGS) -o $(NAME_BONUS)

clean:
	rm -rf $(OBJDIR) $(OBJDIR_BONUS)
	@make -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME) $(NAME_BONUS)
	@make -C $(MLX_DIR) fclean

re: fclean all

.PHONY: all bonus clean fclean re
