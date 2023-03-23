.PHONY: clean all re fclean
CFLAGS = -Wall -Wextra -Werror #-fsanitize=thread -pthread
NAME = philo
SRC = create_threads.c mutex.c philo.c philo_checker.c philo_fct.c threads_fct.c tools.c

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