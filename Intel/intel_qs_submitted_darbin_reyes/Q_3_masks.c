/**

Question 3.

Give the AND and OR masks to set the value 6 in bits 30:23 of a dword.

**/

// d6=b0110

#define AND_MASK 0x807FFFFF // clears bits 30:23
#define OR_MASK   0x03000000 // set value 6 in bits 30:23
dword &= AND_MASK
dword |= OR_MASK