os.iso: kernel.elf
	genisoimage -R                          \
        	    -b boot/grub/stage2_elitro      \
            	-no-emul-boot                   \
            	-boot-load-size 4               \
            	-A os                           \
            	-input-charset utf8             \
            	-quiet                          \
            	-boot-info-table                \
            	-o bin/os.iso                       \
            	iso

	

kernel.elf: loader.o
	ld -T src/link.ld -melf_i386 bin/loader.o bin/kmain.o -o bin/kernel.elf 
	cp bin/kernel.elf iso/boot/kernel.elf

loader.o:
	nasm -f elf32 src/loader.s -o bin/loader.o

run: os.iso
	bochs -f src/bochsrc.txt -q
	
c:
	gcc -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
             -nostartfiles -nodefaultlibs -Wall -Wextra -Werror -c \
			 src/kmain.c -o bin/kmain.o
