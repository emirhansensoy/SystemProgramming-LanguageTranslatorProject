CC = gcc
CFLAGS = -O3 -Iinclude

all: lib/libfdr.a compile

OBJS = obj/dllist.o obj/fields.o obj/jval.o obj/jrb.o obj/program.o

lib/libfdr.a: $(OBJS)
	ar ru lib/libfdr.a $(OBJS)
	ranlib lib/libfdr.a 

clean:
	rm -f obj/* lib/*

compile: $(OBJS)
	$(CC) -o ./bin/ceviri $(OBJS)

obj/fields.o: src/fields.c include/fields.h
	$(CC) $(CFLAGS) -c -o obj/fields.o src/fields.c

obj/jval.o: src/jval.c include/jval.h
	$(CC) $(CFLAGS) -c -o obj/jval.o src/jval.c

obj/dllist.o: src/dllist.c include/dllist.h include/jval.h
	$(CC) $(CFLAGS) -c -o obj/dllist.o src/dllist.c

obj/jrb.o: src/jrb.c include/jrb.h include/jval.h
	$(CC) $(CFLAGS) -c -o obj/jrb.o src/jrb.c
	
obj/program.o: src/program.c include/fields.h
	$(CC) $(CFLAGS) -c -o obj/program.o src/program.c
