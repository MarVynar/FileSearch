all:	FileSearchLib.a

FileSearchLib.a:	FindFile.o	Params.o	ThreadPool.o
	g++ -o  FileSearchLib.a FindFile.o Params.o ThreadPool.o

ThreadPool.o: ThreadPool.cpp ThreadPool.h
	g++ -c ThreadPool.cpp

Params.o: Params.cpp Params.h
	g++ -c Params.cpp

FindFile.o: FindFile.cpp FindFile.h
	g++ -c FindFile.cpp