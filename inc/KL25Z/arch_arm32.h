/************************************************************
Authors:
 Miles Frain & Shreya Chakraborty
Description:
 header files for arch_arm32.h for the following function
- ARM32_AIRCR_get_endianness_setting
**************************************************************/

#define __SCB_ADDRESS			x 
#define __AIRCR_ADDRESS_OFFSET	 0xE000ED0C
#define __AIRCR		*(uint32_t *)(__SCB_ADDRESS+__AIRCR_ADDRESS_OFFSET)
#define __AIRCR_ENDIANNESS_OFFSET	(15)
#define __AIRCR_ENDIANNESS_MASK	(1<<__AIRCR_ENDIANNESS_OFFSET)

__attribute__((always_inline)) uint32_t ARM32_AIRCR_get_endianness_setting();
