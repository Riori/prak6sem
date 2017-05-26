stribog: libstribog.a main.cpp
	g++ -std=c++11 -lstribog main.cpp -o stribog
libstribog.a: stribog.cpp const.h stribog.h types.h
	g++ -std=c++11 stribog.cpp -c -o stribog.o
	ar rc libstribog.a stribog.o
	rm stribog.o