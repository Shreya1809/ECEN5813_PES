/**
 * @file project_test.c
 * @brief CMocka unit tests
 * @author Miles Frain
 * @author Shreya Chakraborty
 * @version 1
 * @date 2018-03-04
 */

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdint.h>

#include "memory.h"
#include "conversion.h"
#include "circbuf.h"
#include "data.h"

#define BASE_16 (16)
#define BASE_10 (10)

#define DATA_SET_SIZE_W (10)
#define MEM_SET_SIZE_B  (32)
#define MEM_SET_SIZE_W  (8)
#define MEM_ZERO_LENGTH (16)
#define MEM_SIZE_EVEN 8
#define MEM_SIZE_ODD 9
#define MEM_SIZE_CHAR 256

#define TEST_MEMMOVE_LENGTH (16)
#define BUFFER_LENGTH    (8)

static void test_itoa_invalid_ptr(void **state) {
 uint8_t * ptr = NULL;
    int32_t num = -4096;
  // ptr = (uint8_t*) reserve_words( DATA_SET_SIZE_W );
   uint32_t digits = my_itoa( num, ptr, BASE_16);
    assert_int_equal(digits,0);
}

static void test_itoa_zero_integer(void **state) {
 uint8_t * ptr;
    int32_t num = 0;
ptr = (uint8_t*) reserve_words( DATA_SET_SIZE_W );

    assert_non_null(ptr);
  // ptr = (uint8_t*) reserve_words( DATA_SET_SIZE_W );
   uint32_t digits = my_itoa( num, ptr, BASE_16);
    assert_int_equal(digits,1);
}

static void test_itoa_max_sized_integer(void **state){
uint8_t * ptr;
    int32_t num = 0;
ptr = (uint8_t*) reserve_words( DATA_SET_SIZE_W );

    assert_non_null(ptr);
  // ptr = (uint8_t*) reserve_words( DATA_SET_SIZE_W );
   uint32_t digits = my_itoa( num, ptr, BASE_16);
    assert_int_equal(digits,1);
}

static void test_atoi_invalid_ptr(void **state) {
 uint8_t * ptr = NULL;
    // int32_t num = -4096;
    uint32_t digits = 5;
    int32_t value;

       // digits = my_itoa( num, ptr, BASE_16);
    value = my_atoi( ptr, digits, BASE_16);
    assert_int_equal(value,0);
}

static void test_atoi_zero_integer(void **state) {
 uint8_t * ptr ;
    // int32_t num = -4096;
    uint32_t digits = 0;
    int32_t value;
ptr = (uint8_t*) reserve_words( DATA_SET_SIZE_W );

    assert_non_null(ptr);

       // digits = my_itoa( num, ptr, BASE_16);
    value = my_atoi( ptr, digits, BASE_16);
    assert_int_equal(value,0);
}

static void test_atoi_max_sized_integer(void **state){
    int32_t value;
	//ptr = (uint8_t*) reserve_words( DATA_SET_SIZE_W );
    //assert_non_null(ptr);
	
    // digits = my_itoa( num, ptr, BASE_16);
    value = my_atoi((uint8_t *)"2147483647", 10, BASE_10);
    assert_int_equal(value,INT32_MAX);			
}

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

static void test_memmove_null_Ptr(void **state ) {
	uint8_t * set = (uint8_t*) malloc(MEM_SIZE_EVEN*sizeof(uint8_t));
	uint8_t * source= &set[0];	
	uint8_t * dest= NULL;	//Pass a NULL destination pointer
	uint8_t * status = NULL;
	status = my_memmove(source,dest,(MEM_SIZE_EVEN/2));
	//check whether the pointer returned is NULL
	assert_ptr_equal(cast_ptr_to_largest_integral_type(status),NULL);	
}

static void test_memmove_no_overlap(void **state) {
	uint8_t * set = (uint8_t*) malloc(MEM_SIZE_EVEN*sizeof(uint8_t));
	uint8_t * source= &set[0];
	uint8_t * dest= &set[(MEM_SIZE_EVEN/2)];
	uint8_t * status = NULL;
	//Initialize the memory to test values
	for (uint8_t i=0; i<(MEM_SIZE_EVEN/2); i++) 
		set[i]=i;
	status = my_memmove(source,dest,(MEM_SIZE_EVEN/2));
	for (uint8_t i=0; i<(MEM_SIZE_EVEN/2); i++) {
		//Check each of the 5 values against the source
		assert_int_equal(i,*(status+i));	
	}	
}


