#include <windows.h>
#include <intrin.h>

#define RAND_SEED (__COUNTER__ * 1234567 + __LINE__)
#define RND(min, max) (min + (RAND_SEED % (max - min + 1)))

#define JUNK_BODY() do {                          \
    volatile int a = RND(100, 999);              \
    volatile int b = RND(100, 999);              \
    volatile int c = RND(1, 50);                 \
                                                   \
    for (int i = 0; i < RND(5, 25); ++i) {        \
        a ^= (b + i);                              \
        b += (a * i) ^ (c + 31);                   \
        c ^= (a | b);                              \
        b = (b << 1) | (b >> 3);                   \
        a ^= (c << 2);                             \
    }                                              \
                                                   \
    if ((a & 1) == 0) {                            \
        b ^= (a << 1);                             \
    } else {                                       \
        a ^= (b >> 1);                             \
    }                                              \
                                                   \
    for (int i = 0; i < RND(5,15); ++i) {          \
        _mm_pause();                               \
        __nop();                                   \
    }                                              \
} while(0)

#define CREATESECTION(name) \
__pragma(code_seg("." #name)) \
__declspec(noinline) void name() { JUNK_BODY(); } \
__pragma(code_seg())

CREATESECTION(vmp0) 
CREATESECTION(vmp1)
CREATESECTION(enigma1)
CREATESECTION(enigma2)
CREATESECTION(themida)
CREATESECTION(junkx)

int main()
{
    vmp0();
    vmp1();
    enigma1();
    enigma2();
    themida();
    junkx();

    return 0;
}
