all:
	nasm -f bin ./boot.S -o ./boot.bin
	dd if=./message.txt >> ./boot.bin
	dd if=/dev/zero bs=512 count=1 >> ./boot.bin