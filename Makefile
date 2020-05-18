SHELL = /bin/bash

current = viewport

run:
	cd $(current) && ./main.out

build: $(current).out

.SECONDEXPANSION:
%.out: $$*/main.cpp
	g++ -Wall -Werror -Wconversion -Wno-unused-variable -Wno-write-strings -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer $^ -o $*/main.out

%.run:
	cd $* && ./main.out

