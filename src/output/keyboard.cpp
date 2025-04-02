#include "../output.h"
#include "../interrupts.h"


#define KBD_DATA_PORT   0x60
#define KEYBOARD_STATUS_PORT 0x64
  /** read_scan_code:
   *  Reads a scan code from the keyboard
   *
   *  @return The scan code (NOT an ASCII character!)
    */
void keyboard_flush_buffer()
{
        for (int i = 0; i < 10; i++) { // Read multiple times just in case
        if (inb(KEYBOARD_STATUS_PORT) & 1) {
            inb(KBD_DATA_PORT); // Discard data
        }
    }
};


unsigned char keyboard_read_scan_code(void)
{
    unsigned char scancode; 
    
    do {
        while (!(inb(KEYBOARD_STATUS_PORT) & 1));  // Wait for bit 0 (output buffer full)
        scancode = inb(KBD_DATA_PORT);
    } while (scancode == 0xFA || scancode == 0xFE); // Ignore ACK (0xFA) and Resend Request (0xFE)
    
    keyboard_flush_buffer();


    return scancode;

};

unsigned char keyboard_scan_code_to_ascii(unsigned char scan_code)
{
	unsigned char ascii[257] =
	{
		0x0, 0x0, '1', '2', '3', '4', '5', '6',		// 0 - 7
		'7', '8', '9', '0', '-', '=', 0x1, 0x0,		// 8 - 15
		'q', 'w', 'e', 'r', 't', 'y', 'u', 'i',		// 16 - 23
		'o', 'p', '[', ']', 0x2, 0x0, 'a', 's',	// 24 - 31
		'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',		// 32 - 39
		'\'', '`', 0x0, '\\', 'z', 'x', 'c', 'v',	// 40 - 47
		'b', 'n', 'm', ',', '.', '/', 0x0, '*',		// 48 - 55
		0x0, ' ', 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,		// 56 - 63
		0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, '7',		// 64 - 71
		'8', '9', '-', '4', '5', '6', '+', '1',		// 72 - 79
		'2', '3', '0', '.'				// 80 - 83
	};

	return ascii[scan_code];
}
void addChar(unsigned char *s, char c) {

    while (*s) s++;  

    // Append the new character
    *s = c;

    // Add null terminator at the new end
    *(s + 1) = '\0';  // Move pointer to the end
  
};

int strlen(const char *s) {
    int len = 0;
    while (*s++) len++;
    return len;
};

unsigned char display_log[] = "";





void keyboard_handler() {
    
    unsigned char scancode = keyboard_read_scan_code(); 
    
    clear_screen();
    
    outb(0x20, 0x20);
    outb(0xA0, 0x20);

    // Ignore key releases (break codes)
    if (scancode & 0x80) {
        return;
    }
    
    //translates character to ascii, ads to array and writes it in the console
    unsigned char character = keyboard_scan_code_to_ascii(scancode);
    addChar(display_log, character);
    fb_write(display_log,strlen((char*)display_log),RED,BLACK);

    // Ensure IRQ1 is unmasked (enable keyboard interrupt)
    unsigned char mask = inb(0x21); // Read current IRQ mask
    mask &= ~(1 << 1); // Clear bit 1 (IRQ1 
    outb(0x21, mask); // Write new mask back to PIC

}

void keyboard_init() {
    // Remap PIC to avoid conflicts
    pic_remap();

    // Set keyboard handler in IDT (IRQ1 -> 0x21)
    idt_set_descriptor(0x21, (void*)keyboard_handler, 0x8E);

    // Unmask keyboard interrupt (IRQ1) in PIC
    outb(0x21, inb(0x21) & ~0x02);

    // Reset and enable the keyboard
    outb(0x64, 0xAD);  // Disable keyboard
    outb(0x64, 0xAE);  // Enable keyboard interface
    outb(0x60, 0xF4);  // Enable keyboard scannin

    asm volatile ("sti");

}

