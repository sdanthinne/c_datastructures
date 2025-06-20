
CC:=clang
CFLAGS:= -I.

ODIR := build
SOURCES := $(shell find . -name "*.c")
ASM_SOURCES := $(shell find . -name "*.S")
INCLUDES := $(shell find . -name "*.h")


OBJS := $(patsubst %.c,%.o,$(SOURCES)) $(patsubst %.S,%.o,$(ASM_SOURCES))

all: run

run: $(subst ./, $(ODIR)/,$(OBJS))
	$(CC) $(CFLAGS) -o $(ODIR)/$@ $^
	./$(ODIR)/$@

$(ODIR)/%.o: %.S
	$(CC) $(CFLAGS) -c -o $@ $<

$(ODIR)/%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<
clean:
	rm -r $(ODIR)/*
