.PHONY: clean all re fclean
CFLAGS = -Wall -Wextra -Werror -fsanitize=thread
NAME = philo
SRC = philo.c tools.c create_threads.c threads_fct.c philo_checker.c check_arg.c

OBJ = $(SRC:.c=.o)

all: $(OBJ) $(NAME)

$(NAME):
	@gcc $(CFLAGS) -o $(NAME) $(SRC)
	@echo "done"

clean:
	@rm -f $(OBJ)
	@echo "OBJ deleted"

fclean: clean
	@rm -f $(NAME)
	@echo "$(NAME) deleted"

re: fclean all