.PHONY: clean all re fclean
CC = gcc
CFLAGS = -Wall -Wextra -Werror #-fsanitize=thread -g
NAME = philo
SRC = philo.c tools.c create_threads.c time.c mutex_lock.c threads_fct.c philo_checker.c check_arg.c print_log.c

OBJ = $(SRC:.c=.o)

all: $(OBJ) $(NAME)

$(NAME):
	@CC $(CFLAGS) -o $(NAME) $(SRC)
	@echo "done"

clean:
	@rm -f $(OBJ)
	@echo "OBJ deleted"

fclean: clean
	@rm -f $(NAME)
	@echo "$(NAME) deleted"

re: fclean all