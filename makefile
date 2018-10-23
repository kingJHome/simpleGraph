files = main.c graph.c

main: $(files)
	gcc -o $@ $^

maintest: $(files)
	gcc -g $^ -o $@
