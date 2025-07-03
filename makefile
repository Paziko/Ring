SHELL := /bin/sh
CC := g++



all: test.cpp ring.h
	$(CC) test.cpp -o test_app;



.PHONY: clean

clean:
	rm -i -f test_app;