%.o: %.c
	gcc -g -c -o $@ $<

debug:	cpu_main.o	my_cpu.o
	gcc -Wall -Werror -g -o my_cpud my_cpu.o cpu_main.o

final:	cpu_main.c	my_cpu.c
	gcc -o my_cpu my_cpu.c cpu_main.c

static64:	cpu_main.c	my_cpu.c
	gcc -m64 -static -o my_cpu64 my_cpu.c cpu_main.c

clean:
	rm -f *.o
