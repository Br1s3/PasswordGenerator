CC = gcc
RM = rm -rf

FLAGS += \
-Wall \
-Wextra \
-Wno-unused-parameter

.PHONY: all clean


all: PasswordGenerator

PasswordGenerator: PasswordGenerator.c
	$(CC) $< -o $@ $(FLAGS)

clean:
	$(RM) PasswordGenerator
