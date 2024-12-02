CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
    	 -nostartfiles -nodefaultlibs -Wall -Wextra -Werror -c -ffreestanding

# add cpp and assembly files here (no suffix)  

OBJECTS = loader kmain output/io output/frame_buffer output/serial_port gdt  

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

kernel.elf: $(addsuffix .o, $(addprefix bin/, $(OBJECTS)))
	ld -T src/link.ld -melf_i386 $(addsuffix .o, $(addprefix bin/, $(OBJECTS))) -o bin/kernel.elf 
	cp bin/kernel.elf iso/boot/kernel.elf

bin/%.o: src/%.s
	@mkdir -p $(dir $@)
	nasm -f elf32 $< -o $@

bin/%.o: src/%.cpp
	@mkdir -p $(dir $@)
	g++ $(CFLAGS) $< -o $@
	
run: os.iso
	bochs -f src/bochsrc.txt -q

clean: 
	rm -r bin/

.PHONY: directories
directories:
	@mkdir -p $(addprefix bin/, $(dir $(OBJECTS)))
