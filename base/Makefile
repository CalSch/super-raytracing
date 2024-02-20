rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

CC := gcc
AR := ar
CFLAGS := -Iinclude

SRC := $(call rwildcard,src,*.c)
OUT_DIR := dst
OBJ_DIR := obj
TARGET := librtx.a

OBJECTS  := $(SRC:%.c=$(OBJ_DIR)/%.o)
DEPENDENCIES \
         := $(OBJECTS:.o=.d)

$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c -MMD -o $@ $<

$(TARGET): $(OBJECTS)
	$(AR) rcs $(OUT_DIR)/$(TARGET) $(OBJECTS)

-include: $(DEPENDENCIES)

.PHONY: all clean ds

all: $(TARGET)

ds: OUT_DIR = dst/arm
ds: CC = /opt/devkitpro/devkitARM/bin/arm-none-eabi-gcc
ds: AR = /opt/devkitpro/devkitARM/bin/arm-none-eabi-ar
ds: all