build: main.o instructions.o queue.o
	gcc main.o instructions.o instructions.h queue.h queue.o -o register-sim
main.o: main.c
	gcc -Wall -c  main.c -o main.o
instructions.o: instructions.c
	gcc -Wall -c instructions.c -o instructions.o
queue.o: queue.c
	gcc -Wall -c queue.c -o queue.o
run: register-sim
	./register-sim
clean:
	rm *.o register-sim
