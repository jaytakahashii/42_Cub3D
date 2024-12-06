# Makefile
MAKEFILE 		= Makefile

# プロジェクト名
NAME			= cub3D

# ソースファイルとオブジェクトファイルのディレクトリ
SRC_DIR			= src/
OBJ_DIR			= .obj/

# ライブラリ
LIBFT_DIR		= libft/
LIBFT_NAME		= libft.a
MLX_DIR			= mlx/
# MacOSの場合
ifeq ($(shell uname), Darwin)
	MLX_NAME	= libmlx.a
# Linuxの場合
else
	MLX_NAME	= libmlx_Linux.a
endif

# インクルード
INCLUDE_DIR		= include/
INCLUDE			= -I$(INCLUDE_DIR)
LIBFT_INCLUDE	= -I$(LIBFT_DIR)$(INCLUDE_DIR)
MLX_INCLUDE		= -I$(MLX_DIR)$(INCLUDE_DIR)
HEADERS			= $(shell find $(INCLUDE_DIR) $(LIBFT_DIR)$(INCLUDE_DIR) $(MLX_DIR)$(INCLUDE_DIR) -name "*.h")

# 依存ファイル
DEPS			= $(HEADERS) $(MAKEFILE)

# コンパイル設定
CC				= cc
# CFLAGS			= -Wall -Wextra -Werror
# MacOSの場合
ifeq ($(shell uname), Darwin)
	LFLAGS		= -framework OpenGL -framework AppKit
# Linuxの場合
else
	LFLAGS		= -lXext -lX11 -lm
endif

# コマンド
RM				= rm -rf
NORM			= norminette

# ソースファイルをまとめる
SRC_FILES		= $(shell find $(SRC_DIR) -name "*.c" | sed "s/.*\///")

# オブジェクトファイルをまとめる
OBJS			= $(addprefix $(OBJ_DIR), $(SRC_FILES:.c=.o))

# color ***********************
Y				= "\033[33m"
R				= "\033[31m"
G				= "\033[32m"
B				= "\033[34m"
X				= "\033[0m"
UP				= "\033[A"
CUT				= "\033[K"
# *****************************

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJS) $(DEPS)
	@echo $(Y) "$(NAME) src files successfully compiled\n" $(X)
	@echo $(B) "--> Into $(LIBFT_DIR)" $(X)
	@$(MAKE) -C $(LIBFT_DIR)
	@printf $(UP)$(CUT)
	@echo $(B) "<-- Out of $(LIBFT_DIR)\n" $(X)
	@echo $(B) "$(NAME) creating" $(X)
	@printf $(UP)$(CUT)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT_DIR)$(LIBFT_NAME) $(MLX_DIR)$(MLX_NAME) $(LFLAGS) -o $(NAME)
	@echo $(G) "!! $(NAME) created !!\n" $(X)

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@echo $(Y) "Compiling $<" $(X)
	@$(CC) $(CFLAGS) $(INCLUDE) $(LIBFT_INCLUDE) $(MLX_INCLUDE) -c $< -o $@
	@printf $(UP)$(CUT)

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@printf $(UP)$(CUT)
	@$(RM) $(OBJ_DIR)
	@echo $(R) "$(OBJ_DIR) has been removed!!" $(X)

fclean:
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@printf $(UP)$(CUT)
	@$(RM) $(OBJ_DIR)
	@$(RM) $(NAME)
	@echo $(R) "$(NAME) $(OBJ_DIR) has been removed!!" $(X)

re: fclean all

leak: CFLAGS += -g
leak: LFLAGS += -fsanitize=address
leak: re

norm:
	@echo $(R) "<<< $(NAME) error count >>>" $(X)
	@norminette $(SRC_DIR) $(INCLUDE_DIR) | grep Error | grep -v Error! | wc -l
	@norminette $(SRC_DIR) $(INCLUDE_DIR) | grep Error || true

.PHONY: all clean fclean re leak norm
