#
# Copyright (c) 2021 jdeokkim
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#

.PHONY: all clean

PROJECT_NAME := c-krit/kbfe
PROJECT_PATH := kbfe
PROJECT_PREFIX := $(shell tput setaf 2)$(PROJECT_NAME):$(shell tput sgr0)

RAYLIB_PATH ?= ../raylib

BINARY_PATH := $(PROJECT_PATH)/bin
SOURCE_PATH := $(PROJECT_PATH)/src
    
SOURCES := $(SOURCE_PATH)/main.c

OBJECTS := $(SOURCES:.c=.o)
TARGETS := $(BINARY_PATH)/kbfe

HOST_OS := LINUX
TARGET_OS := $(HOST_OS)

ifeq ($(OS),Windows_NT)
	PROJECT_PREFIX := $(PROJECT_NAME):
	HOST_OS := WINDOWS
else
	UNAME = $(shell uname)
	ifeq ($(UNAME),Linux)
		HOST_OS = LINUX
	endif
endif

CC := gcc
CFLAGS := -D_DEFAULT_SOURCE -g -std=gnu99 -O2
LDFLAGS := -no-pie
LDLIBS := -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

ifeq ($(TARGET_OS),WINDOWS)
	TARGETS := $(BINARY_PATH)/kbfe.exe
	CC := x86_64-w64-mingw32-gcc
	CFLAGS += -I$(RAYLIB_PATH)/src
	LDFLAGS += -L$(RAYLIB_PATH)/src
	LDLIBS := -lraylib -lopengl32 -lgdi32 -lwinmm -lpthread
endif

all: pre-build build post-build

pre-build:
	@echo "$(PROJECT_PREFIX) Using: '$(CC)' to build this project."
    
build: $(TARGETS)

$(SOURCE_PATH)/%.o: $(SOURCE_PATH)/%.c
	@echo "$(PROJECT_PREFIX) Compiling: $@ (from $<)"
	@$(CC) -c $< -o $@ $(CFLAGS) $(LDFLAGS) $(LDLIBS)
    
$(TARGETS): $(OBJECTS)
	@mkdir -p $(BINARY_PATH)
	@echo "$(PROJECT_PREFIX) Linking: $(TARGETS)"
	@$(CC) $(OBJECTS) -o $(TARGETS) $(CFLAGS) $(LDFLAGS) $(LDLIBS)
    
post-build:
	@echo "$(PROJECT_PREFIX) Build complete."

clean:
	@echo "$(PROJECT_PREFIX) Cleaning up."
	@rm -rf $(BINARY_PATH)/*
	@rm -rf $(SOURCE_PATH)/*.o