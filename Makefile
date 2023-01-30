CFLAGS = -g -Wall -Wextra -pedantic
CC = /usr/bin/gcc

PROGRAMS =   tests_ecosys ecosys

.PHONY:	all clean

all: $(PROGRAMS)

tests_ecosys: ecosys.o main_tests.o
	$(CC) -o $@ $(CFLAGS) $^


ecosys: ecosys.o main_ecosys.o
	$(CC) -o $@ $(CFLAGS) $^

#Ou plus simplement
#%.o:%.c %.h
#	$(CC)  $(GCC_FLAGS) -c  $<


clean:
	rm -f *.o *~ $(PROGRAMS)
