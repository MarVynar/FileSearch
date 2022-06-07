

all:	FileSearchLib.a

FileSearchLib.a:	FindFile.o	Params.o	ThreadPool.o
	g++ -o  FileSearchLib.a FindFile.o Params.o ThreadPool.o

ThreadPool.o: ThreadPool.cpp ThreadPool.h mingw.thread.h mingw.mutex.h mingw.condition_variable.h mingw.shared_mutex.h
	g++ -c ThreadPool.cpp

Params.o: Params.cpp Params.h
	g++ -c Params.cpp

FindFile.o: FindFile.cpp FindFile.h
	g++ -c FindFile.cpp