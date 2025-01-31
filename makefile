prog: main.o functions.o
	g++ -g main.o functions.o -o PA1

main.o: main.cpp 
	g++ -c -g -Wall -std=c++11  main.cpp 

functions.o: functions.cpp 
	g++ -c -g -Wall -std=c++11 functions.cpp 


clean: 
	-rm -f *.o PA1

run:
	@./PA1