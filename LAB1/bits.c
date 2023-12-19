/*
 * CS:APP Data Lab
 *
 * <Please put your name and userid here>
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
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.


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

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

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
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
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
// 1
/*
 * bitXor - x^y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
/*
	  0 1
   0  0 1
   1  1 0
  对着真值表试
*/
int bitXor(int x, int y)
{
	return (~(x & y) & ~(~x & ~y));
}
/*
 * tmin - return minimum two's complement integer
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
/*
  B2T(w)   -公式2.1
  直接左移31位
*/
int tmin(void)
{
	return (0x1 << 31);
}
// 2
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
/*
  B(Tmax) = 01111111 11111111 11111111 11111111
  (!(~x ^ (x + 0x1))) 用来判定是 Tmax
  !!~x 用来排除 x = -1 的case
*/
int isTmax(int x)
{
	// return (!(~x ^ (x + 0x1))) & (!x);
	// return !(~((~0x0 + ~x) & x) ^ (x + 0x1));
	return (!(~x ^ (x + 0x1))) & !!~x;
}
/*
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
/*
  当且仅当 x == mask 时， (x & mask) ^ mask == 0
*/
int allOddBits(int x)
{
	// return !(((x & 0xAA) ^ 0xAA) + (((x >> 8) & 0xAA) ^ 0xAA)
	//       + (( (x >> 16) & 0xAA) ^ 0xAA) + (( (x >> 24) & 0xAA) ^ 0xAA));
	int mask = 0xAA + (0xAA << 8) + (0xAA << 16) + (0xAA << 24);
	return !((x & mask) ^ mask);
}
/*
 * negate - return -x
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
/*
  补码性质：取反加一
*/
int negate(int x)
{
	return ~x + 1;
}
// 3
/*
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
/*
 用到了补码存在的意义--使用加法器就可以实现减法
 如果 0x30 <= x <= 0x39， x - 0x30 >= 0 and x - 0x3a < 0
*/
int isAsciiDigit(int x)
{
	int left = x + (~0x30 + 1);
	int right = x + (~0x3a + 1);
	return (!(left >> 31)) & (right >> 31);
}
/*
 * conditional - same as x ? y : z
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
/*
  算数右移性质：高位补1
  x == True， !!x == 0x1, mask == -1(二进制全1)
  x == False, !!x == 0x0, mask == 0(二进制全0)
*/
int conditional(int x, int y, int z)
{
	int mask = ((!!x << 31) >> 31); // 算数右移
	return (mask & y) | (~mask & z);
}
/*
 * isLessOrEqual - if x <= y  then return 1, else return 0
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y)
{
	// y - x >= 0
	int neg_flag = (x >> 31 & 0x01) | (!(y >> 31 & 0x01)); // neg_flag = 0 if y < 0 and x >= 0, else neg_flag = 1
	int pos_flag = (!(y >> 31 & 0x01)) & (x >> 31 & 0x01); // pos_flag = 1 if y >= 0 and x < 0
	return pos_flag | (neg_flag & (!((y + (~x + 0x01)) >> 31 & 0x01)));
}
// 4
/*
 * logicalNeg - implement the ! operator, using all of
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int logicalNeg(int x)
{
	return (~x >> 31 & 0x01) & (~(x + (~(0x01 << 31))) >> 31);
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
/*
  这个真不会
  规律大概找出来了，对于正数，最高为1的bit位+1；负数取反同正数
  但是要满足操作数小于90，得二分
  二分其实也想到了，但是不知道咋写
*/
int howManyBits(int x)
{

	int mask = (~(x >> 31)); // is 0xFFFFFFFF if x >= 0, is 0x00 if x < 0
	int isRs16Not0 = 0;
	int needRs16 = 0;
	int needRs8 = 0;
	int needRs4 = 0;
	int needRs2 = 0;
	int needRs1 = 0;
	int rsCnt = 0;
	int isRs8Not0 = 0;
	int isRs4Not0 = 0;
	int isRs2Not0 = 0;
	int isRs1Not0 = 0;

	x = (~(x ^ mask));

	// mask = 0x01;
	// int res = 0;

	// x >>= 1; res += !!x;
	isRs16Not0 = (!!((x >> 16) ^ 0x0)); // 判断右移16后是否为0,非0为1,是0则为0
	needRs16 = isRs16Not0 << 4;			// 计算右移位数,上一步 isRs16Not0=0时，则无需右移, 否则右移16位
										// 即isRs16Not0==0? 0:16
	x >>= needRs16;						// 进行右移操作,无论如何,这一步要有.
	isRs8Not0 = !!((x >> 8) ^ 0);
	needRs8 = isRs8Not0 << 3;
	x >>= needRs8;
	isRs4Not0 = !!((x >> 4) ^ 0);
	needRs4 = isRs4Not0 << 2;
	x >>= needRs4;
	isRs2Not0 = !!((x >> 2) ^ 0);
	needRs2 = isRs2Not0 << 1;
	x >>= needRs2;
	isRs1Not0 = !!((x >> 1) ^ 0); // 如果右移一位后是0,则不会右移,此时x一定是:...0001, 最后统计rsCnt时,要加1
	needRs1 = isRs1Not0;		  // 如果右移一位后不是0,则右移一位后,x一定是:...0001
	x >>= needRs1;

	rsCnt = needRs16 + needRs8 + needRs4 + needRs2 + needRs1 + x; // 最后+x, 对于非0数, 最后一定剩下一个1，右移1位即可,
																  // 对于0,从头到位都是0,不需要再+1
	return rsCnt + 1;
}
// float
//  FUCK FLOAT
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
unsigned floatScale2(unsigned uf)
{
	unsigned ret = 0;
	unsigned s, exp, frac;
	s = (uf >> 31) & 0x1;
	exp = (uf >> 23) & 0xff;
	frac = uf & 0x7fffff;

	if (exp == 0xff)
	{
		return uf;
	}
	if (!exp)
	{
		// 非规格化数，其frac < 1（表示接近0的数），计算2 * uf 要把frac*2
		frac <<= 1;
	}
	else
	{
		// 规格化数，frac > 1，计算2*uf=2^（E+1）
		exp += 1;
	}
	ret = (s << 31) | (exp << 23) | frac;
	return ret;
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
int floatFloat2Int(unsigned uf)
{
	// unsigned s, exp, frac;
	// unsigned Bias = 0x7f;
	// s = (uf >> 31) & 0x1;
	// exp = (uf >> 23) & 0xff;
	// frac = uf & 0x7fffff;
	// // E = e - Bias;
	// unsigned E = exp - Bias;
	// if (exp == 0xff) {
	//   return (0x1 << 31);
	// }
	// if (!exp || ((E >> 31) & 0x1)) {
	//   return 0;
	// } else{
	//   frac |= (0x1 << 23);
	//   if (E > 23) {
	//     frac <<= (E - 23);
	//   } else {
	//     frac >>= (E - 23);
	//   }
	// }
	// return frac;
	unsigned s = (uf >> 31) & 0x1;
	unsigned exp = (uf >> 23) & 0xFF;
	unsigned frac = (uf & 0x7FFFFF);
	int E = exp - 127;
	frac = frac | (1 << 23);
	// float = (-1) M * 2^E  -> E的大小可以理解为小数M的小数点向右的位数
	// E < 0, 非规格化数，一定表示<1的。反证：1.0000001 -> M = 0.000001, E = 1 
	if (E < 0)
		return 0;
	// E=31, f=M * 2^31 溢出
	else if (E >= 31)
		return 0x1 << 31;
	else
	{
		// <23,(E - 23)是frac补的0
		if (E < 23)
		{
			frac >>= (23 - E);
		}
		// >23，(E - 23)表示小数点向右点23为后，再向后点的位数
		else
		{
			frac <<= (E - 23);
		}
	}
	if (s)
	     return ~frac + 1;
	return frac;
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
unsigned floatPower2(int x)
{
	unsigned E = 1;
	int exp = E + 127;
	// 2.0 = (1) * 1 * 2^1
	// (2.0)^x = 2^x
	exp = x + 127;
	unsigned ret;
	if (exp > 0xFF) 
	{
		ret = 0x7f800000;	// 非规格的NaN
	}
	// 规格化
	else if (exp > 0)
	{
		ret = exp << 23;
	}
	// ? 这个不懂
	// 非规格
	// exp = -3, e = 2^(-130)
	else if (exp > -23)
	{
		ret = 1 << (exp + 22);
	}
	else
	{
		ret = 0;
	}
	return ret;
}
