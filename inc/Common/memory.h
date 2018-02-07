/**
 * @file memory.h
 * @brief Custom memory functions
 *
 * - my_memmove
 * - my_memcpy
 * - my_memset
 * - my_memzero
 * - my_reverse
 * - reserve_words
 * - free_words
 *
 * @author Shreya Chakraborty
 * @author Miles Frain
 * @version 1.0
 * @date 2018-02-07
 */

#ifndef __MEMORY_H__
#define __MEMORY_H__

/**
 * @brief Move block of memory
 *
 * Copies a length of bytes from source to destination.
 * Can handle overlaps.
 *
 * @param src Memory pointer of where to copy from
 * @param dst Memory pointer of where to copy to
 * @param length Number of bytes to move
 *
 * @return Memory pointer of destination, NULL if src or dst are NULL
 */
uint8_t *my_memmove(uint8_t *src, uint8_t *dst, size_t length);


/**
 * @brief Copy block of memory
 *
 * Copies a length of bytes from source to destination.
 * Undefined behavior if memory regions overlap.
 *
 * @param src Memory pointer of where to copy from
 * @param dst Memory pointer of where to copy to
 * @param length Number of bytes to copy
 *
 * @return Memory pointer of destination, NULL if src or dst are NULL
 */
uint8_t *my_memcpy(uint8_t *src, uint8_t *dst, size_t length);


/**
 * @brief Sets entire memory block to given value
 *
 * @param src Pointer to memory
 * @param length Size of memory block in bytes
 * @param value Value to write to entire memory block
 *
 * @return Pointer to input memory source
 */
uint8_t *my_memset(uint8_t *src, size_t length, uint8_t value);


/**
 * @brief Sets entire memory block to given zero
 *
 * @param src Pointer to memory
 * @param length Size of memory block in bytes
 *
 * @return Pointer to input memory source
 */
uint8_t *my_memzero(uint8_t *src, size_t length);


/**
 * @brief Reverses order of characters in string
 *
 * @param src Pointer to string
 * @param length Length of string in characters (bytes)
 *
 * @return Pointer to input memory source
 */
uint8_t *my_reverse(uint8_t *src, size_t length);


/**
 * @brief Allocates block of memory
 *
 * @param length Size of memory block to allocate in bytes
 *
 * @return Pointer to allocation, NULL if failure
 */
int32_t *reserve_words(size_t length);


/**
 * @brief Deallocates a block of memory
 *
 * @param src Pointer to memory to deallocate
 *
 * @return 0 if successful, 1 for failure
 */
uint8_t free_words(uint8_t *src);


#endif // __MEMORY_H__
