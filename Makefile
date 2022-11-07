GCC := gcc

FLAGS := -pthread -Wall

BUILD := release

build:
	${GCC} ${FLAGS} main.c -o ${BUILD}/fwdport

clean:
	@rm -rf ${BUILD}/*

all: compile
