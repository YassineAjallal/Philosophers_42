.PHONY: clean all re fclean
CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = philo
SRC = philo.c tools.c create_threads.c time.c mutex_lock.c check_nb_eat.c threads_fct.c

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