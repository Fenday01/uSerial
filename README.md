# uSerial

## Description
uSerial is a C library containing verious functions that allow the user to send different veriable types over a serial port

The user must provide a serial write function that can write character arrays to a serial port. This function is then assigned to uSerial and used to print the results of its veriable to string conversions.

## Setup
The user provides a basic function that prints char arrays to a serial port, like the below example.

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

That function is then assigned to uSerial like below. In this instance we called it debug, and then print a uint8_t in binary format.

```c
uint8_t test = 0x4b

uSerial debug;
uSerial_init(&debug, putstr);

debug.uint8ToBin(test);
```

## Usage
Useage is relitivly selfe explanitary. the print options are below.

### Decimal Format Printing

```c
uint8ToDec(uint8_t value)     //Prints an 8-bit unsigned integer (uint8_t) in decimal format.
uint16ToDec(uint16_t value)   //Prints a 16-bit unsigned integer (uint16_t) in decimal format.
uint32ToDec(uint32_t value)   //Prints a 32-bit unsigned integer (uint32_t) in decimal format.
uint64ToDec(uint64_t value)   //Prints a 64-bit unsigned integer (uint64_t) in decimal format.
```

### Hexadecimal Format Printing

```c
uint8ToHex(uint8_t value)     //Prints an 8-bit unsigned integer (uint8_t) in hexadecimal format.
uint16ToHex(uint16_t value)   //Prints a 16-bit unsigned integer (uint16_t) in hexadecimal format.
uint32ToHex(uint32_t value)   //Prints a 32-bit unsigned integer (uint32_t) in hexadecimal format.
uint64ToHex(uint64_t value)   //Prints a 64-bit unsigned integer (uint64_t) in hexadecimal format.
```

### Binary Format Printing

```c
uint8ToBin(uint8_t value)     //Prints an 8-bit unsigned integer (uint8_t) in binary format.
uint16ToBin(uint16_t value)   //Prints a 16-bit unsigned integer (uint16_t) in binary format.
uint32ToBin(uint32_t value)   //Prints a 32-bit unsigned integer (uint32_t) in binary format.
uint64ToBin(uint64_t value)   //Prints a 64-bit unsigned integer (uint64_t) in binary format.
```

### General Printing Functions

```c
printInt(int value)           //Prints a signed integer (int).
printFloat(float value)       //Prints a floating-point number (float).
printDouble(double value)     //Prints a double-precision floating-point number (double).
printBool(bool value)         //Prints a boolean value (bool), displaying true or false.
```


