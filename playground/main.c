#include <stdio.h>

#define ALIGN_WORD __attribute__((aligned(4))) // Align 4 BYTES (32 bits)

typedef unsigned char u8;
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
    s16 gravity_g = 0x0120, gravity_accel_g = 0x0020;

    gravity_g += gravity_accel_g;
    gravity_g += gravity_accel_g;
    gravity_g += gravity_accel_g;
    gravity_g += gravity_accel_g;
    gravity_g += gravity_accel_g;
    gravity_g += gravity_accel_g;
    gravity_g += gravity_accel_g;
    gravity_g += gravity_accel_g;
    gravity_g += gravity_accel_g;
    gravity_g += gravity_accel_g;
    gravity_g += gravity_accel_g;
    gravity_g += gravity_accel_g;
    gravity_g += gravity_accel_g;
    gravity_g += gravity_accel_g;
    gravity_g += gravity_accel_g;
    gravity_g += gravity_accel_g;
    gravity_g += gravity_accel_g;
    gravity_g += gravity_accel_g;
    gravity_g += gravity_accel_g;

    // decimalToBinary(gravity_g);
    printf("%d \n", gravity_g >> 8);

    printf("\n\nterminating...\n");
    return 0;
}
