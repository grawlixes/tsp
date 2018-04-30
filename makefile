run : tsp
#	./tsp

tsp : main.o State.o Transition.o
	g++ Transition.o State.o main.o -o tsp

main.o : main.cpp
	g++ -c main.cpp

State.o : State.cpp
	g++ -c State.cpp

Transition.o : Transition.cpp
	g++ -c Transition.cpp

clean :
	rm -f tsp *.o
