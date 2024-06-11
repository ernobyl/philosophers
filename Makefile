NAME = philo
CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf
SRCS =	main.c

$(NAME) :
	$(CC) $(CFLAGS) $(SRCS) -o $(NAME)

all : $(NAME)

fclean : clean
	$(RM) $(NAME)

clean :
	$(RM) $(NAME)

re: clean all

.PHONY: all, clean, fclean, re