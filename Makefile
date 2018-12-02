fonbook: fonbook.o functions.o 
	g++ fonbook.o functions.o -o fonbook
book.o: fonbook.cpp
	g++ -c fonbook.cpp
functions.o: functions.cpp functions.h
	g++ -c functions.cpp
clean:
	rm *.o fonbook

