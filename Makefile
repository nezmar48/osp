CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
    	 -nostartfiles -nodefaultlibs -Wall -Wextra -Werror -c
# add cpp and assembly files here (no suffix)  
<<<<<<< HEAD
OBJECTS = loader kmain io 
=======
OBJECTS = loader kmain gdt
>>>>>>> 3da34d091c69dd9f488940e152ad9122a279fc87

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

kernel.elf: $(addsuffix .o, $(OBJECTS))
	ld -T src/link.ld -melf_i386 $(addsuffix .o, $(addprefix bin/, $(OBJECTS))) -o bin/kernel.elf 
	cp bin/kernel.elf iso/boot/kernel.elf

%.o: src/%.s
	nasm -f elf32 $< -o bin/$@

%.o: src/%.cpp
	g++ $(CFLAGS) $< -o bin/$@
	
run: os.iso
	bochs -f src/bochsrc.txt -q
