# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/23 08:07:54 by yusengok          #+#    #+#              #
#    Updated: 2024/06/03 15:27:32 by yusengok         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BOLD = \033[1m
RESET = \033[0m
LIGHT_GREEN = \033[32m
BLUE = \033[34m

NAME = cub3D

vpath %c srcs \
		srcs/parsing \
		srcs/raycasting	\
		srcs/rendering \
		srcs/event \
		srcs/error	\
		srcs/minimap
FILES = main	\
		parsing \
		get_file \
		get_data \
		get_sprites_path \
		get_color_rgb \
		get_maps \
		check_map \
		handle_errors	\
		set_data	\
		game_loop	\
		draw	\
		colors	\
		raycasting	\
		check_wall_hit	\
		event_handler	\
		move	\
		move_utils	\
		rotate	\
		quit	\
		error_handling	\
		ft_free	\
		minimap_bonus

SRCS = $(addsuffix .c, $(FILES))

OBJS_DIR = .objs/
OBJS = $(addprefix $(OBJS_DIR), $(addsuffix .o, $(FILES)))

HEADERS_DIR = includes/
HEADER_FILES = cub3d.h
HEADERS = $(addprefix $(HEADERS_DIR), $(HEADER_FILES))
LIB_DIR = ./lib
LIBFT_DIR = $(LIB_DIR)/libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBMLX_DIR = $(LIB_DIR)/minilibx-linux
LIBMLX = $(LIBMLX_DIR)/libmlx.a

BONUS = 0

CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDE = -I$(HEADERS_DIR) -I$(LIBFT_DIR) -I$(LIBMLX_DIR)
MLXFLAGS = -lmlx -lXext -lX11 -lm
RM = rm -f

all: lib
	@$(MAKE) $(NAME)

$(NAME): $(OBJS) $(HEADER) $(LIBFT) $(LIBMLX)
	@printf "$(BLUE)$(BOLD)Building cub3D...\n$(RESET)"
	$(CC) $(CFLAGS) $(MLXFLAGS) $^ -o $@ -L $(LIBFT_DIR) -L $(LIBMLX_DIR) -DBONUS=$(BONUS)
	@printf "$(LIGHT_GREEN)$(BOLD)cub3D is ready to launch\n$(RESET)"

$(OBJS_DIR)%.o: %.c $(HEADERS) $(LIBFT) Makefile
	@mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE) -DBONUS=$(BONUS)

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

bonus: lib
	@$(RM) -r $(OBJS_DIR)
	@$(RM) $(NAME)
	$(MAKE) all BONUS=1

FORCE:

.PHONY: all lib clean fclean re bonus
