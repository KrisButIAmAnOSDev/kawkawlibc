#include "inttypes.h"
#include "stdio.h"
#include "stdint.h"

int main(void)
{
    int32_t a = 1225;
    uint64_t b = 1234567890;
    int64_t c = -69;
    uint8_t d = 64;

    printf("PRId32: %" PRId32 "\n", a);
    printf("PRIu64: %" PRIu64 "\n", b);
    printf("PRId64: %" PRId64 "\n", c);
    printf("PRIu8: %" PRIu8 "\n", d);
    printf("PRIx64: %" PRIx64 "\n", b);
    printf("PRIu32: %" PRIu32 "\n", a);
    printf("PRId8: %" PRId8 "\n", (int8_t)d);
    printf("PRIx32: %" PRIx32 "\n", (uint32_t)a);

    int32_t vals[] = {1225, 69, 64, 1234567890};
    for (int i = 0; i < 4; i++) {
        printf("inttypes val[%d]: %" PRId32 " (0x%" PRIx32 ")\n", i, vals[i], (uint32_t)vals[i]);
    }

    printf("inttypes: all format specifiers worked\n");
    return 0;
}
