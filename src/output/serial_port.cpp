#include "../output.h"

void serial_configure_baud_rate(unsigned long com, unsigned long divisor) {
  /* Tell the serial com to first expect the highest 8 bits, then the lowest
   * 8 bits. This is done by sending 0x80 to the line command com
   */
  outb(SERIAL_LINE_COMMAND_PORT(com), SERIAL_LINE_ENABLE_DLAB);
  outb(SERIAL_DATA_PORT(com), (divisor >> 8) & 0x00FF);
  outb(SERIAL_DATA_PORT(com), divisor & 0x00FF);
}

void serial_configure_line(unsigned long com) {
  /* Bit:     | 7 | 6 | 5 4 3 | 2 | 1 0 |
   * Content: | d | b | prty  | s | dl  |
   * Value:   | 0 | 0 | 0 0 0 | 0 | 1 1 | = 0x03
   * data length of 8 bits, one stop bit, no parity bit, break control
   * disabled and DLAB disabled
   */
  outb(SERIAL_LINE_COMMAND_PORT(com), 0x03);
}

void serial_configure_fifo_buffer(unsigned long com) {
  /* Bit:     | 7 6 | 5  | 4 | 3   | 2   | 1   | 0 |
   * Content: | lvl | bs | r | dma | clt | clr | e |
   * Value:   | 1 1 | 0  | 0 | 0   | 1   | 1   | 1 | = 0xC7
   */
  outb(SERIAL_FIFO_COMMAND_PORT(com), 0xC7);
}

void serial_configure_modem(unsigned long com) {
  /* Bit:     | 7 | 6 | 5  | 4  | 3   | 2   | 1   | 0   |
   * Content: | r | r | af | lb | ao2 | ao1 | rts | dtr |
   * Value:   | 0 | 0 | 0  | 0  | 0   | 0   | 1   | 1 | = 0x03
   */
  outb(SERIAL_MODEM_COMMAND_PORT(com), 0x03);
}

int serial_is_transmit_fifo_empty(unsigned long com) {
  /* 0x20 = 0010 0000 */
  return inb(SERIAL_LINE_STATUS_PORT(com)) & 0x20;
}

int serial_write(unsigned long com, char *buf, unsigned int len) {
    unsigned int indexToBuffer = 0;
    while (indexToBuffer < len) {
        serial_write_byte(com, buf[indexToBuffer]);
        indexToBuffer++;
    
    }
    return 0;
}

void serial_write_byte(unsigned long com, char byteData) {
    while(!serial_is_transmit_fifo_empty(com));

    outb(com, byteData);
}

unsigned long configured_com;

void serial_configure(unsigned long com, unsigned long baudRate) {

    configured_com = com;

    serial_configure_baud_rate(com, baudRate);
    serial_configure_line(com);
    serial_configure_fifo_buffer(com);
    serial_configure_modem(com);
}
