/*#############################################################
 *     File Name	: rlc_demo.c
 *     Author		: winddoing
 *     Created Time	: Tue Apr 16 20:49:48 2019
 *     Description	:
 *############################################################*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

static char* itoa(int value, char* result, int base) {
    // check that the base if valid
    if (base < 2 || base > 36) { *result = '\0'; return result; }

    char* ptr = result, *ptr1 = result, tmp_char;
    int tmp_value;

    do {
        tmp_value = value;
        value /= base;
        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz"[35 + (tmp_value - value * base)];
    } while ( value );

    // Apply negative sign
    if (tmp_value < 0) *ptr++ = '-';
    *ptr-- = '\0';
    while(ptr1 < ptr) {
        tmp_char = *ptr;
        *ptr--= *ptr1;
        *ptr1++ = tmp_char;
    }
    return result;
}

static int rlc_encoding(uint8_t *original, uint32_t len, uint8_t *compress)
{
    int i = 0;
    int ii = 0;
    int count = 1;

    if (len < 0)
        return -1;

    compress[ii] = original[0];

    for (i = 1; i < len; i++) {
        if (original[i] == original[i - 1]) {
            count++;
        } else {
            itoa(count, &compress[++ii], 10);
            compress[++ii] = original[i];
            count = 1;
        }
    }
    //sprintf(&compress[++ii], "%d", count);
    itoa(count, &compress[++ii], 10);

    return 0;
}

static int rlc_decoding(uint8_t *compress, uint32_t len, uint8_t *original)
{
    int i = 0;
    int ii = -1;

    if (len < 0)
        return -1;

    for (i = 0; i < len; i += 2) {
        int cnt = atoi(&compress[i + 1]);
        while(cnt--) {
            original[++ii] = compress[i];
        }
    }

    return 0;
}

int main(int argc, const char *argv[])
{
    uint8_t str[] = "aaaasdassssssddwwwwwwffffjksdfsd";
    uint8_t cmp_str[100];
    uint8_t org_str[100];


    memset(cmp_str, 0, 100 * sizeof(uint8_t));
    memset(org_str, 0, 100 * sizeof(uint8_t));

    printf("int str: %s\n", str);
    rlc_encoding(str, strlen(str), cmp_str);
    printf("cmp str: %s\n", cmp_str);
    rlc_decoding(cmp_str, strlen(cmp_str), org_str);
    printf("org str: %s\n", org_str);

    return 0;
}
