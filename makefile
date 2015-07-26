CXXFLAGS= --std=c++14

OBJECTS= Env.o types.o RandomBot.o util.o

test: main
	./main

clean:
	rm main $(OBJECTS)

main:	main.cpp $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $< $(OBJECTS)

Env.o: Env.cpp types.hpp Env.hpp
RandomBot.o: RandomBot.cpp RandomBot.hpp types.hpp Env.hpp util.hpp
main.o: main.cpp Env.hpp types.hpp RandomBot.hpp
types.o: types.cpp types.hpp
util.o: util.cpp util.hpp types.hpp Env.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<
