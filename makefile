CXXFLAGS= --std=c++14

OBJECTS= Env.o types.o RandomBot.o Random.o

test: main
	./main

clean:
	rm main $(OBJECTS)

main:	main.cpp $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $< $(OBJECTS)

Env.o: Env.cpp Env.hpp types.hpp
Random.o: Random.cpp Random.hpp types.hpp Env.hpp
RandomBot.o: RandomBot.cpp RandomBot.hpp types.hpp Env.hpp Random.hpp
main.o: main.cpp Env.hpp types.hpp RandomBot.hpp Random.hpp
types.o: types.cpp types.hpp
