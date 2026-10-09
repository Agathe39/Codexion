
.SILENT :

NAME = codexion
FLAGS = -Wall -Wextra -Werror -pthread
C_FILES = src/main.c src/parsing.c src/initialisation.c src/time.c \
		src/monitor.c src/algorithm.c src/routine.c src/routine_utils.c \
		src/thread.c src/clean.c \

ARGS = 4 800 50 50 50 2 10 fifo
OBJS = $(C_FILES:.c=.o)

.PHONY: all run clean fclean re help

all: $(NAME)

$(NAME): $(OBJS)
	cc $(FLAGS) $(OBJS) -o $(NAME)

run: $(NAME)
	./$(NAME) $(ARGS)

%.o: %.c
	cc $(FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

help:
	echo "\nmake all -> creates *.o files if they don't exist yet, or rebuilds them if outdated, then compiles the program"
	echo "make run -> execute the program using the latest version of *.o files"
	echo "make clean -> delete *.o files"
	echo "make fclean -> clean + deletes the executable file"
	echo "make re -> fclean + all\n"
