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

enum eKeyIndex
{
    KI_A = 0,
    KI_B,
    KI_SELECT,
    KI_START,
    KI_RIGHT,
    KI_LEFT,
    KI_UP,
    KI_DOWN,
    KI_R,
    KI_L,
    KI_MAX
};

int main(void)
{

    u16 __key_curr = 0x0001;
    u32 aDown = (__key_curr >> KI_A);
    // u32 bDown = (__key_curr >> KI_B) & 1;

    printf("aDown: %d\n", aDown);
    // printf("bDown: %d", bDown);

    printf("\n\nterminating...\n");
    return 0;
}
