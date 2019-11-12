# -*- Makefile -*-

#Declare the variables
CC=g++

CFLAGS=-g -c
MOREFLAGS=-fmessage-length=0 -std=c++17
OPTIFLAGS=-O3 -ffast-math -fopenmp -march=native

DIR_INCL=-I/usr/include -I/usr/local/include -I/usr/lib/gcc/arm-linux-gnueabihf/6/include -I/usr/lib/gcc/arm-linux-gnueabihf/6/include

DIR_LIBS=-L/usr/local/lib
SRC_DIR=./src/
BIN_DIR=./bin/
LIBS=-lm -lstdc++ -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_ml -lopencv_imgcodecs -lboost_system -lboost_filesystem
OBJS= \
 $(BIN_DIR)jproc/basicproc.o \
 $(BIN_DIR)jproc/gridproc.o \
 $(BIN_DIR)jproc/wallproc.o \
 $(BIN_DIR)jproc/procfactory.o \
 $(BIN_DIR)jproc/jproc.o \
 $(BIN_DIR)preproc/preproc.o \
 $(BIN_DIR)main.o \
 

apc: directories $(OBJS)
	$(CC) $(DIR_INCL) $(DIR_LIBS) $(MOREFLAGS) $(OPTIFLAGS) -o ./imgtails $(OBJS) $(LIBS)

directories:
	mkdir -p \
	        $(BIN_DIR)jproc \
	        $(BIN_DIR)preproc


$(BIN_DIR)jproc/basicproc.o: $(SRC_DIR)jproc/basicproc.h $(SRC_DIR)jproc/basicproc.cpp
	$(CC) $(CFLAGS) $(MOREFLAGS) $(OPTIFLAGS) -o $(BIN_DIR)jproc/basicproc.o $(SRC_DIR)jproc/basicproc.cpp

$(BIN_DIR)jproc/gridproc.o: $(SRC_DIR)jproc/gridproc.cpp $(SRC_DIR)jproc/gridproc.h
	$(CC) $(CFLAGS) $(MOREFLAGS) $(OPTIFLAGS) -o $(BIN_DIR)jproc/gridproc.o $(SRC_DIR)jproc/gridproc.cpp

$(BIN_DIR)jproc/wallproc.o: $(SRC_DIR)jproc/wallproc.cpp $(SRC_DIR)jproc/wallproc.h
	$(CC) $(CFLAGS) $(MOREFLAGS) $(OPTIFLAGS) -o $(BIN_DIR)jproc/wallproc.o $(SRC_DIR)jproc/wallproc.cpp

$(BIN_DIR)jproc/procfactory.o: $(SRC_DIR)jproc/procfactory.cpp $(SRC_DIR)jproc/procfactory.h
	$(CC) $(CFLAGS) $(MOREFLAGS) $(OPTIFLAGS) -o $(BIN_DIR)jproc/procfactory.o $(SRC_DIR)jproc/procfactory.cpp

$(BIN_DIR)jproc/jproc.o: $(SRC_DIR)jproc/jproc.cpp $(SRC_DIR)jproc/jproc.h
	$(CC) $(CFLAGS) $(MOREFLAGS) $(OPTIFLAGS) -o $(BIN_DIR)jproc/jproc.o $(SRC_DIR)jproc/jproc.cpp

$(BIN_DIR)preproc/preproc.o: $(SRC_DIR)preproc/preproc.cpp $(SRC_DIR)preproc/preproc.h
	$(CC) $(CFLAGS) $(MOREFLAGS) $(OPTIFLAGS) -o $(BIN_DIR)preproc/preproc.o $(SRC_DIR)preproc/preproc.cpp

$(BIN_DIR)main.o: $(SRC_DIR)main.cpp
	$(CC) $(CFLAGS) $(MOREFLAGS) $(OPTIFLAGS) -o $(BIN_DIR)main.o $(SRC_DIR)main.cpp

clean:
	rm -f $(BIN_DIR)*.o
	rm -f $(BIN_DIR)jproc/*.o
	
