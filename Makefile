NAME = cub3D

# -----$(NAME) but uppercase----------------------------------------------------

PNAME = $(shell echo -n ${NAME} | tr 'a-z' 'A-Z')

# -----VARIABLES-DECLARATIONS-+-OVVERRIDES--------------------------------------

DEBUG_VALUE=1

ROOTDIR=./src
LIBFTX_DIR=$(ROOTDIR)/libftx
MLX_DIR = $(ROOTDIR)/minilibx

CC = cc
INCLUDES = -Iincludes -I$(LIBFTX_DIR)/includes -I$(MLX_DIR)
MLX_FLAGS = -L$(MLX_DIR) -lmlx_$(shell uname) -lXext -lX11 
CFLAGS = -Wall -Wextra -Werror -g $(INCLUDES) -DDEBUG=$(DEBUG_VALUE)

RM = rm -rf

# ----SOURCE-FILES--------------------------------------------------------------

SRC = ./main.c

# ----RULES---------------------------------------------------------------------

all: $(NAME)

debug:
	$(MAKE) DEBUG_VALUE=1

$(NAME): $(SRC)
	@$(MAKE) -C $(LIBFTX_DIR)
	@$(MAKE) -sC $(MLX_DIR) 1>/dev/null 2>/dev/null && echo "$(GREEN)[MLX]:\t\tLIBRARY CREATED"
	@$(CC) $(CFLAGS) $(SRC) -o $(NAME) -L$(LIBFTX_DIR) -lft $(MLX_FLAGS) -lm
	@echo "$(GREEN)[$(PNAME)]:\tPROGRAM CREATED$(R)"
	[ "$(strip $(DEBUG_VALUE))" = "0" ] || echo "$(RED)[$(PNAME)]:\tDEBUG MODE ENABLED$(R)"

clean:
	@$(MAKE) -C $(LIBFTX_DIR) clean
	@$(MAKE) -iC $(MLX_DIR) clean || echo -n ""

fclean: clean
	@$(MAKE) -C $(LIBFTX_DIR) fclean
	@$(RM) $(NAME)
	@$(RM) $(MLX_DIR)
	@echo "$(BLUE)[$(PNAME)]:\tPROGRAM DELETED$(R)"

re: fclean download all
re-debug: fclean debug

# ----UTILS---------------------------------------------------------------------

VALGRIND=@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --quiet --tool=memcheck --keep-debuginfo=yes
# FOR FD 		TRACKING: --track-fds=yes
# FOR CHILDREN	TRACKING: --trace-children=yes
valgrind: debug
	clear
	$(VALGRIND) ./$(NAME)

download:
	@wget https://cdn.intra.42.fr/document/document/25837/minilibx-linux.tgz
	@tar -xf minilibx-linux.tgz
	@mv minilibx-linux $(ROOTDIR)/minilibx
	@$(RM) minilibx-linux.tgz*

# ------------------------------------------------------------------------------

.PHONY: all clean fclean re re-debug debug download test
.SILENT:

# ----COLORS--------------------------------------------------------------------
GREEN=\033[0;32m
RED=\033[0;31m
BLUE=\033[0;34m
R=\033[0m