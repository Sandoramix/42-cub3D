NAME = cub3D
NAME_BONUS = cub3D_bonus

# -----$(NAME) but uppercase----------------------------------------------------

PNAME = $(shell echo -n ${NAME} | tr 'a-z' 'A-Z')
PNAME_BONUS = $(shell echo -n ${NAME_BONUS} | tr 'a-z' 'A-Z')

# ----CONFIGURATIONS------------------------------------------------------------
# THIS ENABLES SOME FEATURES FOR DEBUGGING (if they're not removed already)
DEBUG_VALUE=1
# SET THESE 2 LINES TO 0 IF YOU WANT THE GAME TO TAKE FULL SCREEN'S SIZE
WINDOW_WIDTH=1280
WINDOW_HEIGHT=720
# -----VARIABLES-DECLARATIONS-+-OVVERRIDES--------------------------------------

ROOTDIR=./src
LIBFTX_DIR=$(ROOTDIR)/libs/libftx
MLX_DIR = $(ROOTDIR)/libs/minilibx

CC = cc
INCLUDES = -I$(ROOTDIR)/includes -I$(LIBFTX_DIR)/includes -I$(MLX_DIR)
MLX_NAME = mlx_$(shell uname)
MLX_FLAGS = -L$(MLX_DIR) -l$(MLX_NAME) -lXext -lX11

GAME_CONFIG_DEFINES=-DWINDOW_WIDTH=$(WINDOW_WIDTH) -DWINDOW_HEIGHT=$(WINDOW_HEIGHT)
CFLAGS = -Wall -Wextra -Werror -g $(INCLUDES) -DDEBUG=$(DEBUG_VALUE) $(GAME_CONFIG_DEFINES)

RM = rm -rf

# ----SOURCE-FILES--------------------------------------------------------------

SRC = ./main.c \
	./src/cleanup.c \
	./src/deltatime.c \
	./src/draw_helpers/draw_line.c \
	./src/draw_helpers/draw_pixel.c \
	./src/draw_helpers/draw_rectangle.c \
	./src/init_config.c \
	./src/messages/parse_error_msg.c \
	./src/mlx_engine/events/camera_horizontal_event.c \
	./src/mlx_engine/events/camera_vertical_event.c \
	./src/mlx_engine/events/movement_horizontal_event.c \
	./src/mlx_engine/events/movement_vertical_event.c \
	./src/mlx_engine/game_loop.c \
	./src/mlx_engine/key_events.c \
	./src/mlx_engine/mlx_setup.c \
	./src/parsing/parse.c \
	./src/parsing/parse_config_utils.c \
	./src/parsing/parse_config_value.c \
	./src/parsing/parse_configs.c \
	./src/parsing/parse_map.c \
	./src/parsing/parse_path_utils.c \
	./src/parsing/parse_utils.c \
	./src/rendering/raycasting/raycasting_init.c \
	./src/rendering/raycasting/raycasting_utils.c \
	./src/rendering/render.c \
	./src/rendering/render_crosshair.c \
	./src/rendering/render_sprites.c \
	./src/texture.c \
	./src/utils/color_utils.c \
	./src/utils/map_utils.c \
	./src/utils/math_utils.c \
	./src/utils/mouse_utils.c \
	./src/utils/player_utils.c \
	./src/utils/point_utils.c

SRC_BONUS = ./src/mlx_engine/events/mouse_movement_event_bonus.c \
	./src/mlx_engine/events/player_sprites_events_bonus.c \
	./src/rendering/render_minimap_bonus.c \
	./src/utils/collisions_utils_bonus.c

# ----RULES---------------------------------------------------------------------

