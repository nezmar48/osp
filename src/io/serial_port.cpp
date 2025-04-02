#include "../io.h"

void serial_configure_baud_rate(unsigned short com, unsigned short divisor) {
  outb(SERIAL_LINE_COMMAND_PORT(com), SERIAL_LINE_ENABLE_DLAB);
  outb(SERIAL_DATA_PORT(com), (divisor >> 8) & 0x00FF);
  outb(SERIAL_DATA_PORT(com), divisor & 0x00FF);
}

void serial_configure_line(unsigned short com) {
  outb(SERIAL_LINE_COMMAND_PORT(com), 0x03);
}

void serial_configure_fifo_buffer(unsigned short com) {
  outb(SERIAL_FIFO_COMMAND_PORT(com), 0xC7);
}

void serial_configure_modem(unsigned short com) {
  outb(SERIAL_MODEM_COMMAND_PORT(com), 0x03);
}

int serial_is_transmit_fifo_empty(unsigned short com) {
  return inb(SERIAL_LINE_STATUS_PORT(com)) & 0x20;
}

int serial_write(unsigned short com, char *buf, unsigned int len) {
    unsigned int indexToBuffer = 0;
    while (indexToBuffer < len) {
        serial_write_byte(com, buf[indexToBuffer]);
        indexToBuffer++;
    }
    return 0;
}

void serial_write_byte(unsigned short com, char byteData) {
    while(!serial_is_transmit_fifo_empty(com));

    outb(com, byteData);
}

int configured_com;

void serial_configure(unsigned short com, unsigned short baudRate) {
    configured_com = com;

    serial_configure_baud_rate(com, baudRate);
    serial_configure_line(com);
    serial_configure_fifo_buffer(com);
    serial_configure_modem(com);
}
