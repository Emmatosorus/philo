NAME	= philo

CC		= cc
CFLAGS	= -Werror -Wextra -Wall

HDR = philo.h

all: $(NAME)

NAME: $(HDR)
	$(CC) $(CFLAGS) -o $(NAME)

