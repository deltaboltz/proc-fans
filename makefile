C = gcc
CFLAGS = -I. -g -Wall
EXEC = runsim
OBJS = runsim.o

DEPS=
%.o: %.c $(DEPS)
        $(CC) -c -o $@ $< $(CFLAGS)

runsim: $(OBJS)
        g++ -c main.cpp

testsim: testsim.c
        $(CC) -o testsim testsim.c

all:
        runsim testsim


clean:
        rm $(EXEC) $(OBJS) testsim testsim.o
