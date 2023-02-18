debug:
	gcc -g -Wall -Wextra -o main main.c myalloc.c

clean:
	rm -f $(TARGETS)

main: main.c myalloc.c
	gcc -g -Wall -Wextra -o main main.c myalloc.c