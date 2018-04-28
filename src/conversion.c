/**
 * @file conversion.c
 * @brief source files for conversion.c functions
 * @author Miles Frain
 * @author Shreya Chakraborty
 * @version 1
 * @date 2018-02-10
 */

#include "conversion.h"
#include "memory.h"

/*function to convert data back from ascii to integer*/
int32_t my_atoi(uint8_t *ptr, uint8_t digits, uint32_t base)
{
    int32_t sign = 0, i = 0, result = 0;
    
    if (ptr != NULL && digits >= 0 && base != 0)
    {
	if(*ptr == '-')
    {
        sign = 1; //set sign flag
        i++;
    }
        while((*(ptr+i)!= '\0') && (i < digits))
        {
            if((*(ptr+i)>= '0') && (*(ptr+i) <= '9')) //if the character is within 0 to 9
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
uint8_t  my_itoa(int32_t data, uint8_t *ptr, uint32_t base)
{
    uint32_t sign = 0, i = 0, remainder = 0; // flag for sign
    uint8_t length = 0;


    if (data < 0) //data is negative
    {
        data = data * -1; // takes the absolute value of data
        sign = 1; // set sign flag
    }
    if (ptr != 0 && data > 0 && base != 0)
    {
        while(data)
        {
            remainder = data % base; //stores the remainder
            *(ptr+i) = (remainder > 9)?(remainder -10) + 'A' : remainder + '0';
            data = data/base; //stores the quotient
            i++;length++;
        }
        if(sign == 1){
            *(ptr+i) = 45; //ascii of '-' is 45
            i++; length++;
        }
        // the reversal of string to get the final ouput as the loop gives us values from the last ie from lsb
        ptr = my_reverse(ptr,length);
        *(ptr+i) ='\0'; //null character for the end of string
        //return length;//returns length of array
    }
    else if(data == 0)
{
	remainder = data % base; //stores the remainder
            *(ptr+i) = (remainder > 9)?(remainder -10) + 'A' : remainder + '0';
            data = data/base; //stores the quotient
            i++;length++;
}
    return length;
}

uint8_t * My_itoa(int32_t data, uint8_t *ptr, uint32_t base)
{
    uint32_t sign = 0, i = 0, remainder = 0; // flag for sign
    uint8_t length = 0;


    if (data < 0) //data is negative
    {
        data = data * -1; // takes the absolute value of data
        sign = 1; // set sign flag
    }
    if (ptr != 0 && data > 0 && base != 0)
    {
        while(data)
        {
            remainder = data % base; //stores the remainder
            *(ptr+i) = (remainder > 9)?(remainder -10) + 'A' : remainder + '0';
            data = data/base; //stores the quotient
            i++;length++;
        }
        if(sign == 1){
            *(ptr+i) = 45; //ascii of '-' is 45
            i++; length++;
        }
        // the reversal of string to get the final ouput as the loop gives us values from the last ie from lsb
        ptr = my_reverse(ptr,length);
        *(ptr+i) ='\0'; //null character for the end of string
        //return length;//returns length of array
    }
    else if(data == 0)
{
	remainder = data % base; //stores the remainder
            *(ptr+i) = (remainder > 9)?(remainder -10) + 'A' : remainder + '0';
            data = data/base; //stores the quotient
            i++;length++;
}
    return ptr;
}
/*uint8_t * my_ITOA(int32_t data, uint8_t * ptr, uint32_t base)
{
	if(ptr != NULL)
	{
    int32_t i=0;
    int32_t negative=0;
    int remain = 0;
    int l=0;
    char charval,tempVariable;
    uint8_t length;

    if(data == 0)				//checking if data is 0
    {
        *(ptr+i)='0';
        i++;
        *(ptr+i)='\0';
    }

    if ( data<0 && base==10)			//for negative numbers with base 10
    {
        data = data * (-1);
        negative = 1;
    }

    while (data != 0)
    {
        remain = data % base;		//gets the bits seperately using modulus operator
	if(remain <= 9)
	{
		charval = remain +'0';		//for 1 to 9 digits
	}
	else if(remain > 9)
	{
		charval = (remain-10)+'a';	//for hex values 'A' to 'F'
	}
        *(ptr+i) = charval;
        data = data / base;
        i++;
    }

    if(negative)				// for negative number
    {
        *(ptr+i) = '-';
        i++;
    }

    *(ptr+i)='\0';				// adding null character

    length=i;

    i=0;
    if(length%2 == 0)
    {l=length/2;}
    else if (length%2 !=0)
    {l = (length-1)/2;}
    while(i<l)				//swaping the positions of pointers
    {
        tempVariable=*(ptr+i);
        *(ptr+i)=*(ptr+length-i-1);
        *(ptr+length-i-1)=tempVariable;
        i++;
    }
    return ptr;
	}
}*/



