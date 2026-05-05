CC = gcc
RM = rm -rf

FLAGS += \
-Wall \
-Wextra \
-Wno-unused-parameter

.PHONY: all clean


all: pwgen

pwgen: PasswordGenerator.c
	$(CC) $< -o $@ $(FLAGS)

clean:
	$(RM) pwgen
