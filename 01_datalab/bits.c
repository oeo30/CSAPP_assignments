/* 
 * CS:APP Data Lab  
 * Name: Nayeon Tak
 * Date: 251129
 */

/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {	
	return ~(~(x&~y)&~(~x&y));
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
    return 1<<31; //1000...0
}
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) { 
  return !~(x^(x+1)) & !!(x+1);
}
/* 
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
    int mask1 = 0xAA | 0xAA<<8;
    int mask2 = mask1 | mask1<<16;
    return !((x&mask2)^mask2); 
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
    return (~x)+1;
}
/* 
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
    return !((x>>3)^0x06) | !((x>>1)^0x1C);
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
    int mask = !x + (~0);
    return (y&mask) | (z&~mask);
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
    int diff = x+(~y+1);
    int sign = (x>>31)^(y>>31);

    int case1 = sign&(x>>31);
    int case2 = ~sign&((!diff)|((diff>>31)&0x1));
    return (!!case1) | (!!case2);
}
/* 
 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int logicalNeg(int x) {
    return ((x | (~x+1)) >> 31) + 1;
}
/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
int howManyBits(int x) {
    int y = x ^ (x>>31);  //flip if negative
    int cnt = 0;
    int check16, check8, check4, check2, check1;

    //binary search
    check16 = !!(y>>16);
    cnt += check16<<4;
    y >>= check16<<4;

    check8 = !!(y>>8);
    cnt += check8<<3;
    y >>= check8<<3;

    check4 = !!(y>>4);
    cnt += check4<<2;
    y >>= check4<<2;

    check2 = !!(y>>2);
    cnt += check2<<1;
    y >>= check2<<1;

    check1 = !!(y>>1);
    cnt += check1;
    y >>= check1;

    cnt += y;
    return cnt+1;
}

//float
/* 
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatScale2(unsigned uf) {
    unsigned sign = uf & 0x80000000 ; //first bit
    unsigned exp = uf & 0x7F800000; //second~9th bit
    unsigned frac = uf & 0x007FFFFF; //10th~36th bit

    if(exp>>23 == 0xFF) return uf; //special value
    if(exp == 0) return sign | (frac<<1); //denormalized
    return sign | (exp+(1<<23)) | frac; //normalized
}
/* 
 * floatFloat2Int - Return bit-level equivalent of expression (int) f
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
int floatFloat2Int(unsigned uf) {
    unsigned sign = uf & 0x80000000;
    unsigned exp = uf & 0x7F800000;
    unsigned frac = uf & 0x007FFFFF;

    int E = (exp>>23) - 127;
    int M = (1<<23) | frac;

    if (E < 0) return 0; //0.xxx
    if (E > 30) return 0x80000000u; //overflow

    //normalized value
    if (E >= 23) M = M << (E-23); //scale to exp 
    else M = M >> (23-E);
    
    if (sign) return -M; //sign
    else return M;
}   
/* 
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 * 
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while 
 *   Max ops: 30 
 *   Rating: 4
 */
 /*
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatPower2(int x) { //x is E
    if (x > 127) return 0x7F800000;  //INF: Max(E) = 127
    if (x < -149) return 0;  //underflow: Min(E) = -149 
    if (x < -126) return 1 << (23-(-126-x)); //denormalized, shift = -126-x 
    return (x + 127) << 23; //normalized, exp = E+127
}
