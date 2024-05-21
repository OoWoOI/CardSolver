
.PHONY: clean

all: main.cpp src/pai.cc ./src/tree.cc 
	g++ -std=c++11 main.cpp ./src/pai.cc ./src/tree.cc -o ./bin/CardSolove -I./include

run: clean all
	./bin/CardSolove
clean:
	rm ./bin/CardSolove

