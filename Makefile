# Program name
NAME = cub3D

# Directories
SRCDIR = src
INCDIR = include
OBJDIR = obj
MLXDIR = mlx

# Source files organized by MVC pattern
MODEL_FILES = model/map_parser.c model/map_validator.c model/player.c model/texture.c
VIEW_FILES = view/renderer.c view/raycasting.c view/texture_manager.c view/floor_ceiling.c view/minimap.c view/fps_display.c
CONTROLLER_FILES = controller/game_controller.c controller/input_handler.c controller/movement.c controller/mouse_handler.c controller/smooth_movement.c
UTILS_FILES = utils/error_handler.c utils/string_utils.c utils/memory_utils.c utils/performance.c
MAIN_FILES = main.c

# All source files
SOURCES = $(MAIN_FILES) $(MODEL_FILES) $(VIEW_FILES) $(CONTROLLER_FILES) $(UTILS_FILES)
SRCFILES = $(addprefix $(SRCDIR)/, $(SOURCES))
OBJFILES = $(addprefix $(OBJDIR)/, $(SOURCES:.c=.o))

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I$(INCDIR) -I$(MLXDIR)
LDFLAGS = -L$(MLXDIR) -lmlx -lXext -lX11 -lm -lz
DEBUG_FLAGS = -g -fsanitize=address

# Colors for output
GREEN = \033[0;32m
RED = \033[0;31m
BLUE = \033[0;34m
RESET = \033[0m

# Default target
all: $(NAME)

# Create object directory
$(OBJDIR):
	@mkdir -p $(OBJDIR)
	@mkdir -p $(OBJDIR)/model
	@mkdir -p $(OBJDIR)/view
	@mkdir -p $(OBJDIR)/controller
	@mkdir -p $(OBJDIR)/utils

# Build MLX library
$(MLXDIR)/libmlx.a:
	@echo "$(BLUE)Building MLX library...$(RESET)"
	@$(MAKE) -C $(MLXDIR)

# Compile object files
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	@echo "$(GREEN)Compiling $<$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

# Link executable
$(NAME): $(OBJFILES) $(MLXDIR)/libmlx.a
	@echo "$(BLUE)Linking $(NAME)...$(RESET)"
	@$(CC) $(OBJFILES) $(LDFLAGS) -o $(NAME)
	@echo "$(GREEN)$(NAME) successfully created!$(RESET)"

# Debug build
debug: CFLAGS += $(DEBUG_FLAGS)
debug: $(NAME)

# Clean object files
clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	@rm -rf $(OBJDIR)
	@$(MAKE) -C $(MLXDIR) clean

# Clean everything
fclean: clean
	@echo "$(RED)Cleaning $(NAME)...$(RESET)"
	@rm -f $(NAME)

# Rebuild everything
re: fclean all

# Test with sample map
test: $(NAME)
	@echo "$(BLUE)Running test with sample map...$(RESET)"
	@./$(NAME) assets/maps/sample.cub

# Install dependencies (if needed)
install:
	@echo "$(BLUE)Installing dependencies...$(RESET)"
	# Add any dependency installation commands here

# Check for memory leaks
leak: debug
	@echo "$(BLUE)Running with leak detection...$(RESET)"
	@leaks --atExit -- ./$(NAME) assets/maps/sample.cub

# Format code (if you have a formatter)
format:
	@echo "$(BLUE)Formatting code...$(RESET)"
	@find $(SRCDIR) $(INCDIR) -name "*.c" -o -name "*.h" | xargs clang-format -i

# Show help
help:
	@echo "Available targets:"
	@echo "  all     - Build the program"
	@echo "  debug   - Build with debug flags"
	@echo "  clean   - Remove object files"
	@echo "  fclean  - Remove all generated files"
	@echo "  re      - Rebuild everything"
	@echo "  test    - Run with sample map"
	@echo "  leak    - Run with leak detection"
	@echo "  format  - Format source code"
	@echo "  help    - Show this help"

.PHONY: all debug clean fclean re test install leak format help