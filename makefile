#CXX =/usr/local/opt/llvm/bin/clang-3.6
#LD=/usr/local/opt/llvm/bin/lld
#LDFLAGS=-L/usr/local/opt/llvm/lib
#CPPFLAGS=-I/usr/local/opt/llvm/include
CXXFLAGS=-std=c++11 -g -fno-omit-frame-pointer

OBJECTS=Env.o Random.o RandomBot.o Server.o main.o types.o

test: main
	./main

.PHONY: clean
clean:
	rm main $(OBJECTS) *.plist

main:	$(OBJECTS)
	$(CXX) $(CXXFLAGS) -o main $^

Env.o: Env.cpp Env.hpp types.hpp
Random.o: Random.cpp Random.hpp types.hpp Env.hpp
RandomBot.o: RandomBot.cpp RandomBot.hpp types.hpp Env.hpp Random.hpp
Server.o: Server.cpp Server.hpp Env.hpp types.hpp RandomBot.hpp \
Random.hpp
main.o: main.cpp Env.hpp types.hpp RandomBot.hpp Random.hpp Server.hpp
types.o: types.cpp types.hpp
