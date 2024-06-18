NAME = philo
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
RM = rm -rf
SRCS =	main.c \
		initialize.c \
		utils.c \

$(NAME) :
	$(CC) $(CFLAGS) $(SRCS) -o $(NAME)

all : $(NAME)

fclean : clean
	$(RM) $(NAME)

clean :
	$(RM) $(NAME)

re: clean all

.PHONY: all, clean, fclean, re