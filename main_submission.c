#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <locale.h>

union float_32
{
  float floating_value_in_32_bits;
  int floating_value_as_int;
  struct sign_exp_mantissa
  {
    unsigned mantissa : 23;
    unsigned exponent : 8;
    unsigned sign : 1;
  } f_bits;
  struct single_bits
  {
    unsigned b0 : 1;
    unsigned b1 : 1;
    unsigned b2 : 1;
    unsigned b3 : 1;
    unsigned b4 : 1;
    unsigned b5 : 1;
    unsigned b6 : 1;
    unsigned b7 : 1;
    unsigned b8 : 1;
    unsigned b9 : 1;
    unsigned b10 : 1;
    unsigned b11 : 1;
    unsigned b12 : 1;
    unsigned b13 : 1;
    unsigned b14 : 1;
    unsigned b15 : 1;
    unsigned b16 : 1;
    unsigned b17 : 1;
    unsigned b18 : 1;
    unsigned b19 : 1;
    unsigned b20 : 1;
    unsigned b21 : 1;
    unsigned b22 : 1;
    unsigned b23 : 1;
    unsigned b24 : 1;
    unsigned b25 : 1;
    unsigned b26 : 1;
    unsigned b27 : 1;
    unsigned b28 : 1;
    unsigned b29 : 1;
    unsigned b30 : 1;
    unsigned b31 : 1;
  } bit;
};

// convert a union num (float 32 bits) into a bit_string representation
void float_32_to_bitstring(union float_32 num, char bit_string[])
{

  for (int i = 0; i < 42; i++)
  {
    bit_string[i] = ' ';
  }
  bit_string[42] = '\0';

  bit_string[0] = num.bit.b31 ? '1' : '0';

  bit_string[2] = num.bit.b30 ? '1' : '0';
  bit_string[3] = num.bit.b29 ? '1' : '0';
  bit_string[4] = num.bit.b28 ? '1' : '0';
  bit_string[5] = num.bit.b27 ? '1' : '0';

  bit_string[7] = num.bit.b26 ? '1' : '0';
  bit_string[8] = num.bit.b25 ? '1' : '0';
  bit_string[9] = num.bit.b24 ? '1' : '0';
  bit_string[10] = num.bit.b23 ? '1' : '0';

  bit_string[12] = num.bit.b22 ? '1' : '0';
  bit_string[13] = num.bit.b21 ? '1' : '0';
  bit_string[14] = num.bit.b20 ? '1' : '0';

  bit_string[16] = num.bit.b19 ? '1' : '0';
  bit_string[17] = num.bit.b18 ? '1' : '0';
  bit_string[18] = num.bit.b17 ? '1' : '0';
  bit_string[19] = num.bit.b16 ? '1' : '0';

  bit_string[21] = num.bit.b15 ? '1' : '0';
  bit_string[22] = num.bit.b14 ? '1' : '0';
  bit_string[23] = num.bit.b13 ? '1' : '0';
  bit_string[24] = num.bit.b12 ? '1' : '0';

  bit_string[26] = num.bit.b11 ? '1' : '0';
  bit_string[27] = num.bit.b10 ? '1' : '0';
  bit_string[28] = num.bit.b9 ? '1' : '0';
  bit_string[29] = num.bit.b8 ? '1' : '0';

  bit_string[31] = num.bit.b7 ? '1' : '0';
  bit_string[32] = num.bit.b6 ? '1' : '0';
  bit_string[33] = num.bit.b5 ? '1' : '0';
  bit_string[34] = num.bit.b4 ? '1' : '0';

  bit_string[36] = num.bit.b3 ? '1' : '0';
  bit_string[37] = num.bit.b2 ? '1' : '0';
  bit_string[38] = num.bit.b1 ? '1' : '0';
  bit_string[39] = num.bit.b0 ? '1' : '0';
}

// read a 32-bit float into a union and a bit_string array
union float_32 readFloat(char bit_string[])
{
  union float_32 num;
  num.floating_value_as_int = 0;
  scanf("%g", &num.floating_value_in_32_bits);

  float_32_to_bitstring(num, bit_string);

  return num;
}

void printBitsFromInt(unsigned x, int numBits)
{
  printf("%d: ", x);
  for (int i = numBits - 1; i >= 0; --i)
  {
    printf("%d", ((x >> i) & 1));
  }
}
int main(int argc, char *argv[])
{
  char bit_string1[43];
  char bit_string2[43];

  printf("Please enter two positive floating point values each with:\n");
  printf("- no more than 6 significant digits\n");
  printf("- a value between + 10**37 and 10**-37\n");
  printf("Enter Float 1: ");
  union float_32 num1 = readFloat(bit_string1);
  printf("Enter Float 2: ");
  union float_32 num2 = readFloat(bit_string2);

  printf("Original pattern of Float 1: %s\n", bit_string1);
  printf("Original pattern of Float 2: %s\n", bit_string2);

  //***** add num1 and num2 *****//

  // Step 1: put the mantissas into two unsigned integers
  unsigned mantissa1 = 0;
  unsigned mantissa2 = 0;

  for (int i = 0; i < 23; ++i)
  {
    if ((num1.floating_value_as_int >> i) & 1)
      mantissa1 |= (1 << i);
    if ((num2.floating_value_as_int >> i) & 1)
      mantissa2 |= (1 << i);
  }

  mantissa1 |= (1 << 23);
  mantissa2 |= (1 << 23);

  unsigned exponent1 = 0;
  unsigned exponent2 = 0;
  for (int i = 23; i < 31; ++i)
  {
    if ((num1.floating_value_as_int >> i) & 1)
      exponent1 |= (1 << (i - 23));
    if ((num2.floating_value_as_int >> i) & 1)
      exponent2 |= (1 << (i - 23));
  }

  // Step 2: update the two numbers so that they have the same exponent
  while (exponent1 < exponent2)
  {
    exponent1 += 1;
    mantissa1 >>= 1;
  }

  while (exponent2 < exponent1)
  {
    exponent2 += 1;
    mantissa2 >>= 1;
  }

  // Step 3: add two mantissas & update the exponent, then put the result into a 32-bit float union
  unsigned newMantissa = mantissa1 + mantissa2;
  unsigned newExponent = exponent1;
  while (newMantissa >= (1 << 24))
  {
    newMantissa >>= 1;
    newExponent += 1;
  }
  union float_32 result;
  result.floating_value_as_int = 0;
  for (int i = 0; i < 32; ++i)
  {
    if ((newMantissa >> i) & 1)
      result.floating_value_as_int |= (1 << i);
  }

  int isInfinity = 1;
  for (int i = 23; i < 31; ++i)
  {
    if ((newExponent >> (i - 23)) & 1)
    {
      result.floating_value_as_int |= (1 << i);
    }
    else
    {
      isInfinity = 0;
      result.floating_value_as_int &= ~(1 << i);
    }
  }

  // convert to infinity if overflowed
  if (isInfinity)
  {
    for (int i = 0; i < 23; ++i)
    {
      result.floating_value_as_int &= ~(1 << i);
    }
  }

  // Print result
  char bit_string_result[43];
  float_32_to_bitstring(result, bit_string_result);
  printf("Bit pattern of result : %s\n", bit_string_result);
  printf("EMULATED FLOATING RESULT FROM PRINTF ==>>> %g\n", result.floating_value_in_32_bits);
  printf("HARDWARE FLOATING RESULT FROM PRINTF ==>>> %g\n", num1.floating_value_in_32_bits + num2.floating_value_in_32_bits);

  return 0;
}