static void test_memmove_src_in_dst(void **state) {
	uint8_t * set = (uint8_t*) malloc(MEM_SIZE_EVEN*sizeof(uint8_t));
	uint8_t * source= &set[0];
	uint8_t * dest= &set[2];
	uint8_t * status = NULL;
	//Initialize the memory to test values
	for (uint8_t i=0; i<(MEM_SIZE_EVEN/2); i++) 
		set[i]=i;
	status = my_memmove(source,dest,(MEM_SIZE_EVEN/2));
	for (uint8_t i=0; i<(MEM_SIZE_EVEN/2); i++) {
		//Check each of the 5 values against the source
		assert_int_equal(i,*(status+i));	
	}	
}

static void test_memmove_dst_in_src(void **state) {
	uint8_t * set = (uint8_t*) malloc(MEM_SIZE_EVEN*sizeof(uint8_t));
	uint8_t * source= &set[2];
	uint8_t * dest= &set[0];
	uint8_t * status = NULL;
	//Initialize the memory to test values
	for (uint8_t i=0; i<(MEM_SIZE_EVEN/2); i++) 
		set[i+2]=i;
	status = my_memmove(source,dest,(MEM_SIZE_EVEN/2));
	for (uint8_t i=0; i<(MEM_SIZE_EVEN/2); i++) {
		//Check each of the 5 values against the source
		assert_int_equal(i,*(status+i));	
	}	
}

