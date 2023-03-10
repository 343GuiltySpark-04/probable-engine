#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include "c_printf.h"

/**
 * @brief Calculates the difference between two hexidecimal numbers. This is a shortcut for the user asking for the difference between two numbers and returning the result.
 * @return The difference between the two numbers or 0 if the numbers are equal or not in hexidecimal format
 */
uint64_t hex_diff()
{

    uint64_t a, b, c;

    c_printf("[g]%s", "Enter the first value: ");
    scanf("%llx", &a);

    c_printf("[g]%s", "Enter the second value: ");
    scanf("%llx", &b);

    // Calculates the value of the c value.
    if (a > b)
    {

        c = a - b;
    }
    // Calculates the c value of the b
    else if (b > a)
    {

        c = b - a;
    }
    else
    {

        c = 0;
    }

    return c;
}

// Function to convert hexadecimal to binary
// is causing seg faults
/**
 * @brief Converts a hex number to binary and prints it to standard output. The output is in reverse order of the number
 * @param n the number to be
 */
void hexToBinary(uint64_t n)
{
    // array to store binary number
    uint64_t binaryNum[12];

    // counter for binary array
    uint64_t i = 0;
    // Fills the binaryNum array with the remainder of the binaryNum.
    while (n > 0)
    {

        // storing remainder in binary array
        binaryNum[i] = n % 2;
        n = n / 2;
        i++;
    }

    c_printf("[y]%s", "Ox");
    c_printf("[y]%x", n);
    c_printf("[m]%s\n", "in binary is.");

    // printing binary array in reverse order
    // Print the binary number in binaryNum
    for (uint64_t j = i - 1; j >= 0; j--)
    {

        c_printf("[y]%d", binaryNum[j]);
    }

    printf("\n"); // Added a new line for output formatting.

    return; // Added return statement.
}

/**
 * @brief Check if the address is canonical for x86_64. This is useful for verifying that we don't have a problem with unicorn's addressing system
 * @return true if the address is
 */
bool is_canonical()
{

    uint64_t addr; // Memory address

    c_printf("[y]%s", "Enter the address to test (without the 0x prefix): ");
    scanf("%llx", &addr);

    // check if the address is canonical for x86_64
    bool result = (addr >> 63) == 0;

    return result;
}

/**
 * Extract bits from an integer. This is the inverse of bitwise_shift ()
 *
 * @param num - The integer to extract bits from
 * @param start - The bit position to start extracting
 * @param length - The number of bits to extract
 *
 * @return The bits at the start of num that were extracted
 */
uint64_t bitwise_extract(uint64_t num, uint64_t start, uint64_t length)
{
    /* Create a mask by shifting 1 left by length bits and subtracting 1 */
    uint64_t mask = (1 << length) - 1;

    /* Shift num right by start bits and apply mask */
    return (num >> (start - length + 1)) & mask;
}

/**
 * @brief Converts hex string to decimal number. This function is used to convert hex string to decimal number. For example convertHexToDecimal ( " 0A " ) would return 2.
 * @param hex The hex string to convert to decimal number. It is assumed that the array is terminated by 0
 */
long long convertHexToDecimal(char hex[])
{
    long long decimalNumber = 0;
    int i = 0;
    while (hex[i] != '\0')
    {
        // Get current character and convert it to integer
        char ch = hex[i]; // Current character
        int digit;        // Digit value of current character

        if (ch >= '0' && ch <= '9')
        {                     // Character is a digit between 0-9
            digit = ch - '0'; // Convert charcter to its corresponding integer value
        }
        else if (ch >= 'a' && ch <= 'f')
        {                          // Character is a letter between a-f
            digit = 10 + ch - 'a'; // Convert charcter to its corresponding integer value
        }
        else if (ch >= 'A' && ch <= 'F')
        {                          // Character is a letter between A-F
            digit = 10 + ch - 'A'; // Convert charcter to its corresponding integer value
        }

        decimalNumber += digit * pow(16, strlen(hex) - i - 1);

        i++; // Increment index of character in hexadecimal string
    }

    return decimalNumber; // Return the converted hexadecimal number in decimal format
}

