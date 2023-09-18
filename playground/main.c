#include <stdio.h>

#define ALIGN_WORD __attribute__((aligned(4))) // Align 4 BYTES (32 bits)

typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;

static inline void decimalToBinary(int num)
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
}

int main(void)
{
    u16 disp_cnt = 0x1000 | 0x0040; // result: 0001000001000000
    printf("%d \n", disp_cnt);
    decimalToBinary(disp_cnt);

    printf("\n\nterminating...\n");
    return 0;
}
