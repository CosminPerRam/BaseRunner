CXX		  := g++
CXX_FLAGS := -Wno-unused-variable -Wno-narrowing -Wshadow -std=c++17 -ggdb

BIN		:= bin
SRC		:= src
INCLUDE	:= include
LIB		:= lib

LIBRARIES	:= -lsfml-system -lsfml-graphics -lsfml-window -lsfml-network -lsfml-audio -openal32
EXECUTABLE	:= main

all: $(BIN)/$(EXECUTABLE)

run: clean all
	clear
	./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(SRC)/*.cpp
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) -L$(LIB) $^ $(LIBRARIES) -o $@

clean:
	-rm $(BIN)/*
