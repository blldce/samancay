
FILES = ./build/kernel.S.o ./build/kernel.o ./build/vga.o ./build/idt.S.o ./build/idt.o ./build/memory.o ./build/heap_core.o ./build/kheap.o ./build/paging.S.o ./build/paging.o ./build/string.o
INCLUDES = -I./src
FLAGS = -g -ffreestanding -falign-jumps -falign-functions -falign-labels -falign-loops -fstrength-reduce -fomit-frame-pointer -finline-functions -Wno-unused-function -fno-builtin -Werror -Wno-unused-label -Wno-cpp -Wno-unused-parameter -nodefaultlibs -nostdlib -nostartfiles -nolibc -nodefaultlibs -Wall -O0 -Iinc


all: ./bin/boot.bin ./bin/kernel.bin
	dd if=./bin/boot.bin >> ./bin/os.bin
	dd if=./bin/kernel.bin >> ./bin/os.bin
	dd if=/dev/zero bs=512 count=100 >> ./bin/os.bin


./bin/boot.bin: ./src/boot/boot.S
	nasm -f bin ./src/boot/boot.S -o ./bin/boot.bin


./bin/kernel.bin: $(FILES)
	i686-elf-ld -g $(FILES) -o ./build/kernelfull.o
	i686-elf-gcc $(FLAGS) -T ./src/linker.ld -o ./bin/kernel.bin ./build/kernelfull.o



./build/kernel.S.o : ./src/kernel.S
	nasm -f elf -g ./src/kernel.S -o ./build/kernel.S.o

./build/kernel.o : ./src/kernel.c
	i686-elf-gcc $(INCLUDES) $(FLAGS) -std=gnu99 -c ./src/kernel.c -o ./build/kernel.o

./build/vga.o : ./src/vga/vga.c
	i686-elf-gcc $(INCLUDES) $(FLAGS) -std=gnu99 -c ./src/vga/vga.c -o ./build/vga.o
	
./build/idt.S.o : ./src/idt/idt.S
	nasm -f elf -g ./src/idt/idt.S -o ./build/idt.S.o

./build/paging.S.o : ./src/memory/paging/paging.S
	nasm -f elf -g ./src/memory/paging/paging.S -o ./build/paging.S.o
	
./build/idt.o : ./src/idt/idt.c
	i686-elf-gcc $(INCLUDES) $(FLAGS) -std=gnu99 -c ./src/idt/idt.c -o ./build/idt.o

./build/memory.o : ./src/memory/memory.c
	i686-elf-gcc $(INCLUDES) $(FLAGS) -std=gnu99 -c ./src/memory/memory.c -o ./build/memory.o	

./build/heap_core.o : ./src/memory/heap/heap_core.c
	i686-elf-gcc $(INCLUDES) $(FLAGS) -std=gnu99 -c ./src/memory/heap/heap_core.c -o ./build/heap_core.o

./build/kheap.o : ./src/memory/heap/kernel_heap/kheap.c
	i686-elf-gcc $(INCLUDES) $(FLAGS) -std=gnu99 -c ./src/memory/heap/kernel_heap/kheap.c -o ./build/kheap.o

./build/paging.o : ./src/memory/paging/paging.c
	i686-elf-gcc $(INCLUDES) $(FLAGS) -std=gnu99 -c ./src/memory/paging/paging.c -o ./build/paging.o

./build/string.o: ./src/string/string.c
	i686-elf-gcc $(INCLUDES) $(FLAGS) -std=gnu99 -c ./src/string/string.c -o ./build/string.o


clean:
	rm -rf ./bin/*.bin
	rm -rf ./build/*.o

run:
	qemu-system-i386 -hda ./bin/os.bin

debug:
	qemu-system-i386 -hda ./bin/os.bin -S -gdb stdio

