TARGET = statango
LIBS = -lm  -D PLATFORM_LINUX
CC = gcc
CFLAGS = -g -Wall
OUTDIR = compiled

.PHONY: prepare default all clean

default: $(TARGET)
all: default

prepare:
	-mkdir -p $(OUTDIR)

# OBJECTS = $(patsubst %.c, %.o, $(wildcard src/*.c))
OBJECTS = src/main.c
HEADERS = $(wildcard *.h)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $(OUTDIR)/$@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): prepare $(OBJECTS)
	$(CC) $(OBJECTS) -Wall $(LIBS) -o $(OUTDIR)/$@

clean:
	-rm -f $(OUTDIR)/*.o
	-rm -f $(OUTDIR)/$(TARGET)

