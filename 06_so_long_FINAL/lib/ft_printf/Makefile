# **************************************************************************** #
#                             FT_PRINTF STANDARDIZED                             #
# **************************************************************************** #

NAME    := ft_printf.a
CC      := cc
AR      := ar rcs
RM      := rm -f
RMD     := rm -rf

SRC_DIR := src
OBJ_DIR := obj
INC_DIR := ../../includes

CFLAGS  := -Wall -Wextra -Werror -I$(INC_DIR)

SRC_FILES := ft_hex.c \
ft_printf.c \
ft_ptr.c \
ftp_putchar_fd.c \
ftp_putnbr_fd.c \
ft_putunbr_fd.c \
ftp_putstr_fd.c

SRC      := $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS     := $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

# ================= Colors ===================
GREEN   = \033[0;32m
BLUE    = \033[0;34m
YELLOW  = \033[1;33m
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
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(NAME): $(OBJS)
	@echo "$(YELLOW)Creating archive $(NAME)...$(RESET)"
	@$(AR) $(NAME) $(OBJS)

clean:
	@echo "$(YELLOW)Cleaning object files...$(RESET)"
	@$(RMD) $(OBJ_DIR)

fclean: clean
	@echo "$(YELLOW)Removing archive...$(RESET)"
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
