CC = g++
FLAGS = -std=c++11 -O3 -Wextra -Wall

nbc : main.o fit.o predict.o base.o
	$(CC) $(FLAGS) -o nbc main.o fit.o predict.o base.o
	rm *.o
main.o : main.cpp base.h fit.h predict.h
	$(CC) $(FLAGS) -c main.cpp
fit.o : fit.cpp base.h
	$(CC) $(FLAGS) -c fit.cpp
predict.o : predict.cpp base.h
	$(CC) $(FLAGS) -c predict.cpp
base.o : base.cpp
	$(CC) $(FLAGS) -c base.cpp
clear :
	rm *.o nbc