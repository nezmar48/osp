CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
    	 -nostartfiles -nodefaultlibs -Wall -Wextra -Werror -c -ffreestanding \
		 -mno-sse -mno-sse2 -mno-mmx -mno-avx

# add cpp and assembly files here (no suffix)  

OBJECTS = 	loader kmain \
			other/gdt other/multiboot \
			process/process process/call_process\
		  	output/io output/frame_buffer output/serial_port \
		  	interrupts/ex_handlers interrupts/idt interrupts/interrupts \
		  	paging/enable_paging paging/init_kernel_paging paging/load_page_directory paging/paging paging/disable_paging paging/loader_func\
			stdlib/string stdlib/memcopy stdlib/math

MODULES = program

os.iso: kernel.elf modules
	genisoimage -R                              \
        	    -b boot/grub/stage2_elitro      \
            	-no-emul-boot                   \
            	-boot-load-size 4               \
            	-A os                           \
            	-input-charset utf8             \
            	-quiet                          \
            	-boot-info-table                \
            	-o bin/os.iso                   \
            	iso

kernel.elf: $(addsuffix .o, $(addprefix bin/, $(OBJECTS)))
	ld -T src/link.ld -melf_i386 $(addsuffix .o, $(addprefix bin/, $(OBJECTS))) -o bin/kernel.elf 
	cp bin/kernel.elf iso/boot/kernel.elf

bin/%.o: src/%.s
	mkdir -p $(dir $@)
	nasm -f elf32 $< -o $@

bin/%.o: src/%.cpp
	mkdir -p $(dir $@)
	g++ $(CFLAGS) $< -o $@

iso/modules/%: modules/%.s
	mkdir -p $(dir $@)
	nasm -f bin $< -o $@

iso/modules/%: modules/%.cpp
	mkdir -p $(dir $@)
	g++ $(CFLAGS) $< -o $@

.PHONY: modules bochs clean clean_modules run

modules: clean_modules $(addprefix iso/modules/, $(MODULES))

bochs: os.iso 
	mkdir -p log
	rm -f log/com1.out
	bochs -f src/bochsrc.txt -q

clean: 
	rm -r bin/

clean_modules:
	rm -r iso/modules/

run: bochs clean
