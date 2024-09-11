NAME = philo



SRC = $(wildcard *.c)
SRC_libft = $(wildcard libft/*.c)
OBJECTS = $(SRC:.c=.o)

CC = cc
 
CFLAGS = -Wall -Wextra -Werror  #-g3 -fsanitize=thread 

all: $(NAME) 
	@rm -rf *.o
$(NAME): $(OBJECTS)  
	@$(CC) $(CFLAGS)  $(OBJECTS)   $(libft)  -o $(NAME)

%.o: %.c 
	@$(CC) $(CFLAGS) -c -o $@ $< 

clean:
	@rm -f   $(OBJECTS)   && rm -rf *.o > /dev/null
fclean: clean
	@rm -rf ./philo

re: fclean all

.PHONY: all clean  fclean re bonus

.SECONDARY: 
