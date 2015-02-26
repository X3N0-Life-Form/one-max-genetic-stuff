CC = gcc
LIBS = -lm
WARNINGS = -Wall
STD = -std=c99

OF_REQ = one-max.o select.o mutation.o cross.o insert.o data.o smart_mutate.o

all: One-Future

run: One-Future
	./One-Future

One-Future: ${OF_REQ}
	gcc ${OF_REQ} -o $@ -lm -g

smart_mutate.o: smart_mutate.c
	gcc $< -c -std=c99 -Wall

one-max.o: one-max.c
	gcc $< -c -std=c99 -Wall

data.o: data.c
	gcc $< -c -std=c99 -Wall

select.o: select.c
	gcc $< -c -std=c99 -Wall

mutation.o: mutation.c
	gcc $< -c -std=c99 -Wall

cross.o: cross.c
	gcc $< -c -std=c99 -Wall

insert.o: insert.c
	gcc $< -c -std=c99 -Wall

clean:
	rm *.o
	rm One-Future