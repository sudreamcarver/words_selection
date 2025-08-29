TARGET = words_selection

DEBUG = 1

BUILD_DIR = build

C_HEADERS = ./inc
C_SOURCES = ./src
SRCS := $(wildcard $(C_SOURCES)/*.c)
OBJS := $(patsubst $(C_SOURCES)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

CC = gcc
CFLAGS = -Wall -Wextra -I$(C_HEADERS) \
		 -isystem /usr/include \
		 -isystem /usr/lib/gcc/x86_64-pc-linux-gnu/15.1.1/include

ifeq ($(DEBUG), 1)
	CFLAGS += -g
else
	CFLAGS += -O2
endif

all: $(BUILD_DIR) $(TARGET)
	@echo "---Build complete---"

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@
	@echo "Linked: $@---"

$(BUILD_DIR)/%.o: $(C_SOURCES)/%.c
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled: $<---"

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

.PHONY: all clean
