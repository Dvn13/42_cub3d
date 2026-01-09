NAME = cub3D
NAME_BONUS = cub3D_bonus

CC = cc
CFLAGS = -Wall -Wextra -Werror

MLX_DIR = minilibx-linux
MLX_LIB = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

SRCDIR = src
BONUSDIR = bonus
OBJDIR = obj
OBJDIR_BONUS = obj_bonus
INCDIR = include
INCBNSDIR = include_bonus

SOURCES = src/main.c \
		  src/core/engine.c \
		  src/core/engine_init.c \
		  src/core/engine_error.c \
		  src/entities/character.c \
		  src/entities/file_content.c \
		  src/entities/map_check.c \
		  src/entities/map_connection.c \
		  src/entities/map_layout.c \
		  src/entities/texture.c \
		  src/entities/world_creation.c \
		  src/entities/world_parsing.c \
		  src/entities/world_utils.c \
		  src/entities/world_validation.c \
		  src/entities/world_view_parsing.c \
		  src/entities/world.c \
		  src/graphics/ray_tracer.c \
		  src/graphics/ray_calculation.c \
		  src/graphics/renderer.c \
		  src/graphics/renderer_core.c \
		  src/graphics/render_drawing.c \
		  src/input/keyboard.c \
		  src/input/mouse.c \
		  src/input/movement_process.c \
		  src/input/movement.c \
		  src/input/rotation.c \
		  src/input/collision.c \
		  src/input/hooks.c \
		  src/utils/string_utils.c \
		  src/utils/string_array_utils.c \
		  src/utils/string_manipulation.c \
		  src/utils/memory_utils.c

BONUS_SOURCES = bonus/main_bonus.c \
				bonus/core_bonus/engine_bonus.c \
				bonus/core_bonus/engine_error_bonus.c \
				bonus/core_bonus/engine_init_bonus.c \
				bonus/entities_bonus/character_bonus.c \
				bonus/entities_bonus/file_content_bonus.c \
				bonus/entities_bonus/map_check_bonus.c \
				bonus/entities_bonus/map_connection_bonus.c \
				bonus/entities_bonus/map_layout_bonus.c \
				bonus/entities_bonus/texture_bonus.c \
				bonus/entities_bonus/world_bonus.c \
				bonus/entities_bonus/world_creation_bonus.c \
				bonus/entities_bonus/world_parse_surfaces_bonus.c  \
				bonus/entities_bonus/world_parsing_bonus.c \
				bonus/entities_bonus/world_setup_validation_bonus.c \
				bonus/entities_bonus/world_utils_bonus.c \
				bonus/entities_bonus/world_validation_bonus.c \
				bonus/entities_bonus/world_view_parsing_bonus.c \
				bonus/graphics_bonus/draw_minimap_bonus.c \
				bonus/graphics_bonus/minimap_bonus.c \
				bonus/graphics_bonus/ray_calculation_bonus.c \
				bonus/graphics_bonus/ray_tracer_bonus.c \
				bonus/graphics_bonus/renderer_bonus.c \
				bonus/graphics_bonus/renderer_core_bonus.c \
				bonus/graphics_bonus/sprite_load_bonus.c \
				bonus/graphics_bonus/renderer_textures_bonus.c \
				bonus/graphics_bonus/render_drawing_bonus.c \
				bonus/graphics_bonus/render_floor_ceiling_bonus.c \
				bonus/graphics_bonus/sprite_rendering_bonus.c \
				bonus/graphics_bonus/sprite_utils_bonus.c \
				bonus/input_bonus/keyboard_bonus.c \
				bonus/input_bonus/mouse_bonus.c \
				bonus/input_bonus/movement_bonus.c \
				bonus/input_bonus/movement_process_bonus.c \
				bonus/input_bonus/rotation_bonus.c \
				bonus/input_bonus/collision_bonus.c \
				bonus/input_bonus/hooks_bonus.c \
				bonus/utils_bonus/string_utils_bonus.c \
				bonus/utils_bonus/string_array_utils_bonus.c \
				bonus/utils_bonus/string_manipulation_bonus.c \
				bonus/utils_bonus/memory_utils_bonus.c

OBJECTS = $(SOURCES:%.c=$(OBJDIR)/%.o)

BONUS_OBJECTS = $(BONUS_SOURCES:%.c=$(OBJDIR_BONUS)/%.o)

INCLUDES = -I$(INCDIR) -Imlx

INCLUDES_BONUS = -I$(INCBNSDIR) -Imlx

all: $(NAME)

$(NAME): $(MLX_LIB) $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $(MLX_FLAGS) -o $(NAME)

$(MLX_LIB):
	@if [ ! -d "$(MLX_DIR)" ]; then \
		echo "MinilibX not found. Run 'make get' then run project."; \
		exit 1; \
	fi
	@make -C $(MLX_DIR)

$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(MLX_LIB) $(BONUS_OBJECTS)
	$(CC) $(CFLAGS) $(BONUS_OBJECTS) $(MLX_FLAGS) -o $(NAME_BONUS)


$(OBJDIR_BONUS)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES_BONUS) -c $< -o $@

clean:
	rm -rf $(OBJDIR) $(OBJDIR_BONUS)
	@if [ -d "$(MLX_DIR)" ]; then make -C $(MLX_DIR) clean; fi

fclean: clean
	rm -f $(NAME) $(NAME_BONUS)
	@if [ -d "$(MLX_DIR)" ]; then make -C $(MLX_DIR) clean; fi
	rm -rf $(MLX_DIR)

get:
	@if [ ! -d "$(MLX_DIR)" ]; then \
		git clone https://github.com/42Paris/minilibx-linux.git $(MLXDIR); \
		echo "You got MinilibX now."; \
	else \
		echo "MinilibX already exists."; \
	fi

re: fclean get all bonus

.PHONY: all bonus clean fclean re get
