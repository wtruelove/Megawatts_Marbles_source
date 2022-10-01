#
#	Makefile for Megawatts & Marbles - The Energy Planning Game
#
#	[ESC] Interactive
#
#	Anthony Truelove MASc, P.Eng.
#	Spencer Funk BEng, EIT
#
#	Copyright 2022 (C) - [ESC] Interactive
#	See license terms for details
#


# -------- Compiler Variables -------- #

CC = g++
CFLAGS = -std=c++17 -O1
SFML = -lsfml-graphics\
	   -lsfml-audio\
	   -lsfml-network\
	   -lsfml-window\
	   -lsfml-system


STATIC = -static -static-libgcc -static-libstdc++

# "If X depends on Y, then X is linked before Y"
SFML_STATIC = -DSFML_STATIC\
			  -lsfml-main\
		      -lsfml-graphics-s\
			  -lsfml-audio-s\
			  -lsfml-network-s\
			  -lsfml-window-s\
			  -lsfml-system-s\
			  -lopengl32\
			  -lopenal32\
			  -lfreetype\
			  -lwinmm\
			  -lgdi32\
			  -lFLAC\
			  -lvorbisenc\
			  -lvorbisfile\
			  -lvorbis\
			  -logg\
			  -lws2_32\
			  -ljpeg\
			  -lpthread

# SFML libs:
#
#	apt search sfml -->		libsfml-dev
#
#	sfml-audio 		-->		-lsfml-audio
#	sfml-graphics	-->		-lsfml-graphics
#	sfml-network	-->		-lsfml-network
#	sfml-system		-->		-lsfml-system
#	sfml-window 	-->		-lsfml-window

#THIRD_PARTY =


# -------- build instructions -------- #

# ---- executable ---- #
OUT_RUN = bin/run.out
OBJ_MAIN = object/main.o
SRC_MAIN = source/main.cpp

.PHONY: main
main: $(OBJ_MAIN)
	$(CC) $(CFLAGS) $(OBJ_ESC) $(OBJ_MM) $(OBJ_MAIN) -o $(OUT_RUN) $(SFML)

$(OBJ_MAIN): $(SRC_MAIN)
	$(CC) $(CFLAGS) -c $(SRC_MAIN) -o $(OBJ_MAIN) $(SFML)


SRC_ALL = source/ESC.cpp source/MM.cpp source/main.cpp

.PHONY: main-s
main-s:
	$(CC) $(CFLAGS) $(SRC_ALL) -o $(OUT_RUN) $(SFML_STATIC) $(STATIC)


# ---- Megawatts & Marbles ---- #
OBJ_MM = object/MM.o
SRC_MM = source/MM.cpp

.PHONY: MM
MM: $(SRC_MM)
	$(CC) $(CFLAGS) -c $(SRC_MM) -o $(OBJ_MM) $(SFML)


# ---- [ESC] Interactive ---- #
OBJ_ESC = object/ESC.o
SRC_ESC = source/ESC.cpp

.PHONY: ESC
ESC: $(SRC_ESC)
	$(CC) $(CFLAGS) -c $(SRC_ESC) -o $(OBJ_ESC) $(SFML)


# -------- targets -------- #

.PHONY: all
all:
	mkdir -pv bin
	mkdir -pv core
	mkdir -pv object
	make ESC MM main


.PHONY: all-s
all-s:
	mkdir -pv bin
	mkdir -pv core
	mkdir -pv object
	make main-s


.PHONY: run
run:
	$(OUT_RUN)


.PHONY: run_test
run_test:
	$(OUT_RUN) --test


.PHONY: clean
clean:
	rm -frv bin
	rm -frv core
	rm -frv object
