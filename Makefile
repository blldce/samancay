FILES = ./build/kernel.S.o

all: ./bin/boot.bin $(FILES)
	dd if=./bin/boot.bin >> ./bin/os.bin

./bin/boot.bin: ./src/boot/boot.S
	nasm -f bin ./src/boot/boot.S -o ./bin/boot.bin

./build/kernel.S.o: ./src/kernel.S
	nasm -f elf -g ./src/kernel.S -o ./build/kernel.S.o

clean:
	rm -rf ./bin/boot.bin
	rm -rf ./bin/os.bin
	rm -rf ./build/kernel.S.o