

STATIC=libFileSearchLib.a

.PHONY: all
all: $(STATIC)


$(STATIC): FindFile.o ThreadPool.o Params.o
  ar ru $@ $^
	ranlib $@

FindFile.o: FindFile.cpp FindFile.h
	g++ -c FindFile.cpp

ThreadPool.o: ThreadPool.cpp ThreadPool.h
	g++ -c ThreadPool.cpp



Params.o: Params.cpp Params.h
	g++ -c Params.cpp



