#include <stdio.h>

#define ALIGN_WORD __attribute__((aligned(4))) // Align 4 BYTES (32 bits)

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;

static inline void decimalToBinary(u16 num)
{
    if (num == 0)
    {
        printf("0");
        return;
    }

    // Stores binary representation of number.
    int binaryNum[32]; // Assuming 32 bit integer.
    int i = 0;

    for (; num > 0;)
    {
        binaryNum[i++] = num % 2;
        num /= 2;
    }

    // Printing array in reverse order.
    for (int j = i - 1; j >= 0; j--)
    {
        printf("%d", binaryNum[j] ? binaryNum[j] : 0);
    }

    printf("\n");
}
static inline void printInt(u16 num)
{
    printf("printInt: %d \n", num);
}

static inline u32 bitwiseLog(u32 n)
{
    u32 logValue = 0;
    while (n > 1)
    {
        logValue++;
        n >>= 1;
    }

    return logValue;
}

int main(void)
{
    u32 x = bitwiseLog(128);
    decimalToBinary((u16)x);
    printInt(x);

    printf("\n\nterminating...\n");
    return 0;
}
