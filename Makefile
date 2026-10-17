
.SILENT :

NAME = codexion
FLAGS = -Wall -Wextra -Werror -pthread
VALG_FLAGS = --leak-check=full --show-leak-kinds=all --track-origins=yes
FSAN_FLAGS = -g -fsanitize=thread
C_FILES = src/main.c src/parsing.c src/init.c src/time.c src/monitor.c \
		src/algorithm.c src/routine.c src/routine_utils.c \
		src/thread.c src/clean.c src/init_utils.c src/dongle.c

#    Coders	burnout	  compile  debug   refactor  nb compile  cooldown  scheduler
ARGS = 2     100      20         20       20         2         0      	fifo
OBJS = $(C_FILES:.c=.o)

.PHONY: all run valgrind helgrind clean fclean re help

all: $(NAME)

$(NAME): $(OBJS)
	cc $(FLAGS) $(OBJS) -o $(NAME)

run: $(NAME)
	./$(NAME) $(ARGS)

%.o: %.c
	cc $(FLAGS) -c $< -o $@

valgrind: $(NAME)
	valgrind $(VALG_FLAGS) ./$(NAME) $(ARGS)

helgrind: $(NAME)
	valgrind --tool=helgrind --fair-sched=yes ./$(NAME) $(ARGS)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME) $(NAME)_tsan

re: fclean all

help:
	echo "\nmake all -> creates *.o files if they don't exist yet, or rebuilds them if outdated, then compiles the program"
	echo "make run -> execute the program using the latest version of *.o files"
	echo "make valgrind -> "
	echo "make helgrind -> "
	echo "make clean -> delete *.o files"
	echo "make fclean -> clean + deletes the executable file"
	echo "make re -> fclean + all\n"
