all: Matrix.o functions.o  main.o
	g++ main.o functions.o Matrix.o -o  caritas -O2

functions.o: functions.h functions.cpp 
	g++ -c functions.cpp

Matrix.o: Matrix.h Matrix.cpp 
	g++ -c Matrix.cpp  

main.o: main.cpp
	g++ -c main.cpp      

clean:
	rm main.o Matrix.o caritas functions.o
