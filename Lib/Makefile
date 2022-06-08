<<<<<<< Updated upstream
=======
DESTDIR=../../
PREFIX=../

STATIC=FileSearchLib.a

CC = g++
CFLAGS = -Wall -Winline -pipe

LDFLAGS = -L../../../lib
LIBS	 = -lpthread 

SRC = ThreadPool.cpp Params.cpp FindFile.cpp
>>>>>>> Stashed changes


all:	FileSearchLib.a

FileSearchLib.a:	FindFile.o	Params.o	ThreadPool.o
	g++ -o  FileSearchLib.a FindFile.o Params.o ThreadPool.o

<<<<<<< Updated upstream
ThreadPool.o: ThreadPool.cpp ThreadPool.h mingw.thread.h mingw.mutex.h mingw.condition_variable.h mingw.shared_mutex.h
	g++ -c ThreadPool.cpp
=======
>>>>>>> Stashed changes

Params.o: Params.cpp Params.h
	g++ -c Params.cpp

FindFile.o: FindFile.cpp FindFile.h
	g++ -c FindFile.cpp