/**
 * @brief Main program. Prints a message to the standard output and checks the validity of the address before proceeding
 */
void main()
{

    uint8_t i;

L1:

    c_printf("[c]%s\n", "What do you wish to do?");
    c_printf("[m]%s\n", "1) Hexadecimal diff.");
    c_printf("[m]%s\n", "2) Canonical address checking.");
    c_printf("[m]%s\n", "3) Hex to Binary. (very buggy right now (seg faults on use))");
    c_printf("[m]%s\n", "4) Hex to Decimal.");
    c_printf("[m]%s\n", "5) Bitwise extract (Dec).");
    c_printf("[m]%s\n", "6) Bitwise extract (Hex).");
    c_printf("[m]%s\n", "9) Exit.");
    c_printf("[g]%s", ":> ");
    scanf("%u", &i);

    // Check user input and go to the appropriate label based on the value entered.
    switch (i)
    {
    case 1:
        system("clear");
        goto L3;
        break;

    case 2:
        system("clear");
        goto L2;

    case 3:
        system("clear");
        goto L4;
        break;

    case 4:
        system("clear");
        goto L5;
        break;

    case 5:
        system("clear");
        goto L6;
        break;

    case 6:
        system("clear");
        goto L7;
        break;

    case 9: // Exit the program if user enters 9.
        return;

    default: // If user input is not 1, 2, or 9, go back to the beginning.
        goto L1;
    }

    bool can;

L2:

    can = is_canonical();

    // if can true prints out the address is canonical you re problems lie elsewhere mate.
    if (can == true)
    {

        c_printf("[g]%s\n", "This address is canonical you're problems lie elsewhere mate.");
        goto L1;
    }
    else
    {

        c_printf("[r]%s\n", "Well there's you're problem its non-canonical!");
        goto L1;
    }

    uint64_t out;

L3:

    out = hex_diff();

    c_printf("[c]%s", "The Result is: ");
    c_printf("[y]%u", out);
    c_printf("[c]%s", " or ");
    c_printf("[y]%s", "0x");
    c_printf("[y]%x\n", out);
    goto L1;

    uint64_t h2b_in;

L4:

    c_printf("[g]%s", "Enter the hexadecimal number to convert: ");
    scanf("%u", &h2b_in);
    hexToBinary(h2b_in);
    goto L1;

    char h2d_in[17];
    long long h2d_res;

L5:

    c_printf("[g]%s", "Enter Hex number to convert (without the 0x prefix): ");
    scanf("%s", &h2d_in);
    h2d_res = convertHexToDecimal(h2d_in);
    c_printf("[m]%s", "Result: ");
    c_printf("[y]%u\n", h2d_res);

    goto L1;

    uint64_t s, l, n, bit_res;

L6:

    c_printf("[g]%s", "Enter decimal value to extract from: ");
    scanf("%u", &n);
    c_printf("[g]%s", "Enter bit to start from: ");
    scanf("%u", &s);
    c_printf("[g]%s", "Enter number of bits to extract: ");
    scanf("%u", &l);
    bit_res = bitwise_extract(n, s, l);
    c_printf("[c]%s", "Here are the resulting bits: ");
    c_printf("[y]%u\n", bit_res);

    goto L1;

L7:

    c_printf("[g]%s", "Enter hex value to extract from (Without the 0x prefix): ");
    scanf("%x", &n);
    c_printf("[g]%s", "Enter bit to start from: ");
    scanf("%u", &s);
    c_printf("[g]%s", "Enter number of bits to extract: ");
    scanf("%u", &l);
    bit_res = bitwise_extract(n, s, l);
    c_printf("[c]%s", "Here are the resulting bits: ");
    c_printf("[y]%x\n", bit_res);

    goto L1;
}