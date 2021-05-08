# Starting config

.PHONY: all exec tests build-info clean
.SILENT:

ifndef CONFIG
CONFIG := release
endif

# Load config file

include config.mk

# Platform and config specific stuff

ifeq ($(CONFIG), release)
FLAGS += -O3 -D NDEBUG
FILE_TAG :=
else ifeq ($(CONFIG), debug)
FLAGS += -g
FILE_TAG := -dbg
else
$(error Bad $$(CONFIG) := $(CONFIG), must be release/debug)
endif

ifeq ($(OS), Windows_NT)
EXT := .exe
PLATFORM := Windows
else
EXT := .out
PLATFORM := Unix
endif

# Resolving variables

DIR_OBJ := $(DIR_CACHE)/$(CONFIG)/obj
DIR_DEP := $(DIR_CACHE)/$(CONFIG)/d

FILE_OUT := $(DIR_BUILD)/$(PROJECT)$(FILE_TAG)$(EXT)
FILE_TESTS_OUT := $(DIR_BUILD)/$(PROJECT)-tests$(FILE_TAG)$(EXT)

FILE_MAIN_OBJ := $(FILE_MAIN:%.cpp=$(DIR_OBJ)/%.o)

FILES_SRC := $(filter-out $(FILE_MAIN), $(shell find $(DIR_SRC) -name '*.cpp'))
FILES_TESTS := $(shell find $(DIR_TESTS) -name '*.cpp' 2> /dev/null)

FILES_OBJ := $(patsubst %.cpp, $(DIR_OBJ)/%.o, $(FILES_SRC))
FILES_TESTS_OBJ := $(patsubst %.cpp, $(DIR_OBJ)/%.o, $(FILES_TESTS))
FILES_H := $(patsubst %.cpp, $(DIR_DEP)/%.d, $(FILES_SRC))

# Targets

default: exec

build-info:
	echo "Project settings:"
	echo "    Project:  $(PROJECT)"
	echo "    Compiler: $(CXX)"
	echo "    Platform: $(PLATFORM)"
	echo "    Config:   $(CONFIG)"
	echo "    Flags:    \"$(FLAGS)\"";

help:
	echo "Variables:"
	echo "    CONFIG: release/debug"
	echo "Targets"
	echo "    default: exec   -- Default target"
	echo "    build-info      -- Prints build info"
	echo "    exec            -- Builds executable"
	echo "    tests           -- Builds tests"
	echo "    clean           -- Cleans cache";

exec: $(FILE_MAIN_OBJ) $(FILES_OBJ)
	echo Linking $(FILE_OUT)
	mkdir -p $(dir $(FILE_OUT))
	$(CXX) -o $(FILE_OUT) $^ $(FLAGS)
	echo Successfully built executable!

tests: tests/catch.hpp $(FILES_OBJ) $(FILES_TESTS_OBJ)
	echo Linking $(FILE_TESTS_OUT)
	mkdir -p $(dir $(FILE_TESTS_OUT))
	$(CXX) -o $(FILE_TESTS_OUT) $^ $(FLAGS)
	echo Successfully built tests!

clean:
	rm -rvf $(DIR_CACHE)

# Build rules

$(DIR_DEP)/%.d: %.cpp
	echo Creating dependency graph for $^
	mkdir -p $(dir $@)
	$(CXX) -M $(FLAGS) $^ -o $@

ifeq ($(MAKECMDGOALS), clean)
else ifeq ($(MAKECMDGOALS), build-info)
else
-include $(FILES_H)
endif

$(DIR_OBJ)/%.o: %.cpp
	echo Compiling $<...
	mkdir -p $(dir $@)
	$(CXX) $(FLAGS) -c -o $@ $<

# Catch dependency download

tests/catch.hpp:
	wget -O $@ -q --show-progress https://github.com/catchorg/Catch2/releases/download/v2.13.6/catch.hpp
