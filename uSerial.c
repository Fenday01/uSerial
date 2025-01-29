#include "uSerial.h"
#include "string.h"
#include "stdint.h"
#include "stdio.h"
#include "stdbool.h"


#define USERIAL_BUFFER_SIZE 69// max buffer + \n\r + \0

// Static pointer to the active SerialDriver instance
static uSerial *active_driver = NULL;

void uSerial_init(uSerial *driver, void (*send_char_func)(const char *c)) {
  if (!driver || !send_char_func) return;  // Ensure valid input

  driver->send_char = send_char_func;

  driver->uint8ToDec = uSerial_uint8ToDec_func;
  driver->uint16ToDec = uSerial_uint16ToDec_func;
  driver->uint32ToDec = uSerial_uint32ToDec_func;
  driver->uint64ToDec = uSerial_uint64ToDec_func;

  driver->uint8ToHex = uSerial_uint8ToHex_func;
  driver->uint16ToHex = uSerial_uint16ToHex_func;
  driver->uint32ToHex = uSerial_uint32ToHex_func;
  driver->uint64ToHex = uSerial_uint64ToHex_func;

  driver->uint8ToBin = uSerial_uint8ToBin_func;
  driver->uint16ToBin = uSerial_uint16ToBin_func;
  driver->uint32ToBin = uSerial_uint32ToBin_func;
  driver->uint64ToBin = uSerial_uint64ToBin_func;

  driver->printInt = uSerial_printInt_func;
  driver->printFloat = uSerial_printFloat_func;
  driver->printDouble = uSerial_printDouble_func;
  driver->printBool = uSerial_printBool_func;

  active_driver = driver;  // Set this driver as the active instance
}


// Helper function to add \n\r and send
void uSerial_sendBuffer(char* buffer) {
    size_t len = strlen(buffer);
    if (len + 2 < USERIAL_BUFFER_SIZE) {
        strcat(buffer, "\n\r");
    }
    active_driver->send_char(buffer);
}

/*-------------------------
 -----DECIMAL PRINTING-----
 ------------------------*/
void uSerial_uint8ToDec_func(uint8_t value) {
    char buffer[USERIAL_BUFFER_SIZE];
    sprintf(buffer, "%u", value);
    uSerial_sendBuffer(buffer);
}
void uSerial_uint16ToDec_func(uint16_t value) {
    char buffer[USERIAL_BUFFER_SIZE];
    sprintf(buffer, "%u", value);
    uSerial_sendBuffer(buffer);
}
void uSerial_uint32ToDec_func(uint32_t value) {
    char buffer[USERIAL_BUFFER_SIZE];
    sprintf(buffer, "%lu", (unsigned long)value);
    uSerial_sendBuffer(buffer);
}
void uSerial_uint64ToDec_func(uint64_t value) {
    char buffer[USERIAL_BUFFER_SIZE];
    int i = USERIAL_BUFFER_SIZE - 2;
    buffer[i + 1] = '\0';  // Null terminator

    do {
        buffer[i--] = '0' + (value % 10);
        value /= 10;
    } while (value > 0);

    uSerial_sendBuffer(&buffer[i + 1]);  // Send only the valid part
}

/*-------------------------
 ---HEXADECIMAL PRINTING---
 ------------------------*/
void uSerial_uint8ToHex_func(uint8_t value) {
    char buffer[USERIAL_BUFFER_SIZE];
    sprintf(buffer, "0x%02X", value);
    uSerial_sendBuffer(buffer);
}
void uSerial_uint16ToHex_func(uint16_t value) {
    char buffer[USERIAL_BUFFER_SIZE];
    sprintf(buffer, "0x%04X", value);
    uSerial_sendBuffer(buffer);
}
void uSerial_uint32ToHex_func(uint32_t value) {
    char buffer[USERIAL_BUFFER_SIZE];
    sprintf(buffer, "0x%08lX", value);
    uSerial_sendBuffer(buffer);
}
void uSerial_uint64ToHex_func(uint64_t value) {
    char buffer[USERIAL_BUFFER_SIZE];

    // Manually format 64-bit value as hex
    uint32_t high = (uint32_t)(value >> 32);  // Upper 32 bits
    uint32_t low = (uint32_t)(value & 0xFFFFFFFF);  // Lower 32 bits

    snprintf(buffer, sizeof(buffer), "0x%08lX%08lX", high, low);

    uSerial_sendBuffer(buffer);
}

