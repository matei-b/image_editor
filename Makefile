# compiler setup
CC=gcc
CFLAGS=-Wall -Wextra -std=c99

# define targets
TARGETS = image_editor

build: $(TARGETS)

image_editor: main.c
	$(CC) main.c matrix.c load.c select.c histogram.c equalize.c apply.c rotate.c crop.c save.c -g -o image_editor -lm

pack:
	zip -FSr 312CA_BalanMatei_Tema3.zip README Makefile *.c *.h

clean:
	rm -f $(TARGETS)

run: clean build

.PHONY: pack clean