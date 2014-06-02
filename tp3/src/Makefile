all: Matrix.o functions.o data.o main.o
	g++ main.o functions.o Matrix.o data.o -o  yoAtajo -O2

data.o: data.h data.cpp
	g++ -c data.cpp

functions.o: functions.h functions.cpp
	g++ -c functions.cpp

Matrix.o: Matrix.h Matrix.cpp
	g++ -c Matrix.cpp

main.o: main.cpp
	g++ -c main.cpp

clean:
	rm main.o Matrix.o yoAtajo functions.o data.o
