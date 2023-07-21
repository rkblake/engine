CC=g++
CPPFLAGS+=-g -Wall -std=c++17
LDFLAGS:=-L/usr/local/lib -lraylib -llua
INCLUDE_PATHS:=-I/usr/local/include -I./vendor/
TARGET=engine

OBJ:=$(patsubst %.cpp,%.o,$(wildcard src/*.cpp) $(wildcard src/**/*.cpp))

$(TARGET): bin $(OBJ)
	$(CC) $(OBJ) -o bin/$@ $(LDFLAGS) $(INCLUDE_PATHS)
	
bin:
	mkdir -p $@
obj:
	mkdir -p $@
run:
	bin/$(TARGET)

.PHONY: clean
clean:
	$(RM) $(OBJ)
	$(RM) bin/$(TARGET)
