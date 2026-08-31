BUILD_DIR := build

ifeq ($(OS),Windows_NT)
  EXE := $(BUILD_DIR)/snake.exe
else
  EXE := $(BUILD_DIR)/snake
endif

.PHONY: all build run clean

all: build

build:
	cmake -S . -B $(BUILD_DIR)
	cmake --build $(BUILD_DIR)

run: build
	$(EXE)

clean:
	cmake -E rm -rf $(BUILD_DIR)
