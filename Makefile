.PHONY: touchfiles run clean

touchfiles:
	gcc main.c -o touchfiles -Wall -Werror

run: touchfiles
	./touchfiles 30000000 ./testdir

clean:
	rm touchfiles
