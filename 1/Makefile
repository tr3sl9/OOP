CFLAGS=-g --std=c++23 -Wall -Wextra -Werror -Wpedantic -Wno-implicit-fallthrough
LDFLAGS=-lreadline
CC=g++

OBJ_CLIENT=obj/client
OBJ_LIB=obj/lib
SRC_CLIENT=src/client
SRC_LIB=src/lib
LIB_TARGET=stringlib.a
TARGET=main

SOURCES_CLIENT=$(wildcard $(SRC_CLIENT)/*.cpp)
OBJECTS_CLIENT=$(patsubst $(SRC_CLIENT)/%.cpp,$(OBJ_CLIENT)/%.o,$(SOURCES_CLIENT))

SOURCES_LIB=$(wildcard $(SRC_LIB)/*.cpp)
OBJECTS_LIB=$(patsubst $(SRC_LIB)/%.cpp,$(OBJ_LIB)/%.o,$(SOURCES_LIB))

$(TARGET): $(OBJECTS_CLIENT) $(LIB_TARGET)
	@mkdir -p $(dir $@)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

$(LIB_TARGET): $(OBJECTS_LIB)
	@mkdir -p $(dir $@)
	ar rcs $@ $^

clean:
	rm -fr obj
	rm -fv $(TARGET)
	rm -fv $(LIB_TARGET)

$(OBJ_CLIENT)/%.o: $(SRC_CLIENT)/%.cpp
	@mkdir -p $(dir $@)
	$(CC) -o $@ -c $< $(CFLAGS)

$(OBJ_LIB)/%.o: $(SRC_LIB)/%.cpp
	@mkdir -p $(dir $@)
	$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clean

