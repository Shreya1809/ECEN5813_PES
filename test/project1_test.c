#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdint.h>

#include "memory.h"
#include "conversion.h"
#include "circbuf.h"

#define BASE_16 (16)
#define BASE_10 (10)

#define DATA_SET_SIZE_W (10)
#define MEM_SET_SIZE_B  (32)
#define MEM_SET_SIZE_W  (8)
#define MEM_ZERO_LENGTH (16)

#define TEST_MEMMOVE_LENGTH (16)


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

static void test_memmove1(void **state) {
    uint8_t i;
    uint8_t * set;
    uint8_t * ptra;
    uint8_t * ptrb;

    set = (uint8_t*) reserve_words( MEM_SET_SIZE_W );

    assert_non_null(set);

    ptra = &set[0];
    ptrb = &set[16];

    /* Initialize the set to test values */
    for( i = 0; i < MEM_SET_SIZE_B; i++)
    {
        set[i] = i;
    }

    my_memmove(ptra, ptrb, TEST_MEMMOVE_LENGTH);

    for (i = 0; i < TEST_MEMMOVE_LENGTH; i++)
    {
        assert_int_equal(set[i + 16], i);
    }
    free_words( (uint32_t*)set );
}

static void test_memmove2(void **state){
  uint8_t i;
  uint8_t * set;
  uint8_t * ptra;
  uint8_t * ptrb;

  set = (uint8_t*) reserve_words(MEM_SET_SIZE_W);

  assert_non_null(set);
  ptra = &set[0];
  ptrb = &set[8];

  /* Initialize the set to test values */
  for( i = 0; i < MEM_SET_SIZE_B; i++) {
    set[i] = i;
  }

  my_memmove(ptra, ptrb, TEST_MEMMOVE_LENGTH);

  for (i = 0; i < TEST_MEMMOVE_LENGTH; i++)
  {
      assert_int_equal(set[i + 8],i);
  }

  free_words( (uint32_t*)set );
}
static void test_memmove3(void **state){
  uint8_t i;
  uint8_t * set;
  uint8_t * ptra;
  uint8_t * ptrb;

  set = (uint8_t*)reserve_words( MEM_SET_SIZE_W);
  assert_non_null(set);
  ptra = &set[8];
  ptrb = &set[0];

  /* Initialize the set to test values */
  for( i = 0; i < MEM_SET_SIZE_B; i++)
  {
    set[i] = i;
  }

  my_memmove(ptra, ptrb, TEST_MEMMOVE_LENGTH);

  for (i = 0; i < TEST_MEMMOVE_LENGTH; i++)
  {
      assert_int_equal(set[i],i+8);
  }


  free_words( (uint32_t*)set );

}

static void test_memcpy(void **state){
  uint8_t i;
  uint8_t * set;
  uint8_t * ptra;
  uint8_t * ptrb;

  set = (uint8_t*) reserve_words(MEM_SET_SIZE_W);

  assert_non_null(set);
  ptra = &set[0];
  ptrb = &set[16];

  /* Initialize the set to test values */
  for( i = 0; i < MEM_SET_SIZE_B; i++) {
    set[i] = i;
  }

  my_memcpy(ptra, ptrb, TEST_MEMMOVE_LENGTH);

  for (i = 0; i < TEST_MEMMOVE_LENGTH; i++)
  {
        assert_int_equal(set[i + 16], i);
  }

  free_words( (uint32_t*)set );
}

static void test_memset(void **state){
  uint8_t i;
  uint8_t * set;
  uint8_t * ptra;
  uint8_t * ptrb;

  set = (uint8_t*)reserve_words(MEM_SET_SIZE_W);
  assert_non_null(set);
  ptra = &set[0];
  ptrb = &set[16];

  /* Initialize the set to test values */
  for( i = 0; i < MEM_SET_SIZE_B; i++)
  {
    set[i] = i;
  }

  my_memset(ptra, MEM_SET_SIZE_B, 0xFF);
  my_memzero(ptrb, MEM_ZERO_LENGTH);

  /* Validate Set & Zero Functionality */
  for (i = 0; i < MEM_ZERO_LENGTH; i++)
  {
        assert_int_equal(set[i], 0xFF);
        assert_int_equal(set[i + 16], 0);
  }

  free_words( (uint32_t*)set );
}

static void test_reverse(void **state){
  uint8_t i;
  uint8_t * copy;
  uint8_t set[MEM_SET_SIZE_B] = {0x3F, 0x73, 0x72, 0x33, 0x54, 0x43, 0x72, 0x26,
                                 0x48, 0x63, 0x20, 0x66, 0x6F, 0x00, 0x20, 0x33,
                                 0x72, 0x75, 0x74, 0x78, 0x21, 0x4D, 0x20, 0x40,
                                 0x20, 0x24, 0x7C, 0x20, 0x24, 0x69, 0x68, 0x54
                               };

  copy = (uint8_t*)reserve_words(MEM_SET_SIZE_W);
  assert_non_null(copy);

  my_memcpy(set, copy, MEM_SET_SIZE_B);

  my_reverse(set, MEM_SET_SIZE_B);

  for (i = 0; i < MEM_SET_SIZE_B; i++)
  {
    assert_int_equal(set[i], copy[MEM_SET_SIZE_B - i - 1]);
  }

  free_words( (uint32_t*)copy );
}

