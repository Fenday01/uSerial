# uSerial

## Description
uSerial Library is a C library that that takes different veriable formats a prints them out a serial port

the user must provide a serial write function that can write character arrays to the serial port.

## Usage
useage is relitivly selfe explanitary. the print options are below.

*Decimal Format Printing*
uint8ToDec(uint8_t value)     Prints an 8-bit unsigned integer (uint8_t) in decimal format.
uint16ToDec(uint16_t value)   Prints a 16-bit unsigned integer (uint16_t) in decimal format.
uint32ToDec(uint32_t value)   Prints a 32-bit unsigned integer (uint32_t) in decimal format.
uint64ToDec(uint64_t value)   Prints a 64-bit unsigned integer (uint64_t) in decimal format.

*Hexadecimal Format Printing*
uint8ToHex(uint8_t value)     Prints an 8-bit unsigned integer (uint8_t) in hexadecimal format.
uint16ToHex(uint16_t value)   Prints a 16-bit unsigned integer (uint16_t) in hexadecimal format.
uint32ToHex(uint32_t value)   Prints a 32-bit unsigned integer (uint32_t) in hexadecimal format.
uint64ToHex(uint64_t value)   Prints a 64-bit unsigned integer (uint64_t) in hexadecimal format.

*Binary Format Printing*
uint8ToBin(uint8_t value)     Prints an 8-bit unsigned integer (uint8_t) in binary format.
uint16ToBin(uint16_t value)   Prints a 16-bit unsigned integer (uint16_t) in binary format.
uint32ToBin(uint32_t value)   Prints a 32-bit unsigned integer (uint32_t) in binary format.
uint64ToBin(uint64_t value)   Prints a 64-bit unsigned integer (uint64_t) in binary format.

*General Printing Functions*
printInt(int value)           Prints a signed integer (int).
printFloat(float value)       Prints a floating-point number (float).
printDouble(double value)     Prints a double-precision floating-point number (double).
printBool(bool value)         Prints a boolean value (bool), displaying true or false.


## setup
basic setup is outlined below,

the user provides a basic function that prints strings to a serial port, like the below example.

```c
void putstr(const char *buffer)
{
  uint8_t ptr = 0;

  while (buffer[ptr] != '\0')
    {
    LEUART_Tx(LEUART0, buffer[ptr]);
    ptr++;
    }
}
```

that function is then assigned to uSerial like below. in this instance we called it debug.

```c
uSerial debug;
uSerial_init(&debug, putstr);
```

you can make as many instances as you need if other ports need writing to.