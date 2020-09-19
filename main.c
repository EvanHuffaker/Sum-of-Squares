#include "squareSum.h"
#include <limits.h>

int main() {
    unsigned mx = (1u << 16u) - 1u;
    printf("MAX: %u\n", mx);
    printf("Uint max: %u\n", UINT_MAX);
    solve(mx,4);
    return 0;
}
