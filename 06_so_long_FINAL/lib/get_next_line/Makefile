# **************************************************************************** #
#                          GET_NEXT_LINE STANDARDIZED                            #
# **************************************************************************** #

NAME    := libgnl.a
CC      := cc
CFLAGS  := -Wall -Wextra -Werror
AR      := ar rcs
RM      := rm -f
RMD     := rm -rf

SRC_DIR := src
OBJ_DIR := obj
INC_DIR := ../../includes

SRC_FILES := get_next_line.c \
             get_next_line_utils.c

SRC      := $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS     := $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

# ================= Colors ===================
GREEN   = \033[0;32m
BLUE    = \033[0;34m
YELLOW  = \033[1;33m
RED     = \033[0;31m
RESET   = \033[0m
BOLD    = \033[1m

# **************************************************************************** #
#                                  RULES                                       #
# **************************************************************************** #

all: $(NAME)
	@echo "$(GREEN)Build complete!$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@echo "$(BLUE)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(NAME): $(OBJS)
	@echo "$(YELLOW)Creating archive $(NAME)...$(RESET)"
	@$(AR) $(NAME) $(OBJS)

clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	@$(RMD) $(OBJ_DIR)

fclean: clean
	@echo "$(RED)Removing archive...$(RESET)"
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
