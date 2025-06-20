
CC:=clang

SRC_DIR:=src/
INC_DIR:=include/

CFLAGS:=-I$(INC_DIR)

ODIR := build
SOURCES := $(shell find $(SRC_DIR) -name "*.c")
ASM_SOURCES := $(shell find $(SRC_DIR) -name "*.S")
INCLUDES := $(shell find $(INC_DIR) -name "*.h")


OBJS := $(patsubst %.c,%.o,$(SOURCES)) $(patsubst %.S,%.o,$(ASM_SOURCES))

all: run

run: $(subst src/, $(ODIR)/,$(OBJS))
	$(CC) $(CFLAGS) -o $(ODIR)/$@ $^
	./$(ODIR)/$@

$(ODIR)/%.o: $(SRC_DIR)/%.S
	$(CC) $(CFLAGS) -c -o $@ $<

$(ODIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -r $(ODIR)/*
