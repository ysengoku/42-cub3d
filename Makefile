# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/23 08:07:54 by yusengok          #+#    #+#              #
#    Updated: 2024/05/23 09:07:53 by yusengok         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BOLD = \033[1m
RESET = \033[0m
LIGHT_GREEN = \033[32m
MAGENTA = \033[95m
BLUE = \033[34m

NAME = cub3D

vpath %c srcs
FILES = main

SRCS = $(addsuffix .c, $(FILES))

OBJS_DIR = .objs/
OBJS = $(addprefix $(OBJS_DIR), $(addsuffix .o, $(FILES)))

HEADERS_DIR = ./includes
HEADERS = $(HEADERS_DIR)/cub3d.h
LIB_DIR = ./lib
LIBFT_DIR = $(LIB_DIR)/libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBMLX_DIR = $(LIB_DIR)/minilibx-linux
LIBMLX = $(LIBMLX_DIR)/libmlx.a

CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDE = -I$(HEADERS_DIR) -I$(LIBFT_DIR) -I$(LIBMLX_DIR)
MLXFLAGS = -lmlx -lXext -lX11 -lm
RM = rm -f

all: lib
	@$(MAKE) $(NAME)

$(NAME): $(OBJS) $(HEADER) $(LIBFT) $(LIBMLX)
	@printf "$(BLUE)$(BOLD)Building cub3D...\n$(RESET)"
	$(CC) $(CFLAGS) $(MLXFLAGS) $^ -o $@ -L $(LIBFT_DIR) -L $(LIBMLX_DIR)
	@printf "$(LIGHT_GREEN)$(BOLD)cub3D is ready to launch\n$(RESET)"

$(OBJS_DIR)%.o: %.c $(HEADERS) $(LIBFT) Makefile
	@printf "$(BLUE)$(BOLD)Compiling cub3D...\n$(RESET)"
	@mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE)

lib: $(FORCE)
	@printf "$(BLUE)$(BOLD)Compiling Libft...\n$(RESET)"
	@$(MAKE) -s -C $(LIBFT_DIR)
	@printf "$(BLUE)$(BOLD)Compiling Minilibx...\n$(RESET)"
	@$(MAKE) -s -C $(LIBMLX_DIR)

clean:
	@printf "$(BLUE)$(BOLD)Cleaning Libft...\n$(RESET)"
	@$(MAKE) -s -C $(LIBFT_DIR) clean
	@printf "$(BLUE)$(BOLD)Cleaning Minilibx...\n$(RESET)"
	@$(MAKE) -s -C $(LIBMLX_DIR) clean
	@printf "$(BLUE)$(BOLD)Cleaning cub3D...\n$(RESET)"
	@$(RM) -r $(OBJS_DIR)

fclean: clean
	@$(MAKE) -s -C $(LIBFT_DIR) fclean
	@$(RM) $(NAME)

re: fclean
	@$(MAKE) all

FORCE:

.PHONY: all clean fclean re lib