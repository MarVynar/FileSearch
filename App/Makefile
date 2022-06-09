all: FileSearch.exe

FileSearch.exe: main.cpp FindFile.h libFileSearch.a
	 g++ -I ../inc -L . -static main.cpp -lFileSearch -static