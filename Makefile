NAME = os-image

all: $(NAME)

$(NAME): boot_sect.bin kernel.bin
	cat $^ > $@

boot_sect.bin: boot_sect.asm
	nasm $< -f bin -o $@

kernel.bin: kernel_entry.o kernel.o
	ld -o $@ -Ttext 0x1000 $^ --oformat binary

kernel.o : kernel.c
	gcc -ffreestanding -c $< -o $@

kernel_entry.o : kernel_entry.asm
	nasm $< -f elf64 -o $@


run:
	qemu-system-x86_64 -drive file=$(NAME),index=0,format=raw
clean:
	rm *.bin *.o

fclean: clean
	rm $(NAME)

re: fclean all

.phony: all clean fclean re run
