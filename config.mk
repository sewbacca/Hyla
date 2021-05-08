
# Project settings

PROJECT := Hyla

# I/O settings

DIR_SRC := src
DIR_TESTS := tests
DIR_BUILD := build
DIR_CACHE := .cache

FILE_MAIN := src/main.cpp

# Compiler settings

# TODO: Make platform independant

CXX := /usr/bin/g++
SHELL := /bin/bash

FLAGS := --std=c++17 -Wall -Wextra -Isrc -lpthread
