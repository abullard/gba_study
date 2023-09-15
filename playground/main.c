#include <stdio.h>

typedef unsigned short u16;
typedef unsigned int u32;

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
    u32 vid_page = 0x06000000 + 0x0A000;
    u32 reg_disp_ctl = 0x0004 | 0x0400;

    u32 stuff = vid_page ^ 0x0A000;

    printf("\nvid_page ");
    decimalToBinary(vid_page);
    printf("\nreg_disp_ctl ");
    decimalToBinary(reg_disp_ctl);
    printf("\nstuff ");
    decimalToBinary(stuff);

    u32 idkYet = reg_disp_ctl ^= 0x0010;
    printf("\nidkYet ");
    decimalToBinary(idkYet);

    printf("\n\nterminating...\n");
    return 0;
}
