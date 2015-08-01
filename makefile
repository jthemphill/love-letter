CXXFLAGS += -std=c++14 -Wall

ifeq ($(FAST), 1)
  CXXFLAGS += -O2
else
  CXXFLAGS += -g -fno-omit-frame-pointer
endif

OBJECTS = PublicInfo.o Round.o Random.o GreedyBot.o RandomBot.o Server.o \
choice.o GuardBot.o

main:	main.cc $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@

.PHONY: clean
clean:
	rm -f *.o
	rm -f main
	rm -rf main.DSYM

.PHONY: run
run: main
	./main

GreedyBot.o: GreedyBot.cc GreedyBot.h Bot.h events.h actions.h const.h \
Random.h PublicInfo.h choice.h
GuardBot.o: GuardBot.cc GuardBot.h Bot.h events.h actions.h const.h \
Random.h PublicInfo.h choice.h
PublicInfo.o: PublicInfo.cc PublicInfo.h choice.h const.h actions.h \
events.h
Random.o: Random.cc Random.h const.h PublicInfo.h choice.h actions.h \
events.h
RandomBot.o: RandomBot.cc RandomBot.h Bot.h events.h actions.h const.h \
Round.h PublicInfo.h choice.h Random.h
Round.o: Round.cc Round.h const.h PublicInfo.h choice.h actions.h \
events.h
Server.o: Server.cc Server.h Round.h const.h PublicInfo.h choice.h \
actions.h events.h Bot.h GreedyBot.h Random.h RandomBot.h
choice.o: choice.cc choice.h const.h actions.h
main.o: main.cc Round.h const.h PublicInfo.h choice.h actions.h events.h \
RandomBot.h Bot.h Random.h Server.h
