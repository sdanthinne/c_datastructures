
CC:=clang

SRC_DIR:=src/
INC_DIR:=include/

CFLAGS:=-I$(INC_DIR) -Wmissing-declarations -Wall -Wextra -Wpedantic -Werror 

# Add security warnings
SECURITY_WARNINGS :=-Walloca -Wconversion -Wformat-security -Wnull-dereference -Wstack-protector -Wvla -Warray-bounds -Warray-bounds-pointer-arithmetic -Wunreachable-code-aggressive -Wthread-safety -Wloop-analysis -Wimplicit-fallthrough -Wconditional-uninitialized -Wcomma -Wbad-function-cast -Wfloat-equal -Wpointer-arith -Wshift-sign-overflow -Wtautological-constant-in-range-compare -Wassign-enum -Wswitch-enum
SECURITY_FEATURES :=-fstack-protector-all -fPIE -fstack-clash-protection -ftrivial-auto-var-init=pattern -fsanitize=integer -flto=full -fsanitize=undefined
# safe-stack and ubsan not working

CFLAGS += $(SECURITY_WARNINGS) $(SECURITY_FEATURES)

LDFLAGS :=--gc-sections
LIBS :=m

ODIR := build
SOURCES := $(shell find $(SRC_DIR) -name "*.c")
ASM_SOURCES := $(shell find $(SRC_DIR) -name "*.S")
INCLUDES := $(shell find $(INC_DIR) -name "*.h")


OBJS := $(patsubst %.c,%.o,$(SOURCES)) $(patsubst %.S,%.o,$(ASM_SOURCES))

all: run

run: $(subst src/, $(ODIR)/,$(OBJS))
	$(CC) $(CFLAGS) -Wl,$(LDFLAGS) -l$(LIBS) -o $(ODIR)/$@ $^
	./$(ODIR)/$@

$(ODIR)/%.o: $(SRC_DIR)/%.S
	$(CC) $(CFLAGS) -c -o $@ $<

$(ODIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -r $(ODIR)/*
