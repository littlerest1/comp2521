# Makefile for COMP1917 15s2 Week 08 Lab

CC=gcc 
CFLAGS=-Wall -g -std=c11
LIBS= graph.o 
TESTS=ts tq tk tg

pageRank : pageRank.o $(LIBS)
	gcc -g -o pageRank pageRank.o $(LIBS) -lcurl

tests : $(TESTS)


graph.o : graph.c graph.h

tg : tg.o graph.o
	gcc -o tg tg.o graph.o
tg.o : tg.c graph.h

clean :
	rm -f pageRank $(TESTS) *.o core
