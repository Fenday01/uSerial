#ifndef USERIAL_H
#define USERIAL_H

#include <stdint.h>

// Main Struct Definition
typedef struct uSerial {
  void (*send_char)(const char *c); //function to print char buffer
  void (*print_int)(int value); //function to print integer
} uSerial;

// init function
void uSerial_init(uSerial *driver, void (print_char_func)(const char *c));

// print functions
void print_int_func(int value);


// conversion functions
void uint32todec2(uint32_t data, char* decstring);

#endif // USERIAL_H
