/**
 * OSAL behavior definition file.
 */

#include "OSAL.hh"

// Typedef used for representing complex numbers.
typedef short Scalar;
typedef union {
    int word;
    struct {
        Scalar imag;
        Scalar real;
    }cplx;
}Complex;

#define Real(a) (a.cplx.real)
#define Imag(a) (a.cplx.imag)
#define Word(a) (a.word)

OPERATION(COS16)

TRIGGER

unsigned int input = UINT(1);

    unsigned int cosine_values[] = {32767,  
                                    32138, 
                                    30274,
                                    27246,
                                    23170,
                                    18205,
                                    12540,
                                    6393};

    unsigned int remainder = 0;
    int inverse = 0;
    int temp = 0;
    unsigned int value = 0;
    temp = input/8;
    remainder = input - input/16;
    if (remainder >8) {
    	remainder = 16 - remainder;
    }
    
    while (temp>=4)
    	temp -= 4;

    if (temp ==1 || temp ==2)
        inverse = 1;
    
    if (inverse == 1) {
    	if (address == 0) {
            value = 65536-cosine_values[remainder]-1;
        } else {
	    value = 65536-cosine_values[remainder];
    	}
    } else {
        value = cosine_values[remainder];
    }

IO(2) = value;
RETURN_READY;
END_TRIGGER;

END_OPERATION(COS16)



OPERATION(MUL_16_FIX)
TRIGGER
unsigned int num1 = UINT(1);
unsigned int num2 = UINT(2);
unsigned int prod;
int temp1,temp2;
int neg1= 0;
int neg2 = 0;


if (num1 > 32767){
  if (num1 > 65535) {
    num1 = 65535;
  }
  neg1 = 1;
  temp1 = 0-num1+65536;
} else {
  temp1 = (int)(num1);
}
if (num2 > 32767){
  if (num2 > 65535) {
    num2 = 65535;
  }
  neg2 = 1;
  temp2 = 0-num2+65536;
} else {
  temp2 = (int)(num2);
}
prod = ((int)(temp1) * (int)(temp2)) >> 15;

if ((neg1 == 0 && neg2 == 1)||
    (neg1 == 1 && neg2 == 0)) {
  prod = 65536 - prod;
}


IO(3) = prod;
RETURN_READY;
END_TRIGGER;
END_OPERATION(MUL_16_FIX)

OPERATION(ADD_16_FIX)
TRIGGER
unsigned int num1 = UINT(1);
unsigned int num2 = UINT(2);
unsigned int sum;

int temp1 = 0;
int temp2 = 0;
int neg1 = 0;
int neg2 = 0;

  if (num1 > 32767){
    if (num1 > 65535) {
      num1 = 65535>>1;
    }
    neg1 = 1;
    temp1 = (0-num1+65536)>>1;
  } else {
    temp1 = (int)(num1)>>1;
  }
  if (num2 > 32767){
    if (num2 > 65535) {
      num2 = 65535>>1;
    }
    neg2 = 1;
    temp2 = (0-num2+65536)>>1;
  } else {
    temp2 = (int)(num2)>>1;
  }
  /*
  printf("neg1 : %d, neg2: %d\ntemp1 : %u, temp2 : %u\n",neg1,neg2,temp1,temp2);
  */
  if (temp1 > temp2) {
    if (neg1 == 1 && neg2 == 0){
      sum = 65536-(temp1 - temp2);
    } else if (neg1 == 0 && neg2 ==1) {
      sum = temp1-temp2;
    } else if (neg1 == 1 && neg2 == 1){
      sum = 65536-(temp1+temp2);
    } else {
      sum = temp1+temp2;
    }
  } else {
    if (neg2 == 1 && neg1 == 0){
      sum = 65536-(temp2 - temp1);
    } else if (neg2 == 0 && neg1 ==1) {
      sum = temp2-temp1;
    } else if (neg1 == 1 && neg2 == 1){
      sum = 65536-(temp1+temp2);
    } else {
      sum = temp1+temp2;
    }    
  }

IO(3) = sum;
RETURN_READY;
END_TRIGGER;
END_OPERATION(ADD_16_FIX)

