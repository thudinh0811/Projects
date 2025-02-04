CC:=emcc
INCLUDES:=-I../include
CFLAGS:=-std=gnu17 -pedantic -Wall
LFLAGS:=-lm -lGL -sUSE_GLFW=3 -sUSE_WEBGL2 -sFULL_ES3 -sMIN_WEBGL_VERSION=2 -sENVIRONMENT=web --js-library=mylib.js

SRCDIR:=../src
OBJDIR:=./obj
TARGET:=App.html

SRCFILES:=$(wildcard $(SRCDIR)/*.c)
HEADERFILES:=$(wildcard $(SRCDIR)/*.h)
OBJFILES:=$(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.c.o, $(SRCFILES))

all: $(TARGET)

clean:
	rm $(OBJDIR)/*.o

$(OBJDIR):
	mkdir ./obj

$(OBJDIR)/%.c.o: $(SRCDIR)/%.c Makefile $(HEADERFILES) $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

$(TARGET): $(OBJDIR) $(OBJFILES) $(SRCFILES) Makefile
	$(CC) $(OBJFILES) -o $@ $(LFLAGS) --preload-file ./assets
