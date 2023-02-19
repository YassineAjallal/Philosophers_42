.PHONY: clean all re fclean
CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = philo
SRC = philo.c

OBJ = $(SRC:.c=.o)

all: $(OBJ) $(NAME)

$(NAME):
	@CC $(CFLAGS) -o $(NAME) $(SRC)
	@ar rc $(NAME) $(OBJ)
	@echo "done"

clean:
	@rm -f $(OBJ)
	@echo "OBJ deleted"

fclean: clean
	@rm -f $(NAME)
	@echo "$(NAME) deleted"

re: fclean all