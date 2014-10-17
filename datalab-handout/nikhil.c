int getByte(int x, int n)
{
	// n << 3 adjusts n so its value is represented in bit form.
	// x is arithmetically shifted right to n*(2^3) bits.
	// The mask 0xFF is applied to return only the least significant byte, byte n
	return (0xFF & (x >> (n << 3)));
}

int byteSwap(int x, int n, int m)
{
int a = 0xFF; /*a byte of ones, will be used to copy single bytes*/
/*<<3 is the same as multiplying by 8
nShift and mShift contain the number of bits you need to shift*/
int nShift = n << 3;
int mShift = m << 3;
/*shift a to the desired byte in x, & with x*/
int nByte = (a << nShift)&x;
int mByte = (a << mShift)&x;
int combo = (a << nShift) | (a << mShift); /*1's in the swapping bytes*/
/*shift swapping bytes back to the left*/
nByte = (nByte >> nShift)&a;
mByte = (mByte >> mShift)&a;
/*shift swapping bytes to their new position*/
nByte = nByte << mShift;
mByte = mByte << nShift;
/*store the nonchanging part of the int in "combo"*/
combo = ~combo & x;
return combo | mByte | nByte; /*combine the three parts*/
}

int allOddBits(int x) {
// build mask: 0xAAAAAAAA
int mask = (0xAA << 8) + 0xAA;
mask = (mask << 16) + mask;
return !((x & mask) ^ mask);
}

int conditional(int x, int y, int z)
{
x = !!x; /*puts x in 0 or 1 form*/
x = ~x+1; /*x is now either all 1's or all 0's*/
return (x & y) | (~x & z);
}

int greatestBitPos(int x) {
  int a = x | (x >> 1);
  a = a | (a >> 2);
  a = a | (a >> 4);
  a = a | (a >> 8);
  a = a | (a >> 16);
  return ((a ^ (a >> 1)) | 0x80 << 24) & a;
}

OR TRY THIS CODE

int greatestBitPos(int x) {
 // return log(2) of x
 unsigned int m;
 m = x;
 m = m | m >> 1;
 m = m | m >> 2;
 m = m | m >> 4;
 m = m | m >> 8;
 m = m | m >> 16;
 m = m & ((~m >> 1)^0x80000000);
printf("m is now %d\n", m);
return m;
}

int fitsShort(int x) {
// if will shift, and add 15 places of most signifiant bit
int n = x >> 15;
// there are two circumstances if it fits, you either get all 0000s or all 1111s
// if it fits, return 1 if its all zeros or all ones
// if there are sig numbers in upper bits, then it will evaluate to false
// the last situation is if the leading number is a 0
// this is the reason for the second half of the return statement
return !n + !(~n);
}

int isLess(int x, int y) {

  int sy,sx,cxy,override_byte,z;

  sy=y>>31;
  sx=x>>31;
  cxy=sx^sy;
  override_byte=cxy&sx;

    z=(y+(~x))>>31;

    return !((z|cxy)^override_byte);
 /*1. if x and y have the same sign y plus the complement of x should be positive. 2. if they have different signs the override byte has an effect and sets the result to either one or zero always*/


}

int sm2tc(int x) {

  /*1. if the msb of x is 0, no operation is carried out, else we use the fact that the sm number has the magnitude of the complement of its bit pattern viewed as a two's complement number plus the smallest two's complement number representable plus one. All in six ops :D */

  int small,sx;

  sx=x>>31;
  small=sx<<31;
  
  return small+(x^sx)+(sx&1);

}


unsigned float_abs(unsigned uf) {
unsigned mask = 0x7FFFFFFF;	
unsigned minNaN = 0x7Fc00000;
unsigned res = uf & mask;	// set sign bit to 0
// return argument if it is NaN, all NaN >= minimum NaN
if (res >= minNaN)
{
return uf;
}
else
{
return res;
}
}

unsigned float_i2f(int x) {
    /* Determine by different value */
    unsigned uNonSign;
    unsigned uExp;
    unsigned uTemp;
    if (x) { // Non-zero
        if (x < 0) { // Choose sign and exp part by sign
            uExp = 0xCF800000;
            uNonSign = -x;
        } else {
            uExp = 0x4F800000;
            uNonSign = x;
        }
        while (1) { // Calculate frac and exp part
            uTemp = uNonSign;
            uNonSign <<= 1;
            uExp -= 0x800000;
            if (uTemp & 0x80000000) {
                break;
            }
        }
        uExp += (uNonSign >> 9);
        if ((uNonSign & 0x3FF) == 0x300) { // Round frac
            ++ uExp;
        } else if ((uNonSign & 0x1FF) > 0x100) {
            ++ uExp;
        }
        return uExp;
    } else { // Zero
        return 0;
    }
}

unsigned float_twice(unsigned uf) {
  int sign = ((uf >> 31) << 31);
  int exp =  (((uf << 1) >> 24) << 23);
  int fract = (uf << 9) >> 9;

   if(exp == 0)
   {
      return ((uf << 1) | sign);
   }

   else if(exp == 0x7F800000)
   {
      return uf;
   }
   
   else
   {
       exp = (exp + 0x800000);
   }
 return ((sign | exp) | fract);
 }

OR TRY THIS CODE

unsigned float_twice(unsigned uf) {
    /* Divided into different situations */
    unsigned uNonSign = uf << 1;
    unsigned uSign = uf & 0x80000000;
    if (uNonSign >= 0xFF000000) { // NaN and infinity, return itself
        return uf;
    } else if (uNonSign < 0x01000000) { // Denormalized, return non sign right shift 1 bit
        return uSign | uNonSign;
    } else if (uNonSign < 0xFE000000) { // Normalized, non-sign < 0xFE000000, return exp + 1
        return uf + 0x800000;
    } else { // Other situation, return infinity
        return uSign | 0x7F800000;
    }
}




