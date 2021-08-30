#include <stdio.h>
#include <string.h>

const int seven_seg[] =
{
    0b1111110,
    0b0101000,
    0b1010111,
    0b1111001,
    0b0101011,
    0b1110011,
    0b1110111,
    0b1101000,
    0b1111111,
    0b1101011
};
const int seven_seg_bin[] =
{
    0b0111111,
    0b0001010,
    0b1110101,
    0b1001111,
    0b1101010,
    0b1100111,
    0b1110111,
    0b0001011,
    0b1111111,
    0b1101011
}; 

int main(void)
{
	char test[] = "";
	printf("%d", test[0] == 0);

	return 0;
}
