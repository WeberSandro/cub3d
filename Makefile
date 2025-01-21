# Nome do executável
NAME = cub3d

# Compilador e flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -Ilib/minilibx-linux -Ilib/libft -Iinclude -no-pie -g

# Diretórios
SRCS_DIRS = src map player render utills textures
OBJS_DIR = obj
LIBMLX_DIR = lib/minilibx-linux
LIBFT_DIR = lib/libft
ASSETS_DIR = asserts

# Arquivos fontes e objetos
SRCS = $(shell find $(SRCS_DIRS) -type f -name '*.c')
OBJS = $(patsubst %.c, $(OBJS_DIR)/%.o, $(SRCS))

# Bibliotecas
LIBS = -L$(LIBMLX_DIR) -lmlx -lm -lX11 -lXext -lbsd -L$(LIBFT_DIR) -lft

# Cores para saída
RESET = \033[0m
GREEN = \033[32m
YELLOW = \033[33m
RED = \033[31m
BLUE = \033[34m
CYAN = \033[36m

# Regras
all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_DIR)/libft.a $(LIBMLX_DIR)/libmlx.a
	@printf "$(CYAN)Linking $(NAME)...$(RESET)\n"
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS)
	@printf "$(GREEN)Build complete!$(RESET)\n"

$(LIBFT_DIR)/libft.a:
	@printf "$(CYAN)Compiling libft...$(RESET)\n"
	@make -C $(LIBFT_DIR)

$(LIBMLX_DIR)/libmlx.a:
	@printf "$(CYAN)Compiling MinilibX...$(RESET)\n"
	@make -C $(LIBMLX_DIR)

$(OBJS_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@printf "$(BLUE)Compiling $<...$(RESET)\n"
	$(CC) $(CFLAGS) -c $< -o $@

valgrind: $(NAME)
	@printf "$(CYAN)Running Valgrind on $(NAME)...$(RESET)\n"
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=valgrind-report.txt ./$(NAME) asserts/maps/level1.cub
	@printf "$(GREEN)Valgrind finished. Check valgrind-report.txt for details.$(RESET)\n"


clean:
	@printf "$(RED)Cleaning objects...$(RESET)\n"
	rm -rf $(OBJS_DIR)
	@make -C $(LIBFT_DIR) clean
	@make -C $(LIBMLX_DIR) clean

fclean: clean
	@printf "$(RED)Cleaning executable and libraries...$(RESET)\n"
	rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@rm -f $(LIBMLX_DIR)/libmlx.a

re: fclean all

.PHONY: all clean fclean re
