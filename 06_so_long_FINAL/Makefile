# **************************************************************************** #
#                                CONFIGURATION                                 #
# **************************************************************************** #

NAME	:= so_long
CC		:= cc
CFLAGS	:= -Wall -Wextra -Werror -Ofast #-g -fsanitize=address -O0
LIBMLX	:= ./lib/MLX42
SRC_DIR	:= src
OBJ_DIR := obj

# **************************************************************************** #
#                                HEADERS                                       #
# **************************************************************************** #

HEADERS	:= -I ./includes -I $(LIBMLX)/include

# **************************************************************************** #
#                                LIBRARIES                                     #
# **************************************************************************** #

LIBFT     := lib/libft/libft.a
FT_PRINTF := lib/ft_printf/ft_printf.a
GNL       := lib/get_next_line/libgnl.a
LIBS      := $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm 
LIBS      += lib/libft/libft.a
LIBS      += lib/ft_printf/ft_printf.a
LIBS      += lib/get_next_line/libgnl.a

# **************************************************************************** #
#                                OBJECTS                                       #
# **************************************************************************** #

SRC_FILES = helpers.c \
main.c \
map_utils.c \
play_game.c \
player.c \
read_map.c \
solution.c \
utils.c \
validation.c \
free_functions.c

SRCS:= $(addprefix $(SRC_DIR)/, $(SRC_FILES))
# OBJS	:= ${SRCS:.c=.o}
OBJS := $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))


# **************************************************************************** #
#                                COLORS                                        #
# **************************************************************************** #
GREEN	= \033[0;32m
BLUE	= \033[0;34m
YELLOW	= \033[1;33m
RED		= \033[0;31m
PURPLE	= \033[0;35m
RESET	= \033[0m
BOLD	= \033[1m
ITALIC	= \033[3m

# **************************************************************************** #
#                                   RULES                                      #
# **************************************************************************** #

all: libmlx libs $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)
	@echo "$(GREEN)$(BOLD)Build complete: $(NAME)$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

# **************************************************************************** #
#                                EXT LIBRARIES                                 #
# **************************************************************************** #
libs:
	@echo "$(PURPLE)$(BOLD)Building Libs$(RESET)\n"
	@$(MAKE) -C lib/libft
	@$(MAKE) -C lib/ft_printf
	@$(MAKE) -C lib/get_next_line

libmlx:
	@echo "$(PURPLE)$(BOLD)Building MLX42$(RESET)"
	@cmake $(LIBMLX) -B $(LIBMLX)/build && $(MAKE) -C $(LIBMLX)/build -j4

# **************************************************************************** #
#                                CLEANING RULES                                #
# **************************************************************************** #
clean:
	@rm -f $(OBJS)
	@$(MAKE) -C lib/libft clean
	@$(MAKE) -C lib/ft_printf clean
	@$(MAKE) -C lib/get_next_line clean
	@echo "$(RED)Cleaned objects$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@rm -rf $(LIBMLX)/build
	@$(MAKE) -C lib/libft fclean
	@$(MAKE) -C lib/ft_printf fclean
	@$(MAKE) -C lib/get_next_line fclean
	@echo "$(RED)Full clean done$(RESET)"

re: fclean all

.PHONY: all clean fclean re libs libmlx