/*-------------------------
 -----BINARY PRINTING------
 ------------------------*/
void uSerial_uintToBin(uint64_t value, uint8_t bits) {
    char buffer[USERIAL_BUFFER_SIZE] = "0b";
    for (int i = 0; i < bits; i++) {
        buffer[2 + i] = (value & ((uint64_t)1 << (bits - 1 - i))) ? '1' : '0';
    }
    buffer[2 + bits] = '\0';
    uSerial_sendBuffer(buffer);
}
void uSerial_uint8ToBin_func(uint8_t value) { uSerial_uintToBin(value, 8); }
void uSerial_uint16ToBin_func(uint16_t value) { uSerial_uintToBin(value, 16); }
void uSerial_uint32ToBin_func(uint32_t value) { uSerial_uintToBin(value, 32); }
void uSerial_uint64ToBin_func(uint64_t value) { uSerial_uintToBin(value, 64); }

/*-------------------------
 ------OTHER PRINTING------
 ------------------------*/
void uSerial_printInt_func(int value) {
    char buffer[USERIAL_BUFFER_SIZE];
    sprintf(buffer, "%d", value);
    uSerial_sendBuffer(buffer);
}
void uSerial_printFloat_func(float value) {
  char buffer[USERIAL_BUFFER_SIZE];

  bool isNegative = value < 0;
  if (isNegative) {
      value = -value;
  }

  int wholeNumber = (int)value;
  int decimalPart = (int)((value - wholeNumber) * 1000000);

  snprintf(buffer, sizeof(buffer), "%d.%06d", wholeNumber, decimalPart);

  char *end = buffer + strlen(buffer) - 1;
  while (*end == '0') {
      *end = '\0';
      end--;
  }

  // Remove the decimal point if nothing follows it
  if (*end == '.') {
      *end = '\0';
  }

  // Add negative sign if needed
  if (isNegative) {
      char temp[USERIAL_BUFFER_SIZE];
      snprintf(temp, sizeof(temp), "-%s", buffer);
      strcpy(buffer, temp);
  }

  uSerial_sendBuffer(buffer);
}
void uSerial_printDouble_func(double value) {
    char buffer[USERIAL_BUFFER_SIZE];

    bool isNegative = value < 0;
    if (isNegative) {
        value = -value;
    }

    int wholeNumber = (int)value;
    double fractional = value - wholeNumber;
    int decimalPart1 = (int)(fractional * 1000000000);  // First 9 decimal places
    int decimalPart2 = (int)((fractional * 1000000000000000) - ((int64_t)decimalPart1 * 1000000)); // Next 6 decimal places

    // Format the number with two parts
    snprintf(buffer, sizeof(buffer), "%d.%09d%06d", wholeNumber, decimalPart1, decimalPart2);

    // Trim trailing zeros
    char *end = buffer + strlen(buffer) - 1;
    while (*end == '0') {
        *end = '\0';
        end--;
    }

    // Remove the decimal point if nothing follows it
    if (*end == '.') {
        *end = '\0';
    }

    // Add negative sign if needed
    if (isNegative) {
        char temp[USERIAL_BUFFER_SIZE];
        snprintf(temp, sizeof(temp), "-%s", buffer);
        strcpy(buffer, temp);
    }

    uSerial_sendBuffer(buffer);
}
void uSerial_printBool_func(bool value) {
    active_driver->send_char(value ? "true\n\r" : "false\n\r");
}
