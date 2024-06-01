# ********************************************************************* #
#  __   __  _______  ___   _  _______  _______  ___   ___      _______  #
# |  |_|  ||   _   ||   | | ||       ||       ||   | |   |    |       | #
# |       ||  |_|  ||   |_| ||    ___||    ___||   | |   |    |    ___| #
# |       ||       ||      _||   |___ |   |___ |   | |   |    |   |___  #
# |       ||       ||     |_ |    ___||    ___||   | |   |___ |    ___| #
# | ||_|| ||   _   ||    _  ||   |___ |   |    |   | |       ||   |___  #
# |_|   |_||__| |__||___| |_||_______||___|    |___| |_______||_______| #
#                                                                       #
# ********************************************************************* #

# ************************************************** #

NAME			=	cub3D

CC				=	cc

CFLAGS			=	-Wall -Wextra -Werror -g3

IFLAGS			=	-I ./includes/ -I ./lib/minilibx-linux/ -I ./lib/libft/

INCLUDES		=	./includes/cub3d.h ${LIB_H} ${MLX_H}

SRCS_D			=	srcs/

SRCS_ERR_D		=	${SRCS_D}error/

SRCS_PARSING_D	=	${SRCS_D}parsing/

OBJS_D			=	.obj/

SRCS			=	${SRCS_D}main.c

SRCS_ERR		=	${SRCS_ERR_D}error_handling.c

SRCS_PARSING	=	${SRCS_PARSING_D}parsing.c \
					${SRCS_PARSING_D}get_file.c \
					${SRCS_PARSING_D}get_data.c \
					${SRCS_PARSING_D}get_sprites_path.c \
					${SRCS_PARSING_D}get_color_rgb.c \
					${SRCS_PARSING_D}get_maps.c \
					${SRCS_PARSING_D}check_map.c \
					${SRCS_PARSING_D}handle_errors.c \

OBJS			=	${patsubst ${SRCS_D}%.c, ${OBJS_D}%.o, ${SRCS}}

OBJS_ERR		=	${patsubst ${SRCS_ERR_D}%.c, ${OBJS_D}%.o, ${SRCS_ERR}}

OBJS_PARSING	=	${patsubst ${SRCS_PARSING_D}%.c, ${OBJS_D}%.o, ${SRCS_PARSING}}

# ************************************************** #

LIB_H			=	./lib/libft/libft.h

LIB_A			=	./lib/libft/libft.a

MLX_H			=	./lib/minilibx-linux/mlx.h

MLX_A			=	./lib/minilibx-linux/libmlx.a

# ************************************************** #

all :				${NAME}

${NAME} :			${OBJS_D} ${OBJS} ${OBJS_ERR} ${OBJS_PARSING} ${INCLUDES} Makefile
	${MAKE} -C lib/libft/ 
	${MAKE} -C lib/minilibx-linux
	${CC} ${CFLAGS} ${OBJS} ${OBJS_ERR} ${OBJS_PARSING} ${LIB_A} ${MLX_A} -lXext -lX11 -lm -lz -o $@

${OBJS_D}%.o :		${SRCS_D}%.c ${INCLUDES} Makefile
	${CC} ${CFLAGS} ${IFLAGS} -c $< -o $@

${OBJS_D}%.o :		${SRCS_ERR_D}%.c ${INCLUDES} Makefile
	${CC} ${CFLAGS} ${IFLAGS} -c $< -o $@

${OBJS_D}%.o :		${SRCS_PARSING_D}%.c ${INCLUDES} Makefile
	${CC} ${CFLAGS} ${IFLAGS} -c $< -o $@

${OBJS_D}:
	mkdir -p $@

clean :
	${MAKE} clean -C lib/libft 
	${MAKE} clean -C lib/minilibx-linux
	rm -rf ${OBJS_D}

fclean :			clean
	${MAKE} fclean -C lib/libft
	rm -rf ${NAME}

re :				fclean all

# ************************************************** #

.PHONY :			all clean fclean re

# ************************************************** #