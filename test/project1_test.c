#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdint.h>

#include "memory.h"
#include "conversion.h"

#define BASE_16 (16)
#define BASE_10 (10)

#define DATA_SET_SIZE_W (10)
#define MEM_SET_SIZE_B  (32)
#define MEM_SET_SIZE_W  (8)
#define MEM_ZERO_LENGTH (16)


static void test_data1(void **state) {
    (void) state; /* unused */

    uint8_t * ptr;
    int32_t num = -4096;
    uint32_t digits;
    int32_t value;

    ptr = (uint8_t*) reserve_words( DATA_SET_SIZE_W );

    assert_non_null(ptr);

    digits = my_itoa( num, ptr, BASE_16);
    value = my_atoi( ptr, digits, BASE_16);
    free_words( (uint32_t*)ptr );

    assert_int_equal(value, num);
}

static void test_data2(void **state) {
    uint8_t * ptr;
    int32_t num = 123456;
    uint32_t digits;
    int32_t value;

    ptr = (uint8_t*) reserve_words( DATA_SET_SIZE_W );

    assert_non_null(ptr);

    digits = my_itoa( num, ptr, BASE_10);
    value = my_atoi( ptr, digits, BASE_10);
    free_words( (uint32_t*)ptr );

    assert_int_equal(value, num);
}


int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_data1),
        cmocka_unit_test(test_data2),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
