MAKEFLAGS += -j

CC = g++
CFLAGS = -g -Wall -std=c++23 -I/mingw64/include/SDL2 -I./include
LIBS = -L/mingw64/lib -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
SRCDIR = .
OBJDIR = ./obj

SRCS = $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS))

all: $(OBJDIR) game

game: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

clear:
	rm -f game $(OBJS)