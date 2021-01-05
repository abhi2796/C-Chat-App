CC=g++
EXEC_BINARY = Client Server
CFLAGS=-I../include 
LIBS = -lpthread

all: $(EXEC_BINARY)

$(EXEC_BINARY): %: %.cpp
	$(CC) $(CFLAGS) -o $@ $< $(LIBS)
