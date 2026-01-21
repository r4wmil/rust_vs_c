#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#define NANOS_PER_SEC (1000 * 1000 * 1000)

double secs(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
		uint64_t nanos = (NANOS_PER_SEC) * ts.tv_sec + ts.tv_nsec;
    return (double)nanos / (NANOS_PER_SEC);
}

typedef struct uintn_t {
	uint64_t* buf;
	size_t len;
} uintn_t;

#define MAX(_a, _b) ((_b) < (_a) ? (_a) : (_b))

void uintn_add(uintn_t* dst, uintn_t* src) {
	__uint128_t carry = 0;
	for (size_t i = 0; i < dst->len; i++) {
		carry += src->buf[i];
		carry += dst->buf[i];
		dst->buf[i] = carry;
		carry >>= 64;
	}
	if (carry) { dst->buf[dst->len++] = 1; }
}

void uintn_print(uintn_t* n) {
	for (size_t i = n->len - 1; i != (size_t)-1; i--) {
		printf("%016lx'", n->buf[i]);
	}
	printf("\n");
}

int main() {
	double start = secs();
	uintn_t a = {0};
	uintn_t b = {0};
	for (uint64_t n = 0; n < 10000; n++) {
		a.buf = calloc(4 * 1024, sizeof(uint64_t));
		b.buf = calloc(4 * 1024, sizeof(uint64_t));
		a.len = 1;
		b.buf[0] = 1;
		b.len = 1;
		for (uint64_t i = 0; i < n; i++) {
			uintn_t tmp = a;
			a = b;
			b = tmp;
			uintn_add(&b, &a);
		}
		(void)b.buf[0];
	}
	printf("%lfs\n", secs() - start);
	//uintn_print(&b);
	return 0;
}
