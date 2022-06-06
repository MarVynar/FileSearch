LDFLAGS= /lib
LDLIBS = FileSearchLib.a

all: FileSearchApp.exe

FileSearchApp.exe: main.o 
	g++ -o FileSearchApp.exe main.o 

main.o: main.cpp FindFile.h
	g++ -c  main.cpp

