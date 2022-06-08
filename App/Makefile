

all: FileSearchApp.exe

FileSearchApp.exe: main.o FileSearchLib.a
	g++ -o FileSearchApp.exe main.o -L -lFileSearchLib.a

main.o: main.cpp FindFile.h
	g++ -c  main.cpp

