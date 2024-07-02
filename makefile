CC=gcc
CFLAGS=-I.
build: vram_main.o vram.o
	$(CC) -o vram_main.bin vram_main.o vram.o
	./vram_main.bin