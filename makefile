CXXFLAGS += -std=c++14

ifeq ($(FAST), 1)
  CXXFLAGS += -O2
else
  CXXFLAGS += -g -fno-omit-frame-pointer
endif

OBJECTS = PublicInfo.o Round.o Random.o RandomBot.o Server.o types.o

main:	main.cc $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@

.PHONY: clean
clean:
	rm -f *.o
	rm -f main
	rm -rf main.dSYM/

.PHONY: run
run: main
	./main

PublicInfo.o: PublicInfo.cc PublicInfo.h types.h
Random.o: Random.cc Random.h types.h PublicInfo.h
RandomBot.o: RandomBot.cc RandomBot.h Bot.h types.h Round.h PublicInfo.h \
Random.h
Round.o: Round.cc Round.h types.h PublicInfo.h
Server.o: Server.cc Server.h Round.h types.h PublicInfo.h RandomBot.h \
Bot.h Random.h
main.o: main.cc Round.h types.h PublicInfo.h RandomBot.h Bot.h Random.h \
Server.h
types.o: types.cc types.h
