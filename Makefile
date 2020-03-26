# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/11 15:11:22 by bnesoi            #+#    #+#              #
#    Updated: 2019/07/10 13:57:12 by bnesoi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=fractol

OS			=	$(shell uname -s)
CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror

SRC_FILES	=			\
	animation.c			\
	app.c				\
	app_utils.c			\
	events.c			\
	file_io.c			\
	gradient.c			\
	gradient_utils.c	\
	main.c				\
	renderer.c			\
	renderer_utils.c	\
	utils.c				\
	ocl/ocl_error.c  	\
	ocl/ocl_init.c  	\
	ocl/ocl_program.c  	\
	ocl/ocl_utils.c

HDR_FILES	=			\
	file_io.h			\
	fractol.h			\
	gradient.h			\
	ocl.h

DIR_SRC		=	./src
DIR_INC		=	./include
DIR_OBJ		=	./obj

LIBFT		=	./libft/libft.a
LIBFT_DIR	=	./libft

FT_PRINTF		=	./ft_printf/libftprintf.a
FT_PRINTF_DIR	=	./ft_printf

SRC			=	$(addprefix $(DIR_SRC)/, $(SRC_FILES))
HDR			=	$(addprefix $(DIR_INC)/, $(HDR_FILES))
OBJ			=	$(addprefix $(DIR_OBJ)/, $(SRC_FILES:.c=.o))

INCLUDES	=	-I $(LIBFT_DIR) -I $(FT_PRINTF_DIR)/include -I $(DIR_INC)
LIBS		:=	./libft/libft.a -lm ./ft_printf/libftprintf.a

ifeq ($(OS),Linux)
	LIBS	:= $(LIBS) -lOpenCL
	MINILIBX_DIR=./minilibx
	MINILIBX_LINK=-L$(MINILIBX_DIR) -lmlx -lXext -lX11
else
	LIBS	:= $(LIBS) -framework OpenCL
	MINILIBX_DIR=./minilibx_macos
	MINILIBX_LINK=-L$(MINILIBX_DIR) -lmlx -framework OpenGL -framework AppKit
endif

INCLUDES:= $(INCLUDES) -I $(MINILIBX_DIR)
LIBS	:= $(LIBS) $(MINILIBX_LINK)
MINILIBX=$(MINILIBX_DIR)/libmlx.a

all: $(NAME)

$(DIR_OBJ):
	@mkdir $(DIR_OBJ)
	@mkdir $(DIR_OBJ)/ocl

$(NAME): $(MINILIBX)  $(DIR_OBJ) $(OBJ) $(LIBFT) $(FT_PRINTF)
	$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $(NAME) $(SDL_LINK)

$(DIR_OBJ)/%.o:$(DIR_SRC)/%.c $(HDR)
	$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@

$(MINILIBX): FAKE
	@$(MAKE) -C $(MINILIBX_DIR)/ --no-print-directory

$(LIBFT): FAKE
	@$(MAKE) -C $(LIBFT_DIR)/ --no-print-directory

$(FT_PRINTF): FAKE
	@$(MAKE) -C $(FT_PRINTF_DIR)/ --no-print-directory

clean :
	@/bin/rm -rf $(DIR_OBJ)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(FT_PRINTF_DIR) clean
	@$(MAKE) -C $(MINILIBX_DIR) clean

fclean : clean
	@/bin/rm -f $(NAME) $(addprefix tests/test_,$(FILE_NAMES))
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@$(MAKE) -C $(FT_PRINTF_DIR) fclean
	@/bin/rm -f $(addprefix tests/,$(TEST_NAMES))

re : fclean all

.PHONY: FAKE
