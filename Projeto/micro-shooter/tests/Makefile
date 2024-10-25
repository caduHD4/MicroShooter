CC = g++
CFLAGS = -g -Wall -std=c++23 -I../include -I/mingw64/include/SDL2
LIBS = -L/mingw64/lib -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
SRCDIR = .
OBJDIR = ./obj

SRCS = test.cpp ../player.cpp ../graphic-implement-sdl.cpp ../sprite.cpp ../status-bar.cpp ../bullet.cpp ../enemy.cpp
OBJS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS))

all: $(OBJDIR) test

test: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

clear:
	rm -f test $(OBJS)