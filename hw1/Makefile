CC = gcc
all : hw1_naive hw1_kmp
CFLAGS = -W -Wall

hw1_naive : hw1_naive.c
	$(CC) $(CFLAGS) -o $@ $<
hw1_kmp : hw1_kmp.c
	$(CC) $(CFLAGS) -o $@ $<

clean :
	rm *.o hw1_naive hw1_kmp
