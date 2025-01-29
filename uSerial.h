#ifndef USERIAL_H
#define USERIAL_H

#include <stdint.h>
#include <stdbool.h>


// Main Struct Definition
typedef struct uSerial {
  void (*send_char)(const char *c); //function to print char buffer

  void (*uint8ToDec)(uint8_t value);    // function to print uint8_t in decimal format
  void (*uint16ToDec)(uint16_t value);  // function to print uint16_t in decimal format
  void (*uint32ToDec)(uint32_t value);  // function to print uint32_t in decimal format
  void (*uint64ToDec)(uint64_t value);  // function to print uint64_t in decimal format

  void (*uint8ToHex)(uint8_t value);    // function to print uint8_t in hexadecimal format
  void (*uint16ToHex)(uint16_t value);  // function to print uint16_t in hexadecimal format
  void (*uint32ToHex)(uint32_t value);  // function to print uint32_t in hexadecimal format
  void (*uint64ToHex)(uint64_t value);  // function to print uint64_t in hexadecimal format

  void (*uint8ToBin)(uint8_t value);    // function to print uint8_t in binary format
  void (*uint16ToBin)(uint16_t value);  // function to print uint16_t in binary format
  void (*uint32ToBin)(uint32_t value);  // function to print uint32_t in binary format
  void (*uint64ToBin)(uint64_t value);  // function to print uint64_t in binary format

  void (*printInt)(int value);          // function to print an integer
  void (*printFloat)(float value);      // function to print a float
  void (*printDouble)(double value);    // function to print a double
  void (*printBool)(bool value);        // function to print a boolean} uSerial;
} uSerial;

// init function
void uSerial_init(uSerial *driver, void (print_char_func)(const char *c));

//helper functions
void uSerial_sendBuffer(char* buffer);
void uSerial_uintToBin(uint64_t value, uint8_t bits);

//print functions
void uSerial_uint8ToDec_func(uint8_t value);
void uSerial_uint16ToDec_func(uint16_t value);
void uSerial_uint32ToDec_func(uint32_t value);
void uSerial_uint64ToDec_func(uint64_t value);
void uSerial_uint8ToHex_func(uint8_t value);
void uSerial_uint16ToHex_func(uint16_t value);
void uSerial_uint32ToHex_func(uint32_t value);
void uSerial_uint64ToHex_func(uint64_t value);
void uSerial_uint8ToBin_func(uint8_t value);
void uSerial_uint16ToBin_func(uint16_t value);
void uSerial_uint32ToBin_func(uint32_t value);
void uSerial_uint64ToBin_func(uint64_t value);
void uSerial_printInt_func(int value);
void uSerial_printFloat_func(float value);
void uSerial_printDouble_func(double value);
void uSerial_printBool_func(bool value);

#endif // USERIAL_H
