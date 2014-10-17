/* 
 * CS:APP Data Lab 
 * 
 * <Shao-Han Chen:scr487; Nikhil Thagadur:nrt945>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
/* 
 * minusOne - return a value of -1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int minusOne(void) {
  return (~0);
}

/* 
 * fitsShort - return 1 if x can be represented as a 
 *   16-bit, two's complement integer.
 *   Examples: fitsShort(33000) = 0, fitsShort(-32768) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 1
 */
int fitsShort(int x) {
 
    //Ideas: two situdations which can't be represented by 16-bit 2's complement integer
    //1: positive: 0NNNNNNNNNNNNNNN*************** (N means non-zero, * means don't care)
    //2: negative: 1******************************
    
    x = x>>15;
    
    // All one or all zero means can be represented by 16-bit two's complement integer.
    return (!x + !(~x));

}
/*
 * isZero - returns 1 if x == 0, and 0 otherwise 
 *   Examples: isZero(5) = 0, isZero(0) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int isZero(int x) {
    
    return !x;
}
/* 
 * isLess - if x < y  then return 1, else return 0 
 *   Example: isLess(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLess(int x, int y) {
    
    
    //Ideas: Two situdations result in x < y
    //1: y is positive, and x is negative
    //2: x,y are different signs, and x < y

    
    int situation1 = x & (~y);
    int situation2 = ( (~(x^y)) & (x+(~y+1)) );
    
    return ((situation1|situation2)>>31)&1;
    
    
    /* Original Idea (doesn't work)
     int k;
    
     x = (~x)+1;
     k = (x+y);
   
     x = k&((0x00000001)<<31); // if x>y , x = 1
     x = ((!x)&(!!k))|((!!(x>>31))&(!(y>>31)));
     +((~(!k))+1)
     */
  

}
/* 
 * absVal - absolute value of x
 *   Example: absVal(-1) = 1.
 *   You may assume -TMax <= x <= TMax
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 4
 */
int absVal(int x) {
 
    return ( ((x>>31)^x) + (~(x>>31)+1) );
}
/* 
 * sm2tc - Convert from sign-magnitude to two's complement
 *   where the MSB is the sign bit
 *   Example: sm2tc(0x80000005) = -5.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 4
 */
int sm2tc(int x) {
    
    //Ideas: two situdations, x is positive or negative
    
    int k = (x>>31);
    
    return ( (~k&x) | ( k & (~(x&(~(1<<31))))+ (!!k) ) );;
}
/* 
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n) {
    
    return ( (x>>(n<<3)) & (0x000000FF) );
}
/* 
 * byteSwap - swaps the nth byte and the mth byte
 *  Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *            byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *  You may assume that 0 <= n <= 3, 0 <= m <= 3
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 25
 *  Rating: 2
 */
int byteSwap(int x, int n, int m) {
    
    int swap1 = ((x>>(n<<3))&(0x000000FF));
    int swap2 = ((x>>(m<<3))&(0x000000FF));
    
    swap1 = (swap1<<(m<<3));
    swap2 = (swap2<<(n<<3));
    
    x = (x&(~((0x000000FF)<<(n<<3)))&(~((0x000000FF)<<(m<<3))));
    
    return (x|swap1|swap2);
}
/* 
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
    
    x =( x & ( (0x000000AA) + ( (0x000000AA)<<8 )+( (0x000000AA)<<16 )+( (0x000000AA)<<24) ) );
  
    return ( !( x + (x<<1) + 2 ) );
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
    
    //By definition, two situdations: x=0 or x!=0
    
    x = !(!x);
    
    y = y & ( ~x+1 );
    z = z & ( ~( ~x+1 ) );
    
    return z+y;
}
/* 
 * greatestBitPos - return a mask that marks the position of the
 *               most significant 1 bit. If x == 0, return 0
 *   Example: greatestBitPos(96) = 0x40
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 70
 *   Rating: 4 
 */
int greatestBitPos(int x) {
    
    //Ideas: two situdations: MSB is the 32th bit or MSB is not the 32th bit
    
    x = x|(x>>1);
    x = x|(x>>2);
    x = x|(x>>4);
    x = x|(x>>8);
    x = x|(x>>16);
    
    return ( ( (x+1)>>1 )&( ~(x+1) ) ) | ( ((!((x+1)>>1) )& ( x>>31 ))<<31 );
}
/* 
 * float_abs - Return bit-level equivalent of absolute value of f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument..
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_abs(unsigned uf) {
    
    if ( (uf&0x7fffffff) >= 0x7F800001)
    return uf;
    
    else
    return (uf&0x7fffffff);


}
/* 
 * float_f2i - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int float_f2i(unsigned uf) {
    
    unsigned sign = uf >> 31;
    unsigned exp = (uf >> 23) & 0xFF;
    unsigned frac =(uf & 0x7FFFFF);
    unsigned bias = 0x7F;
    unsigned result;
         int E = (exp - bias);
    
    if (exp == 0xFF)
    return 0x80000000u;
    
    // 1. Denormalized Case
    // 2. Normalized Case that exp is less than bias
    // Result: Round-up to Zero
    if (exp < bias)
    return 0x0;
    
    // Normal normalized cases
    
    
    // Overflow
    if (E >= 31)
    return 0x80000000u;
    
    // get integer result after shift corresponding bits
    if (E > 22)
    result = frac << (E - 23);
    else
    result = frac >> (23 - E);
    
    // add 1 << exp for normalized case
    result += 1 << E;
    
    // if sign = 1, change its sign
    if (sign)
    result = -result;
    
    return result;

    
    //unsigned sign = !!(uf&(0x8000000));
    //unsigned exp = (uf&(0x7fc00000))>>23);
    //unsigned fraction =(uf&(0x007fffff));
    //unsigned cast = ((-1)^sign)*2^(exp-127)*

}
/* 
 * float_twice - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_twice(unsigned uf) {
    
    unsigned nosign = uf << 1;
    unsigned sign = uf & 0x80000000;
    
    // NaN and infinity, return itself
    if (nosign >= 0xFF000000) {
        return uf;
        
    // Denormalized, return non sign left shift by 1 bit
    } else if (nosign < 0x01000000) {
        return sign | nosign;
        
    // Normalized, non-sign < 0xFE000000, return value by exp+1
    } else if (nosign < 0xFF000000) {
        return uf + 0x800000;

    } else {
        return 0;
    }
    
}

    
