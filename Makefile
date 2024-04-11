#--------------------------------------Makefile-------------------------------------
#------------------
#		Wilcard
#-----------------
# - *: match any number of char
# - ?: match a single alpha in specific position
# - []: match char in brackekt
WARNING_STRING = testing
OBJECTS = ./build/boot.o ./build/kernel.o ./build/uart.o ./build/mailbox.o ./build/cli.o
CFILES = $(wildcard ./src/*.c) # = : keep updating assignment
OFILES = $(CFILES:./src/%.c=./build/%.o) # replace .c file to .o file, example: kernel.c -> kernel.o
GCCFLAGS = -Wall -O2 -ffreestanding -nostdinc -nostdlib # compiler
#----------------Target-------------------------------
# type make with the specific target name, it will run that target
all: clean uart_build mailbox_build cli_build kernel8.img minh

./build/boot.o: ./src/boot.S #check if  project have this boot
	aarch64-none-elf-gcc $(GCCFLAGS) -c ./src/boot.S -o ./build/boot.o > NUL 2>&1

./build/%.o: ./src/%.c #present all o and c
#this will compile all dependencies of the .o target to the full target name
	aarch64-none-elf-gcc $(GCCFLAGS) -c $< -o $@ > NUL 2>&1

uart_build: ./src/uart/uart.c
	aarch64-none-elf-gcc $(GCCFLAGS) -c ./src/uart/uart.c -o ./build/uart.o > NUL 2>&1

cli_build: ./src/cli/cli.c
	aarch64-none-elf-gcc $(GCCFLAGS) -c ./src/cli/cli.c -o ./build/cli.o > NUL 2>&1

mailbox_build: ./src/mailbox/mailbox.c
	aarch64-none-elf-gcc $(GCCFLAGS) -c ./src/mailbox/mailbox.c -o ./build/mailbox.o > NUL 2>&1

kernel8.img: $(OBJECTS)
#aarch64-none-elf-ld -nostdlib ./build/boot.o $(OFILES) -T ./src/link.ld -o ./build/kernel8.elf
	@echo $(WARNING_STRING)
	aarch64-none-elf-ld -nostdlib ./build/boot.o ./build/uart.o ./build/mailbox.o ./build/cli.o $(OFILES) -T ./src/link.ld -o ./build/kernel8.elf
	aarch64-none-elf-objcopy -O binary ./build/kernel8.elf kernel8.img
clean:
	del .\build\kernel8.elf .\build\*.o *.img
minh:
	qemu-system-aarch64 -M raspi3 -kernel kernel8.img -serial null -serial stdio