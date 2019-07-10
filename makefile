prog: main.o mats.o inout.o
		gcc -Wall -std=c11 -o mat main.o mats.o inout.o -lm

main.o: main.c
		gcc -Wall -std=c11 -c main.c -lm

mats.o: mats.c
		gcc -Wall -std=c11 -c mats.c -lm

inout.o: inout.c
		gcc -Wall -std=c11 -c inout.c -lm