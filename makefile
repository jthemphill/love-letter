CXXFLAGS += -std=c++14

ifeq ($(FAST), 1)
  CXXFLAGS += -O2
else
  CXXFLAGS += -g -fno-omit-frame-pointer
endif

OBJECTS = PublicInfo.o Round.o Random.o GreedyBot.o RandomBot.o Server.o types.o

main:	main.cc $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@

.PHONY: clean
clean:
	rm -f *.o
	rm -f main

.PHONY: run
run: main
	./main

GreedyBot.o: GreedyBot.cc GreedyBot.h Bot.h events.h types.h Random.h \
PublicInfo.h
PublicInfo.o: PublicInfo.cc PublicInfo.h events.h types.h
Random.o: Random.cc Random.h types.h PublicInfo.h events.h
RandomBot.o: RandomBot.cc RandomBot.h Bot.h events.h types.h Round.h \
PublicInfo.h Random.h
Round.o: Round.cc Round.h types.h PublicInfo.h events.h
Server.o: Server.cc Server.h Round.h types.h PublicInfo.h events.h Bot.h \
GreedyBot.h Random.h RandomBot.h
main.o: main.cc Round.h types.h PublicInfo.h events.h RandomBot.h Bot.h \
Random.h Server.h
types.o: types.cc types.h
