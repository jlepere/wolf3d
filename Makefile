# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jlepere <jlepere@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/01/09 11:50:13 by jlepere           #+#    #+#              #
#*   Updated: 2017/04/19 14:45:55 by jlepere          ###   ########.fr       *#
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean norme re

CXX = gcc
NAME = wolf3d
CFLAGS = -Wall -Werror -Wextra
LFLAGS = -framework OpenGL -framework AppKit -lmlx -lft

SRC_PATH = ./srcs/
OBJ_PATH = ./objs/
INC_PATH = ./include/
LIB_PATH = ./libft/ ./minilibx_macos/

SRC_NAME = main.c env.c map.c player.c draw.c events.c raycasting.c

OBJ_NAME = $(SRC_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))
LIB = $(addprefix -L, $(LIB_PATH))
INC = $(addprefix -I, $(INC_PATH))
INC += $(addprefix -I, libft/includes/)
INC += $(addprefix -I, minilibx_macos/)

all: $(NAME)

$(NAME): $(OBJ)
	@$(foreach DIR, $(LIB_PATH), $(MAKE) -sC $(DIR) ;)
	@$(CXX) $^ $(LIB) $(LFLAGS) -o $@
	@printf "%-72s\033[32;01m[FINISH]\033[0m\n" "[BIN] Built target $@ ..."

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@$(CXX) $(CFLAGS) $(INC) -c $< -o $@
	@printf "%-73s\033[33;01m[BUILD]\033[0m\n" "[GCC] Building object $@ ..."

clean:
	@$(foreach DIR, $(LIB_PATH), $(MAKE) -sC $(DIR) clean;)
	@rm -f $(OBJ)
	@rmdir $(OBJ_PATH) 2> /dev/null || true
	@printf "%-73s\033[31;01m[CLEAN]\033[0m\n" "[BIN] Clear target $(NAME) ..."

fclean: clean
	@rm -f $(NAME)

norme:
	norminette $(SRC_PATH)
	norminette $(INC_PATH)

re: fclean all
