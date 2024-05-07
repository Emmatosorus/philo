NAME	=	philo
CC		=	cc
C_FLAGS	=	-Werror -Wextra -Wall -g -fsanitize=address

HDR		=	philo.h
OBJ_DIR	=	.obj/

#---------Sources---------#

SRC		= \
			main.c \
			utils.c \
			parse.c \
			routine.c \
			actions.c \
			mutex_helpers.c \
			create_philosophers.c

OBJ =	$(SRC:%.c=$(OBJ_DIR)%.o)

#---------Rules---------#

all: Makefile
	$(MAKE) $(NAME)

$(OBJ_DIR)%.o: %.c $(HDR)
	mkdir -p $(OBJ_DIR)
	$(CC) $(C_FLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(C_FLAGS) -o $(NAME) $(OBJ)

clean:
	rm -rf $(OBJ_DIR)

fclean:
	$(MAKE) clean
	rm -rf $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all clean fclean re

-include $(D_SRC)
