#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <limits.h>

#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define for_endian(size) for (int i = 0; i < size; ++i)
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define for_endian(size) for (int i = size - 1; i >= 0; --i)
#else
#error "No se detecto el tipo de Endian"
#endif

#define printb(value)                                   \
({                                                      \
        typeof(value) _v = value;                       \
        __printb((typeof(_v) *) &_v, sizeof(_v));       \
})

#define MSB_MASK 1 << (CHAR_BIT - 1)

void __printb(void *value, size_t size)
{
        unsigned char uc;
        unsigned char bits[CHAR_BIT + 1];

        bits[CHAR_BIT] = '\0';
        for_endian(size) {
                uc = ((unsigned char *) value)[i];
                memset(bits, '0', CHAR_BIT);
                for (int j = 0; uc && j < CHAR_BIT; ++j) {
                        if (uc & MSB_MASK)
                                bits[j] = '1';
                        uc <<= 1;
                }
                printf("%s ", bits);
        }
}

int main() {
    float a;
    printf("Ingrese el numero a convertir: ");
    scanf("%f", &a);
    unsigned char *p = (unsigned char *)&a;
    int i;

    printf("a = ");
    for (i = sizeof(a)-1; i >= 0; --i)
    {
        printb(p[i]);
    }
    printf("\n");
    return 0;
}