all: $(NAME)
$(NAME): $(SRC) $(SRC_BONUS)
	@$(MAKE) -C $(LIBFTX_DIR) DEBUG_VALUE=$(DEBUG_VALUE)

	if [ ! -f $(MLX_DIR)/$(MLX_LIBNAME) ] && [ ! -d $(MLX_DIR) ] ; then $(MAKE) download-mlx; fi
	@$(MAKE) -sC $(MLX_DIR) && ( [ ! -f $(MLX_DIR)/$(MLX_LIBNAME) ] || echo "$(GREEN)[MLX]:\t\tLIBRARY CREATED")

	@$(CC) $(CFLAGS) $(SRC) $(SRC_BONUS) -o $(NAME) -L$(LIBFTX_DIR) -lft $(MLX_FLAGS) -lm -DWITH_BONUS=0
	@echo "$(GREEN)[$(PNAME)]:\tPROGRAM CREATED$(R)"

	[ "$(strip $(DEBUG_VALUE))" = "0" ] || echo "$(RED)[$(PNAME)]:\tDEBUG MODE ENABLED$(R)"

bonus: $(NAME_BONUS)
$(NAME_BONUS): $(SRC) $(SRC_BONUS)
	@$(MAKE) -C $(LIBFTX_DIR) DEBUG_VALUE=$(DEBUG_VALUE)

	if [ ! -f $(MLX_DIR)/$(MLX_LIBNAME) ] && [ ! -d $(MLX_DIR) ] ; then $(MAKE) download-mlx; fi
	@$(MAKE) -sC $(MLX_DIR) && ( [ ! -f $(MLX_DIR)/$(MLX_LIBNAME) ] || echo "$(GREEN)[MLX]:\t\tLIBRARY CREATED")

	@$(CC) $(CFLAGS) $(SRC) $(SRC_BONUS) -o $(NAME_BONUS) -L$(LIBFTX_DIR) -lft $(MLX_FLAGS) -lm -DWITH_BONUS=1
	@echo "$(GREEN)[$(PNAME_BONUS)]:\tPROGRAM CREATED$(R)"

	[ "$(strip $(DEBUG_VALUE))" = "0" ] || echo "$(RED)[$(PNAME_BONUS)]:\tDEBUG MODE ENABLED$(R)"

clean:
	@$(MAKE) -C $(LIBFTX_DIR) clean
	@$(MAKE) -iC $(MLX_DIR) clean || echo -n ""

fclean: clean
	@$(MAKE) -C $(LIBFTX_DIR) fclean
	[ ! -f $(NAME) ] || ($(RM) $(NAME) && echo "$(BLUE)[$(PNAME)]\t\tDELETED$(R)")
	[ ! -f $(NAME_BONUS) ] || ($(RM) $(NAME_BONUS) && echo "$(BLUE)[$(PNAME_BONUS)]\tDELETED$(R)")

re: fclean all
re-debug: fclean debug

re-force: fclean delete-mlx download-mlx all

debug:
	$(MAKE) DEBUG_VALUE=1
# ----UTILS---------------------------------------------------------------------
VALGRIND=@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --quiet --tool=memcheck --keep-debuginfo=yes
ARGS="assets/maps/with_config.cub"
valgrind: debug
	clear
	$(VALGRIND) ./$(NAME) "$(ARGS)"

MLX_LINK=https://github.com/42Paris/minilibx-linux/archive/refs/heads/master.zip
download-mlx:
	echo "$(BLUE) Downloading MLX...$(R)";
	wget $(MLX_LINK) -O minilibx-linux.zip || (echo "$(RED)SOMETHING WENT WRONG WITH MLX LINK. PLEASE UPDATE IT$(R)"; exit 1)
	unzip minilibx-linux.zip
	mv minilibx-linux-master $(MLX_DIR)
	$(RM) minilibx-linux.zip*

delete-mlx:
	@$(RM) $(MLX_DIR)
# ------------------------------------------------------------------------------

.PHONY: all clean fclean re re-debug debug download-mlx test re-force delete-mlx
.SILENT:

# ----COLORS--------------------------------------------------------------------
GREEN=\033[0;32m
RED=\033[0;31m
BLUE=\033[0;34m
R=\033[0m