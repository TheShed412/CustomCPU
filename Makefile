%.o: %.c
	gcc -g -c -o $@ $<

debug:	my_cpu.o
	gcc -Wall -Werror -g -o my_cpud my_cpu.o

final:	my_cpu.c
	gcc -o my_cpu my_cpu.c

static32:	my_cpu.c
	gcc -m32 -static -o my_cpu32 my_cpu.c

static64:	my_cpu.c
	gcc -m64 -static -o my_cpu64 my_cpu.c

clean:
	rm -f *.o
