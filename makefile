CXXFLAGS += -std=c++14 -g -fno-omit-frame-pointer

OBJECTS = PublicInfo.o Round.o Random.o RandomBot.o Server.o types.o

test: main
	./main

.PHONY clean:
	rm -f *.o
	rm -f main
	rm -rf main.dSYM/

main:	main.cc $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@

PublicInfo.o: PublicInfo.cc PublicInfo.h types.h
Random.o: random.cc Random.h types.h PublicInfo.h
RandomBot.o: RandomBot.cc RandomBot.h types.h Round.h PublicInfo.h \
Random.h
Round.o: Round.cc Round.h types.h PublicInfo.h
Server.o: Server.cc Server.h Round.h types.h PublicInfo.h RandomBot.h \
Random.h
types.o: types.cc types.h