static void test_circbuf_init(void **state){
    cb_struct my_cb;

    cb_enum cb_status = cb_init(&my_cb, 100);

    assert_int_equal(cb_status, CB_SUCCESS);
}

static void test_circbuf_is_full1(void **state){
    cb_struct my_cb;

    cb_enum cb_status = cb_init(&my_cb, 100);
    assert_int_equal(cb_status, CB_SUCCESS);

    assert_false(cb_is_full(&my_cb));
}

static void test_circbuf_is_full2(void **state){
    cb_struct my_cb;

    cb_enum cb_status = cb_init(&my_cb, 100);
    assert_int_equal(cb_status, CB_SUCCESS);

    cb_status = cb_buffer_add_item(&my_cb, 'a');
    assert_int_equal(cb_status, CB_SUCCESS);

    assert_false(cb_is_full(&my_cb));
}
 static void test_circbuf_destroy(void **state){
     cb_struct my_cb;
    
     cb_enum cb_status = cb_init(&my_cb,100);
     assert_int_equal(cb_status,CB_SUCCESS);
   
     cb_status = cb_destroy(&my_cb);
     assert_int_equal(cb_status, CB_SUCCESS);
 }
static void test_circbuf_empty1(void **state){
    cb_struct my_cb;

    cb_enum cb_status =  cb_init(&my_cb,100);
    assert_int_equal(cb_status, CB_SUCCESS);

    cb_status = cb_buffer_add_item(&my_cb, 'a');
    assert_int_equal(cb_status, CB_SUCCESS);

    assert_false(cb_is_empty(&my_cb));
}

static void test_circbuf_empty2(void **state){
    cb_struct my_cb;

    cb_enum cb_status = cb_init(&my_cb,100);
    assert_int_equal(cb_status, CB_SUCCESS);
    
    cb_status = cb_buffer_add_item(&my_cb, 'a');
    assert_int_equal(cb_status, CB_SUCCESS);

    cb_status = cb_buffer_remove_item(&my_cb,'a');
    assert_int_equal(cb_status,CB_SUCCESS);

    assert_true(cb_is_empty(&my_cb));
}

static void test_circbuf_add_remove(void **state){
    cb_struct my_cb;

    cb_enum cb_status = cb_init(&my_cb,100);
    assert_int_equal(cb_status, CB_SUCCESS);

    cb_status = cb_buffer_add_item(&my_cb, 'a');
    assert_int_equal(cb_status, CB_SUCCESS);

    cb_status = cb_buffer_remove_item(&my_cb,'a');
    assert_int_equal(cb_status,CB_SUCCESS);
	
    assert_int_equal(cb_status,CB_SUCCESS);
 
}

static void test_circbuf_add_item(void **state){
    cb_struct my_cb;

    cb_enum cb_status = cb_init(&my_cb,100);
    assert_int_equal(cb_status, CB_SUCCESS);

    cb_status = cb_buffer_add_item(&my_cb, 'a');
    assert_int_equal(cb_status, CB_SUCCESS);

    cb_status = cb_is_empty(&my_cb);
    assert_int_not_equal(cb_status, CB_EMPTY_ERROR);
}

static void test_circbuf_wrap_add(void **state){
    cb_struct my_cb;
	assert_true(cb_is_empty(&my_cb));

    cb_enum cb_status = cb_init(&my_cb,3);
    assert_int_equal(cb_status, CB_SUCCESS);

    assert_false(cb_is_full(&my_cb));

    cb_status = cb_buffer_add_item(&my_cb, 'a');
    assert_int_equal(cb_status, CB_SUCCESS);

    assert_false(cb_is_full(&my_cb));

    cb_status = cb_buffer_add_item(&my_cb, 'b');
    assert_int_equal(cb_status, CB_SUCCESS);

    assert_false(cb_is_full(&my_cb));

    cb_status = cb_buffer_add_item(&my_cb, 'c');
    assert_int_equal(cb_status, CB_SUCCESS);

    assert_true(cb_is_full(&my_cb));
	
    cb_status = cb_buffer_add_item(&my_cb, 'd');
    assert_int_equal(cb_status, CB_SUCCESS);

    assert_true(cb_is_full(&my_cb));
}

	
int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_data1),
        cmocka_unit_test(test_data2),
        cmocka_unit_test(test_memmove1),
        cmocka_unit_test(test_memmove2),
        cmocka_unit_test(test_memmove3),
        cmocka_unit_test(test_memcpy),
        cmocka_unit_test(test_memset),
        cmocka_unit_test(test_reverse),
        cmocka_unit_test(test_circbuf_init),
        cmocka_unit_test(test_circbuf_is_full1),
        cmocka_unit_test(test_circbuf_is_full2),
        cmocka_unit_test(test_circbuf_destroy),
        cmocka_unit_test(test_circbuf_empty1),
        cmocka_unit_test(test_circbuf_empty2),
	cmocka_unit_test(test_circbuf_add_remove),
	cmocka_unit_test(test_circbuf_add_item),
	cmocka_unit_test(test_circbuf_wrap_add),


    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
