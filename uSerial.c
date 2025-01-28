#include "uSerial.h"
#include "string.h"
#include "stdio.h"

// Static pointer to the active SerialDriver instance
static uSerial *active_driver = NULL;

void uSerial_init(uSerial *driver, void (*send_char_func)(const char *c)) {
  if (!driver || !send_char_func) return;  // Ensure valid input

  driver->send_char = send_char_func;
  driver->print_int = print_int_func;

  active_driver = driver;  // Set this driver as the active instance
}

void print_int_func(int num) {
    // Buffer to store the string representation of the integer
    char intString[16]; // At most 11 characters + null terminator +\n\r

    // Convert the integer to a string
    if (num == 0) {
        intString[0] = '0';
        intString[1] = '\0';
    } else {
        // Check if the number is negative
        int isNegative = num < 0;
        if (isNegative) {
            num = -num;
        }

        // Convert the number to decimal representation
        uint32todec2((uint32_t)num, intString);

        // Prepend a negative sign if the number was negative
        if (isNegative) {
            memmove(intString + 1, intString, strlen(intString) + 1);
            intString[0] = '-';
        }
    }

    // safely add the \n\r
    size_t len = strlen(intString);
    if (len + 2 < sizeof(intString)) {  // Ensure buffer size is sufficient
        strcat(intString, "\n\r");
    }

    // Output the string
    active_driver->send_char(intString);
}

void uint32todec2(uint32_t data, char* decstring) {
    memset(decstring, 0, 11); // initialize the array with null characters
    uint8_t i = 0;
    do {
        decstring[i++] = (data % 10) + '0';
        data /= 10;
    } while(data > 0);

    // reverse the string
    uint8_t j = 0;
    i--;
    while(j < i) {
        char temp = decstring[j];
        decstring[j] = decstring[i];
        decstring[i] = temp;
        j++;
        i--;
    }
}