static void test_memmove_dst_equal_src(void **state) {
	uint8_t * set = (uint8_t*) malloc(MEM_SIZE_EVEN*sizeof(uint8_t));
	uint8_t * source= &set[0];
	uint8_t * dest= &set[0];
	uint8_t * status = NULL;
	//Initialize the memory to test values
	for (uint8_t i=0; i<(MEM_SIZE_EVEN/2); i++) 
		set[i]=i;
	status = my_memmove(source,dest,(MEM_SIZE_EVEN/2));
	for (uint8_t i=0; i<(MEM_SIZE_EVEN/2); i++) {
		//Check each of the 5 values against the source
		assert_int_equal(*(status+i),i);	
	}	
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

static void test_big_to_little_valid_Ptr(void **state) {
	uint32_t * data = NULL;
	//uint32_t length =4;
	int8_t status =  big_to_little(data); //check for null pointer
	assert_int_equal(status,1); //status = 1 , null pointer passed
}

static void test_big_to_little_valid_Conv(void **state) {
	int8_t status;
	uint32_t data = {0x9ABCDEF0};
	//uint32_t length = sizeof(data);	
	uint32_t * temp = (uint32_t *)malloc(sizeof(uint32_t)); // temp variable to store original copy 
	my_memcpy((uint8_t*)&data,(uint8_t*)temp,4); //length*4);
	status =  big_to_little(&data);
	assert_int_equal(status,0);
	for(int8_t i =0; i<2;i++)
{
	assert_int_equal(*(((uint8_t *)temp)+i),*(((uint8_t *)&data)+3-i)); //checking byte wise for data conversion
}
	
}

static void test_little_to_big_valid_Ptr(void **state) {
	//uint32_t length =4;
	uint32_t * data = NULL;
	int8_t status =  little_to_big(data);
	assert_int_equal(status,1); // return value is 1 if null pointer is passed
}

static void test_little_to_big_valid_Conv(void **state) {
	int8_t status;
	uint32_t data = {0x9ABCDEF0};
	//uint32_t length = sizeof(data);	
	uint32_t * temp = (uint32_t *)malloc(sizeof(uint32_t)); // temp variable to store original copy 
	my_memcpy((uint8_t*)&data,(uint8_t*)temp,4); //length*4);
	status =  big_to_little(&data);
	assert_int_equal(status,0);
	for(int8_t i =0; i<2;i++)
{
	assert_int_equal(*(((uint8_t *)temp)+i),*(((uint8_t *)&data)+3-i)); //checking byte wise for data conversion
}
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

static void test_circbuf_full(void **state){
cb_struct *ptr = (cb_struct*)malloc(sizeof(cb_struct));
    cb_enum cb_status = cb_init(ptr,BUFFER_LENGTH);
    assert_int_equal(cb_status, CB_SUCCESS);
for (uint8_t i=0; i<BUFFER_LENGTH; i++) 
	{
	cb_status = cb_buffer_add_item(ptr,i);
	assert_int_equal(cb_status,CB_SUCCESS);
	}
	assert_int_equal(cb_is_full(ptr),1);//check if buffer full true
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
    int8_t j;

    cb_enum cb_status = cb_init(&my_cb,100);
    assert_int_equal(cb_status, CB_SUCCESS);
    
    cb_status = cb_buffer_add_item(&my_cb, 'a');
    assert_int_equal(cb_status, CB_SUCCESS);

    cb_status = cb_buffer_remove_item(&my_cb, &j);
    assert_int_equal(cb_status,CB_SUCCESS);

    assert_true(cb_is_empty(&my_cb));
}

static void test_circbuf_empty(void **state){
cb_struct *ptr = (cb_struct*)malloc(sizeof(cb_struct));
       cb_enum cb_status = cb_init(ptr,BUFFER_LENGTH);
    assert_int_equal(cb_status, CB_SUCCESS);
    assert_int_equal(cb_is_empty(ptr),1);
}

static void test_circbuf_add_remove(void **state){
    cb_struct my_cb;
    int8_t j;
    cb_enum cb_status = cb_init(&my_cb,BUFFER_LENGTH);
    assert_int_equal(cb_status, CB_SUCCESS);

for (uint8_t i=0; i<BUFFER_LENGTH+2; i++) 
	{
	cb_status = cb_buffer_add_item(&my_cb,i);
	cb_status = cb_buffer_remove_item(&my_cb, &j);
	assert_int_equal(i,(uint8_t)j);
	}
	
    assert_int_equal(cb_status,CB_SUCCESS);
 
}

static void test_circbuf_add_item(void **state){
    cb_struct my_cb;

    cb_enum cb_status = cb_init(&my_cb,100);
    assert_int_equal(cb_status, CB_SUCCESS);

    cb_status = cb_buffer_add_item(&my_cb, 'a');
    assert_int_equal(cb_status, CB_SUCCESS);

    cb_status = cb_is_empty(&my_cb);
    assert_false(cb_status);
}


static void test_circbuf_wrap_add(void **state){
    //cb_struct my_cb;
    cb_struct *ptr = (cb_struct*)malloc(sizeof(cb_struct));
    int8_t j;
    cb_enum cb_status = cb_init(ptr,BUFFER_LENGTH);
    assert_int_equal(cb_status, CB_SUCCESS);
for (uint8_t i=0; i<BUFFER_LENGTH; i++) 
	{
	cb_status = cb_buffer_add_item(ptr,i);
	assert_int_equal(cb_status,CB_SUCCESS);
	}
	
cb_status = cb_buffer_remove_item(ptr, &j); //remove first item
cb_status = cb_buffer_add_item(ptr,j);//add it again to the end for wrap add
assert_ptr_equal((ptr->head),(ptr->tail)-1);
}

static void test_circbuf_wrap_remove(void **state){
 cb_struct *ptr = (cb_struct*)malloc(sizeof(cb_struct));
    int8_t j;
    cb_enum cb_status = cb_init(ptr,BUFFER_LENGTH);
    assert_int_equal(cb_status, CB_SUCCESS);
for (uint8_t i=0; i<BUFFER_LENGTH; i++) 
	{
	cb_status = cb_buffer_add_item(ptr,i);
	assert_int_equal(cb_status,CB_SUCCESS);
	}
for (uint8_t i=0; i<BUFFER_LENGTH; i++) 
	{
	cb_status = cb_buffer_remove_item(ptr,&j);
	assert_int_equal(cb_status,CB_SUCCESS);
	}	
assert_ptr_equal((ptr->head),(ptr->tail));
}

static void test_circbuf_overfill(void **state){
 cb_struct *ptr = (cb_struct*)malloc(sizeof(cb_struct));
    //int8_t j;
    cb_enum cb_status = cb_init(ptr,BUFFER_LENGTH);
    assert_int_equal(cb_status, CB_SUCCESS);
for (uint8_t i=0; i<BUFFER_LENGTH; i++) 
	{
	cb_status = cb_buffer_add_item(ptr,i);
	assert_int_equal(cb_status,CB_SUCCESS);
	}
cb_status = cb_buffer_add_item(ptr,(uint8_t)0 );
    assert_int_equal(cb_status, CB_FULL_ERROR);
}

static void test_circbuf_overempty(void **state){
cb_struct *ptr = (cb_struct*)malloc(sizeof(cb_struct));
    int8_t j;
    cb_enum cb_status = cb_init(ptr,BUFFER_LENGTH);
    assert_int_equal(cb_status, CB_SUCCESS);
//remove item from empty buffer
cb_status = cb_buffer_remove_item(ptr,&j);
	assert_int_equal(cb_status,CB_EMPTY_ERROR);
}

static void test_circbuf_allocate_free(void **state){
cb_struct *ptr = (cb_struct*)malloc(sizeof(cb_struct));
    //int8_t j;
    cb_enum cb_status = cb_init(ptr,BUFFER_LENGTH);//allocate
    assert_int_equal(cb_status, CB_SUCCESS);
cb_status = cb_destroy(ptr);//free
     assert_int_equal(cb_status, CB_SUCCESS);
}

static void test_circbuf_invalid_ptr(void **state){
cb_struct *ptr = (cb_struct*)malloc(sizeof(cb_struct));
    //int8_t j;
    cb_enum cb_status = cb_init(ptr,BUFFER_LENGTH);//allocate
    assert_int_equal(cb_status, CB_SUCCESS);
    assert_ptr_not_equal(ptr->buffer, NULL);
}
static void test_circbuf_initialised(void **state){
cb_struct *ptr = (cb_struct*)malloc(sizeof(cb_struct));
    int8_t j;
    cb_enum cb_status = cb_init(ptr,BUFFER_LENGTH);//allocate
    assert_int_equal(cb_status, CB_SUCCESS);
    for(j=0;j<BUFFER_LENGTH;j++)
    assert_int_equal(*((ptr->buffer)+j),0);
}

static void test_reverse_null_Ptr(void **state) {
	uint8_t * array= NULL;
	uint8_t * status = NULL;
	status = my_reverse(array,MEM_SIZE_EVEN);
	assert_ptr_equal(cast_ptr_to_largest_integral_type(status),NULL);
}

static void test_reverse_odd(void **state) {
	uint8_t array[MEM_SIZE_ODD]= {10,11,12,13,14,15,16,17,18};
	uint8_t *temp =(uint8_t *)malloc(MEM_SIZE_ODD*sizeof(uint8_t));
	temp = my_memcpy(array,temp,MEM_SIZE_ODD);
	uint8_t * status = NULL;
	status = my_reverse(array,MEM_SIZE_ODD);
	for (uint8_t i=0;i<MEM_SIZE_ODD;i++)
	{	
		assert_int_equal(temp[MEM_SIZE_ODD-1-i],status[i]);
	}
}

static void test_reverse_even(void **state) {
	uint8_t array[MEM_SIZE_EVEN]= {10,11,12,13,14,15,16,17};
	uint8_t *temp =(uint8_t *)malloc(MEM_SIZE_EVEN*sizeof(uint8_t));
	temp = my_memcpy(array,temp,MEM_SIZE_EVEN);
	uint8_t * status = NULL;
	status = my_reverse(array,MEM_SIZE_EVEN);
	for (uint8_t i=0;i<MEM_SIZE_EVEN;i++)
	{	
		assert_int_equal(temp[MEM_SIZE_EVEN-1-i],status[i]);
	}
}	

static void test_reverse_char(void **state) {
	char a[MEM_SIZE_CHAR];
	for (uint16_t i=0; i<MEM_SIZE_CHAR; i++)  
		a[i]=(char)i;
	uint8_t * status = NULL;
	status = my_reverse((uint8_t *)a,MEM_SIZE_CHAR);
	for (uint16_t i=0;i<MEM_SIZE_CHAR;i++) 
		assert_int_equal(MEM_SIZE_CHAR-i-1,status[i]);
}

static void test_memzero_null_Ptr(void **state) {
	uint8_t * set = NULL;
	uint8_t * status = NULL;
	status = my_memzero(set,MEM_SIZE_EVEN);
	assert_ptr_equal(cast_ptr_to_largest_integral_type(status),NULL);
}

static void test_memzero_check_set(void **state) {
	uint8_t * set = (uint8_t *)malloc(MEM_SIZE_EVEN*sizeof(uint8_t));
	uint8_t * status = NULL;
	status = my_memzero(set,MEM_SIZE_EVEN);
	for (uint8_t i=0; i<MEM_SIZE_EVEN; i++)
		assert_int_equal(0,*(status+i));
}

static void test_memset_null_Ptr(void **state) {
	uint8_t * set = NULL;
	uint8_t * status = NULL;
	uint8_t data = 10;
	status = my_memset(set,MEM_SIZE_EVEN,data);
	assert_ptr_equal(cast_ptr_to_largest_integral_type(status),NULL);
}
static void test_memset_check_set(void **state) {
	uint8_t * set = (uint8_t *)malloc(MEM_SIZE_EVEN*sizeof(uint8_t));
	uint8_t * status = NULL;
	uint8_t data = 10;
	status = my_memset(set,MEM_SIZE_EVEN,data);
	for (uint8_t i=0; i<MEM_SIZE_EVEN; i++)
		assert_int_equal(data,*(status+i));
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_data1),
        cmocka_unit_test(test_data2),
	cmocka_unit_test(test_itoa_max_sized_integer),
	cmocka_unit_test(test_atoi_max_sized_integer),
        cmocka_unit_test(test_memmove1),
        cmocka_unit_test(test_memmove2),
        cmocka_unit_test(test_memmove3),
	cmocka_unit_test(test_memmove_null_Ptr),
	cmocka_unit_test(test_memmove_no_overlap),
	cmocka_unit_test(test_memmove_src_in_dst),
	cmocka_unit_test(test_memmove_dst_in_src),
	cmocka_unit_test(test_memmove_dst_equal_src),
	cmocka_unit_test(test_memzero_null_Ptr),
	cmocka_unit_test(test_memzero_check_set),
        cmocka_unit_test(test_memcpy),
        cmocka_unit_test(test_memset),
	cmocka_unit_test(test_memset_null_Ptr),
	cmocka_unit_test(test_memset_check_set),
        cmocka_unit_test(test_reverse),
	cmocka_unit_test(test_reverse_null_Ptr),
	cmocka_unit_test(test_reverse_odd),
	cmocka_unit_test(test_reverse_even),
	cmocka_unit_test(test_reverse_char),
	cmocka_unit_test(test_big_to_little_valid_Ptr),
 	cmocka_unit_test(test_big_to_little_valid_Conv),
	cmocka_unit_test(test_little_to_big_valid_Ptr),
	cmocka_unit_test(test_little_to_big_valid_Conv),
        cmocka_unit_test(test_circbuf_init),
        cmocka_unit_test(test_circbuf_is_full1),
        cmocka_unit_test(test_circbuf_is_full2),
        cmocka_unit_test(test_circbuf_destroy),
        cmocka_unit_test(test_circbuf_empty1),
        cmocka_unit_test(test_circbuf_empty2),
	cmocka_unit_test(test_circbuf_add_remove),
	cmocka_unit_test(test_circbuf_add_item),
	cmocka_unit_test(test_circbuf_wrap_add),
        cmocka_unit_test(test_circbuf_wrap_remove),
	cmocka_unit_test(test_circbuf_overfill),
	cmocka_unit_test(test_circbuf_overempty),
	cmocka_unit_test(test_circbuf_allocate_free),
	cmocka_unit_test(test_circbuf_invalid_ptr),
	cmocka_unit_test(test_circbuf_full),
	cmocka_unit_test(test_circbuf_initialised),
	cmocka_unit_test(test_circbuf_empty),
	cmocka_unit_test(test_itoa_invalid_ptr),
	cmocka_unit_test(test_atoi_invalid_ptr),
	cmocka_unit_test(test_itoa_zero_integer),
	cmocka_unit_test(test_atoi_zero_integer)


    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
