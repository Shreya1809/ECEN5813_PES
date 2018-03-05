/**
 * @file arch_arm32.h
 *
 * @brief source file for arch_arm.c
 *
 * header files for arch_arm32.h for the following function
 * - ARM32_AIRCR_get_endianness_setting
 *
 * @author Miles Frain
 * @author Shreya Chakraborty
 * @version 1
 * @date 2018-02-10
 */

#include <stdint.h>

#define __SCB_ADDRESS			0xE000ED00
#define __AIRCR_ADDRESS_OFFSET	        0xC
#define __AIRCR		*(uint32_t *)(__SCB_ADDRESS+__AIRCR_ADDRESS_OFFSET)
#define __AIRCR_ENDIANNESS_OFFSET	(15)
#define __AIRCR_ENDIANNESS_MASK	(1<<__AIRCR_ENDIANNESS_OFFSET)
#define __CPUID_ADDRESS_OFFSET (0x00)
#define __CPUID (__SCB_ADDRESS + __CPUID_ADDRESS_OFFSET )
#define __CPUID_PART_NO_OFFSET (4)
#define __CPUID_PART_NO_MASK   (0xFFF0)
#define CPUID    ((uint32_t*)__CPUID)
#define __CCR_ADDRESS_OFFSET (0x14)
#define __CCR (__SCB_ADDRESS + __CCR_ADDRESS_OFFSET )
#define CCR ((uint32_t*)__CCR)
#define __CCR_STK_ALIGNMENT_OFFSET (9)
#define __CCR_STK_ALIGNMENT_MASK   (0x200)
#define __CCR_UNALIGNED_ACCESS_TRAP_OFFSET (3)
#define __CCR_UNALIGNED_ACCESS_TRAP_MASK   (0x8)
#define __CCR_DIVIDE_BY_ZERO_TRAP_OFFSET (4)
#define __CCR_DIVIDE_BY_ZERO_TRAP_MASK   (0x10)


__attribute__((always_inline)) uint32_t ARM32_CCR_get_stack_alignment()
{
    return (uint32_t)(((*CCR)&(__CCR_STK_ALIGNMENT_MASK))>>(__CCR_STK_ALIGNMENT_OFFSET));
}

__attribute__((always_inline)) uint32_t ARM32_CPUID_get_part_number()
{
    return (uint32_t)(((*CPUID)&(__CPUID_PART_NO_MASK))>>(__CPUID_PART_NO_OFFSET));
}

__attribute__((always_inline)) uint32_t ARM32_CCR_enable_divide_by_zero_trap()
{
    CCR |= (1)<<__CCR_DIVIDE_BY_ZERO_TRAP_OFFSET;
}

__attribute__((always_inline)) uint32_t ARM32_CCR_enable_unaligned_access_trap()
{
    CCR |= (1)<<__CCR_STK_ALIGNMENT_OFFSET;
}

static inline void ARM32_create_unaligned_access_trap()
{
    /* Perform an unaligned read/access */
    uint32_t data[2];
    uint32_t element = *((uint32_t*)(((uint8_t*)data) + 1))
}

static inline void ARM32_create_divide_by_zero_trap()
{
    uint8_t div = 1;
    div = div/0;
}
__attribute__((always_inline)) uint32_t ARM32_AIRCR_get_endianness_setting()
{
	return ((__AIRCR & __AIRCR_ENDIANNESS_MASK)>>__AIRCR_ENDIANNESS_OFFSET);
}

//__attribute__((always_inline)) uint32_t ARM32_AIRCR_get_endianness_setting();
