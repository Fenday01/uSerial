uSerial Library is a C library that that takes different veriable formats a prints them out a serial port

the user must provide a serial write function that can write character arrays to the serial port.

basic usage is outlined below,

void putstr(const char *buffer)
{
  uint8_t ptr = 0;

  while (buffer[ptr] != '\0')
    {
    LEUART_Tx(LEUART0, buffer[ptr]);
    ptr++;
    }
}

above is a basic function that prints the contense of buffer to a serial port. its assigned to uSerial as shown in the below example

uSerial debug;
uSerial_init(&debug, putstr);