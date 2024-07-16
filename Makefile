NAME = philo
CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf
SRCS =	main.c \
		check_args.c \
		initialize.c \
		utils.c \
		data_utils.c \
		philo_utils.c \
		philo_cycle.c \

OBJS	:= ${SRCS:.c=.o}

all: $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $<

$(NAME): $(OBJS)
	@echo "Compiling Philosophers..."
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)
	@echo "Done!"

clean:
	@echo "Cleaning object files..."
	@rm -rf $(OBJS)

fclean: clean
	@echo "Cleaning everything else..."
	@rm -rf $(NAME)

re: clean all

.PHONY: all, clean, fclean, re