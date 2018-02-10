#define __SCB_ADDRESS			0xE000ED00
#define __AIRCR_ADDRESS_OFFSET	        0xC
#define __AIRCR		*(uint32_t *)(__SCB_ADDRESS+__AIRCR_ADDRESS_OFFSET)
#define __AIRCR_ENDIANNESS_OFFSET	(15)
#define __AIRCR_ENDIANNESS_MASK	(1<<__AIRCR_ENDIANNESS_OFFSET)

__attribute__((always_inline)) uint32_t ARM32_AIRCR_get_endianness_setting()
{
	return ((__AIRCR & __AIRCR_ENDIANNESS_MASK)>>__AIRCR_ENDIANNESS_OFFSET);
}
