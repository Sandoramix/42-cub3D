NAME = cub3D

# -----$(NAME) but uppercase----------------------------------------------------

PNAME = $(shell echo -n ${NAME} | tr 'a-z' 'A-Z')

# -----VARIABLES-DECLARATIONS-+-OVVERRIDES--------------------------------------

DEBUG_VALUE=0

ROOTDIR=./src
LIBFTX_DIR=$(ROOTDIR)/libs/libftx
MLX_DIR = $(ROOTDIR)/libs/minilibx

CC = cc
INCLUDES = -I$(ROOTDIR)/includes -I$(LIBFTX_DIR)/includes -I$(MLX_DIR)
MLX_NAME = mlx_$(shell uname)
MLX_FLAGS = -L$(MLX_DIR) -l$(MLX_NAME) -lXext -lX11
CFLAGS = -Wall -Wextra -Werror -g $(INCLUDES) -DDEBUG=$(DEBUG_VALUE)

RM = rm -rf

# ----SOURCE-FILES--------------------------------------------------------------

SRC = ./main.c \
        ./src/cleanup.c \
        ./src/conditionals.c \
        ./src/deltatime.c \
        ./src/events/events.c \
        ./src/events/events_handler.c \
        ./src/events/mlx_config.c \
        ./src/messages/parse_error_msg.c \
        ./src/parsing/parse.c \
        ./src/parsing/parse_configurations.c \
        ./src/parsing/parse_utils.c \
        ./src/rendering/drawing_helpers.c \
        ./src/rendering/math_helpers.c \
        ./src/rendering/rendering_helpers.c \
        ./src/rendering/rendering_init.c \
        ./src/rendering/rendering_logic.c
# ----RULES---------------------------------------------------------------------

all: $(NAME)

debug:
	$(MAKE) DEBUG_VALUE=1

$(NAME): $(SRC)
	@$(MAKE) -C $(LIBFTX_DIR)

	if [ ! -f $(MLX_DIR)/$(MLX_LIBNAME) ] && [ ! -d $(MLX_DIR) ] ; then $(MAKE) download-mlx; fi
	@$(MAKE) -sC $(MLX_DIR) 1>/dev/null 2>/dev/null && ( [ ! -f $(MLX_DIR)/$(MLX_LIBNAME) ] || echo "$(GREEN)[MLX]:\t\tLIBRARY CREATED")

	@$(CC) $(CFLAGS) $(SRC) -o $(NAME) -L$(LIBFTX_DIR) -lft $(MLX_FLAGS) -lm
	@echo "$(GREEN)[$(PNAME)]:\tPROGRAM CREATED$(R)"

	[ "$(strip $(DEBUG_VALUE))" = "0" ] || echo "$(RED)[$(PNAME)]:\tDEBUG MODE ENABLED$(R)"

clean:
	@$(MAKE) -C $(LIBFTX_DIR) clean
	@$(MAKE) -iC $(MLX_DIR) clean || echo -n ""

fclean: clean
	@$(MAKE) -C $(LIBFTX_DIR) fclean
	@$(RM) $(NAME)
	@echo "$(BLUE)[$(PNAME)]:\tPROGRAM DELETED$(R)"

re: fclean all
re-debug: fclean debug

re-force: fclean delete-mlx download-mlx all

# ----UTILS---------------------------------------------------------------------
VALGRIND=@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --quiet --tool=memcheck --keep-debuginfo=yes
ARGS="assets/maps/mappa.cub"
# FOR FD 		TRACKING: --track-fds=yes
# FOR CHILDREN	TRACKING: --trace-children=yes
valgrind: debug
	clear
	$(VALGRIND) ./$(NAME) "$(ARGS)"

download-mlx:
	echo "$(BLUE) Downloading MLX...$(R)";
	wget https://cdn.intra.42.fr/document/document/25837/minilibx-linux.tgz || (echo "$(RED)SOMETHING WENT WRONG WITH MLX LINK. PLEASE UPDATE IT$(R)"; exit 1)
	tar -xf minilibx-linux.tgz
	mv minilibx-linux $(MLX_DIR)
	$(RM) minilibx-linux.tgz*

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