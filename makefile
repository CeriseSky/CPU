APP_NAME:=cpu

SRC:=src
INCLUDE:=include

PREFIX:=$(shell pwd)/install/linux
BIN=$(PREFIX)/bin
TMP:=tmp
OUTPUT_DIRS:=$(PREFIX) \
             $(TMP) \
             $(BIN) \

CC:=clang++
CFLAGS:=-Wall -Werror -std=gnu++23 -I$(INCLUDE) -O3 -MMD -MP \
		-Wno-c99-designator

LD:=clang++
LIBS:=

SOURCES:=$(wildcard $(SRC)/*.cpp)

OBJS:=$(patsubst $(SRC)/%.cpp,$(TMP)/%.o,$(SOURCES))
DEPENDS:=$(patsubst $(SRC)/%.cpp,$(TMP)/%.d,$(SOURCES))

.PHONEY: all dirs clean

all: dirs $(BIN)/$(APP_NAME)

dirs: $(OUTPUT_DIRS)

clean: $(TMP)
	rm -rf $(TMP)

$(OUTPUT_DIRS):
	mkdir -p "$@"

$(BIN)/$(APP_NAME): $(OBJS)
	$(LD) $(OBJS) $(LIBS) -o "$@"

-include $(DEPENDS)

$(OBJS): $(TMP)/%.o: $(SRC)/%.cpp makefile
	$(CC) $(CFLAGS) -c $< -o "$@"

