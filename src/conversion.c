/************************************************************
Authors:
Miles Frain & Shreya Chakraborty
Description:
source files for conversion.c for the following conversion functions
- my_itoa
- my_atoi
 **************************************************************/

#include "conversion.h"
#include "memory.h"

/*function to convert data back from ascii to integer*/
int32_t my_atoi(uint8_t *ptr, uint8_t digits, uint32_t base)
{
    uint32_t sign = 0, i = 0, result = 0;
    if(*ptr == '-')
    {
        sign = 1; //set sign flag
        i++;
    }
    if (*ptr != 0 && digits >= 0 && base != 0)
    {
        while((*(ptr+i)!= '\0') && (i < digits))
        {
            if((*(ptr+i)>= '0') && (*(ptr+i) <=9)) //if the character is within 0 to 9
            {
                result = result * base + *(ptr+i) - 48;
                i++;
            }
            else { //the character is  between A  to F
                result = (result * base) + *(ptr+i) - 55;
                i++;
            }
        }
    }
    if (sign == 1) //if the number is negative
        result = result * -1;
    return result;
}





/*function to convert data from an integer to ascii*/
int32_t my_itoa(int32_t data, uint8_t *ptr, uint32_t base)
{
    uint32_t sign = 0, i = 0, remainder = 0; // flag for sign
    uint8_t length = 0;

    if (data < 0 && base == 10) //data is negative
    {
        data = data * -1; // takes the absolute value of data
        sign = 1; // set sign flag
    }
    if (*ptr != 0 && data >= 0 && base != 0)
    {
        while(data)
        {
            remainder = data % base; //stores the remainder
            *(ptr+i) = (remainder > 9)?(remainder -10) + 'A' : remainder + '0';
            data = data/base; //stores the quotient
            i++;length++;
        }
        if(sign = 1){
            *(ptr+i) = 45; //ascii of '-' is 45
            i++; length++;
        }
        *ptr ='\0'; //null character for the end of string
            // the reversal of string to get the final ouput as the loop gives us values from the last ie from lsb
            ptr = my_reverse(ptr,length);
        return length;//returns length of array
    }
    else return 0;
}



