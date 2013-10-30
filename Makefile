a.out: linked_sequence.hpp array_sequence.hpp main.cpp
	g++ -Wall -Wextra -pedantic -O0 -g3 main.cpp
#	g++ -w -O0 -g3 main.cpp

clean:
	rm -f a.out
