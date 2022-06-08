<<<<<<< Updated upstream
all:	FileSearchLib.a
=======
DESTDIR=../../
PREFIX=../

STATIC=FileSearchLib.a

CC = g++
CFLAGS = -Wall -Winline -pipe
>>>>>>> Stashed changes

LDFLAGS = -L../../../lib
LIBS	 = -lpthread 

SRC = ThreadPool.cpp Params.cpp FindFile.cpp

OBJ = $(SRC:.c=.o)

$(STATIC): $(OBJ)
	@echo "[Link (Static)]"
	@ar rcs $@ $^

.c.o:
	@echo [Compile] $<
	@$(CC) -c $(CFLAGS) $< -o $@


.PHONY: install
install: $(STATIC)
	@install -m 0755 $< $(DESTDIR)$(PREFIX)/lib

all: install
	$(CC) -g -Wall -o program main.cpp $(LDFLAGS) $(LIBS)

<<<<<<< Updated upstream
ThreadPool.o: ThreadPool.cpp ThreadPool.h
	g++ -c ThreadPool.cpp
=======
>>>>>>> Stashed changes


