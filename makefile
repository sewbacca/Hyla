# Starting config

.PHONY: all exec tests

ifndef VERBOSE
.SILENT:
endif

ifndef CONFIG
CONFIG := release
endif

# Project settings

PROJECT_NAME := Hyla

# I/O settings

DIR_SRC := src
DIR_TESTS := tests
DIR_OBJ = cache/obj/$(CONFIG)
DIR_BIN = build/$(CONFIG)
FILE_MAIN := src/main.cpp

DEP_SRC := -lpthread

# Compiler settings

MAKE := /usr/bin/make
CXX := /usr/bin/g++
SHELL := /bin/bash

FLAGS := --std=c++17 -Wall -Wextra -Isrc

ifeq ($(CONFIG), release)
FLAGS += -O3 -D NDEBUG
endif

ifeq ($(CONFIG), debug)
FLAGS += -g
endif

# Resolve files

FILES_SRC = $(filter-out $(FILE_MAIN), $(wildcard $(DIR_SRC)/*.cpp))
FILES_TESTS = $(wildcard $(DIR_TESTS)/*.cpp)

# Rules

all: exec

# Builds executable
exec: $(patsubst %.cpp,$(DIR_OBJ)/%.o,$(FILE_MAIN) $(FILES_SRC))
	mkdir -p $(DIR_BIN)
	echo Linking $(DIR_BIN)/$(PROJECT_NAME)
	$(CXX) -o $(DIR_BIN)/$(PROJECT_NAME) $^ $(DEP_SRC)
	echo Successfully built executable

# Builds tests
tests: tests/catch.hpp $(patsubst %.cpp,$(DIR_OBJ)/%.o,$(FILES_TESTS) $(FILES_SRC))
	mkdir -p $(DIR_BIN)
	echo Linking $(DIR_BIN)/tests
	$(CXX) -o $(DIR_BIN)/tests $^ $(DEP_SRC)
	echo Successfully built tests

$(DIR_OBJ)/%.o: %.cpp
	mkdir -p $(dir $@)
	echo Compiling $<...
	$(CXX) $(FLAGS) -c -o $@ $<

clean: clean-cache clean-build

clean-cache:
	rm -rvf $(DIR_OBJ)

clean-build:
	rm -rvf $(DIR_BIN)

# Catch dependency

tests/catch.hpp:
	wget -O $@ -q --show-progress https://github.com/catchorg/Catch2/releases/download/v2.13.6/catch.hpp