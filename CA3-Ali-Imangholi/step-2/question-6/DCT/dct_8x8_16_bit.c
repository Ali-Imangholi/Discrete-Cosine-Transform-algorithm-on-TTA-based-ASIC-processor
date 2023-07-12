/* Calculation of DCT_8x8 */

/* f(x,y) is 8X8 matrix containing inputs for DCT */
/* f(1,0) means second(0,1,2...,7) row first column */ 
/* results are also stored to same matrix */
/* calculation can be done with different orders */
/* columns followed by rows or rows followed by columns */

/* used fixed point values 1,15 */
/* value of fixed_point numner is:
   (1/2^15)(-2^(15)(sign_bit)+sum(2^n*(bit_n))), sum 0;N-2,n
   => 8000 => -2^15*(1/2^15) = -1  
   => ffff => -(2^15)+(2^15-1)/2^15 = -1/2^15
*/  

/* calculates the value of cos(input1*Pi/16) */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>

/*
#define DEBUG_WHOLE_MEMORY
#define DEBUG_SINGLE_MEMORY_LOCATION
#define DEBUG_MULTIPLIER
#define DEBUG_ADDER


  #define DEBUG_COS
*/

unsigned int cos16(int input);
unsigned int fix_mul_16(unsigned int num1, unsigned int num2);

unsigned int fix_add_16(unsigned int num1, unsigned int num2);

unsigned int f [8][8] = 
{
    {19166, 56110, 39345, 48489, 35352, 56025, 46185, 39081},
    {59462, 59696, 65342, 54608, 7366, 24575, 27599, 10264},
    {26973, 28815, 10036, 25075, 21014, 41419, 25812, 23650},
    {31348, 58441, 7837, 25319, 26211, 9919, 10125, 46459},
    {38085, 22594, 20614, 47266, 1660, 5157, 28476, 31670},
    {17491, 46366, 42065, 53606, 65260, 28434, 53825, 25629},
    {29498, 38758, 33485, 36774, 46403, 7667, 51590, 53276},
    {8299, 29726, 13226, 57324, 50627, 26239, 151, 10542}
};

int main() {

  
    unsigned int F[8][8];
    unsigned int a;
    unsigned int b;
    unsigned int c;
    unsigned int d;
    unsigned int e;
    unsigned int g;
    unsigned int h;
    unsigned int k;
    unsigned int j;
    unsigned int temp3;
    int y = 0; 
    int x = 0;
    int i = 0; 
    
    /*  MEMORY ORGANIZATION
        0,0 0,1 0,2 0,3 0,4 0,5 0,6 0,7
        1,0 1,1 1,2 1,3 1,4 1,5 1,6 1,7
        2,0 2,1 2,2 2,3 2,4 2,5 2,6 2,7
        3,0 3,1 3,2 3,3 3,4 3,5 3,6 3,7
        4,0 4,1 4,2 4,3 4,4 4,5 4,6 4,7
        5,0 5,1 5,2 5,3 5,4 5,5 5,6 5,7
        6,0 6,1 6,2 6,3 6,4 6,5 6,6 6,7
        7,0 7,1 7,2 7,3 7,4 7,5 7,6 7,7
 
         first calculate rows */
    for (y = 0 ; y < 8; y++){
/*#ifdef DEBUG_SINGLE_MEMORY_LOCATION
        printf("ROW %1d:\n" ,y);
#endif	*/
        for (x = 0 ; x < 8; x++){
            a = fix_mul_16(f[y][0],cos16(x));
            b = fix_mul_16(f[y][1],cos16(3*x));
            c = fix_mul_16(f[y][2],cos16(5*x));
            d = fix_mul_16(f[y][3],cos16(7*x));
            e = fix_mul_16(f[y][4],cos16(9*x));
            g = fix_mul_16(f[y][5],cos16(11*x));
            h = fix_mul_16(f[y][6],cos16(13*x));
            j = fix_mul_16(f[y][7],cos16(15*x));
/*#ifdef DEBUG_MULTIPLIER
            printf("    a: %d , f: %d , cos: %d\n",a,f[y][0],cos16(x));
            printf("    b: %d , f: %d , cos: %d\n",b,f[y][1],cos16(3*x));
            printf("    c: %d , f: %d , cos: %d\n",c,f[y][2],cos16(5*x));
            printf("    d: %d , f: %d , cos: %d\n",d,f[y][3],cos16(7*x));
            printf("    e: %d , f: %d , cos: %d\n",e,f[y][4],cos16(9*x));
            printf("    g: %d , f: %d , cos: %d\n",g,f[y][5],cos16(11*x));
            printf("    h: %d , f: %d , cos: %d\n",h,f[y][6],cos16(13*x));
            printf("    j: %d , f: %d , cos: %d\n",j,f[y][7],cos16(15*x));
#endif

#ifdef DEBUG_ADDER
            temp3 = fix_add_16(a,b);
            printf("a+b : %d\n", temp3); 
            temp3 = fix_add_16(temp3,c);
            printf("+c : %d\n", temp3);
            temp3 = fix_add_16(temp3,d);
            printf("+d : %d\n", temp3);
            temp3 = fix_add_16(temp3,e);
            printf("+e : %d\n", temp3);
            temp3 = fix_add_16(temp3,g);
            printf("+g : %d\n", temp3);
            temp3 = fix_add_16(temp3,h);
            printf("+h : %d\n", temp3);
            temp3 = fix_add_16(temp3,j);
            printf("+j : %d\n", temp3);
#endif
*/

            temp3 = fix_add_16(a,b);
            temp3 = fix_add_16(temp3,c);
            temp3 = fix_add_16(temp3,d);
            temp3 = fix_add_16(temp3,e);
            temp3 = fix_add_16(temp3,g);
            temp3 = fix_add_16(temp3,h);
            temp3 = fix_add_16(temp3,j);
	    
            F[y][x] = temp3;
/*
#ifdef DEBUG_SINGLE_MEMORY_LOCATION
            printf("  memory at [%1d][%1d] : %d\n", y,x,F[y][x]);
#endif*/
        }
        for (x = 0 ; x < 8; x++){
            f[y][x] = F[y][x];
        }
    }/*
#ifdef DEBUG_WHOLE_MEMORY
	printf("MEMORY_AFTER ROWS:\n");	
    for (y = 0 ; y < 8; y++){
        for (x = 0 ; x < 8; x++){
            printf("  memory at [%1d][%1d] : %d\n", y,x,F[y][x]);              
        }
    }	
#endif	
*/
    /* second columns
     */
    
    for (y = 0 ; y < 8; y++){
/*#ifdef DEBUG_SINGLE_MEMORY_LOCATION
        printf("COLUMN %1d:\n" ,y);
#endif*/		
        for (x = 0 ; x < 8; x++){
            a = fix_mul_16(f[0][y],cos16(x));
            b = fix_mul_16(f[1][y],cos16(3*x));
            c = fix_mul_16(f[2][y],cos16(5*x));
            d = fix_mul_16(f[3][y],cos16(7*x));
            e = fix_mul_16(f[4][y],cos16(9*x));
            g = fix_mul_16(f[5][y],cos16(11*x));
            h = fix_mul_16(f[6][y],cos16(13*x));
            j = fix_mul_16(f[7][y],cos16(15*x));
/*
#ifdef DEBUG_MULTIPLIER
            printf("    a: %d , f: %d , cos: %d\n",a,f[0][y],cos16(x));
            printf("    b: %d , f: %d , cos: %d\n",b,f[1][y],cos16(3*x));
            printf("    c: %d , f: %d , cos: %d\n",c,f[2][y],cos16(5*x));
            printf("    d: %d , f: %d , cos: %d\n",d,f[3][y],cos16(7*x));
            printf("    e: %d , f: %d , cos: %d\n",e,f[4][y],cos16(9*x));
            printf("    g: %d , f: %d , cos: %d\n",g,f[5][y],cos16(11*x));
            printf("    h: %d , f: %d , cos: %d\n",h,f[6][y],cos16(13*x));
            printf("    j: %d , f: %d , cos: %d\n",j,f[7][y],cos16(15*x));
#endif

#ifdef DEBUG_ADDER
            temp3 = fix_add_16(a,b);
            printf("a+b : %d\n", temp3); 
            temp3 = fix_add_16(temp3,c);
            printf("+c : %d\n", temp3);
            temp3 = fix_add_16(temp3,d);
            printf("+d : %d\n", temp3);
            temp3 = fix_add_16(temp3,e);
            printf("+e : %d\n", temp3);
            temp3 = fix_add_16(temp3,g);
            printf("+g : %d\n", temp3);
            temp3 = fix_add_16(temp3,h);
            printf("+h : %d\n", temp3);
            temp3 = fix_add_16(temp3,j);
            printf("+j : %d\n", temp3);
#endif
*/

            temp3 = fix_add_16(a,b);
            temp3 = fix_add_16(temp3,c);
            temp3 = fix_add_16(temp3,d);
            temp3 = fix_add_16(temp3,e);
            temp3 = fix_add_16(temp3,g);
            temp3 = fix_add_16(temp3,h);
            temp3 = fix_add_16(temp3,j);
	    
            F[x][y] = temp3;
/*#ifdef DEBUG_SINGLE_MEMORY_LOCATION
            printf("  memory at [%1d][%1d] : %d\n", x,y,F[x][y]);
#endif*/	    
        }
        for (x = 0 ; x < 8; x++){
            f[x][y] = F[x][y];
        }
    }
    
    
/*
#ifdef DEBUG_WHOLE_MEMORY
	printf("MEMORY_AFTER Final memory:\n");		
	for (y = 0 ; y < 8; y++){
	    for (x = 0 ; x < 8; x++){
            printf("  memory at [%1d][%1d] : %d\n", y,x,F[y][x]);              
	    }
	}
#endif*/
    return 0;
    /* calculation is complete */
}

unsigned int cos16(int input) {

    unsigned int cosine_values[] = {32138, 
                                    27246,
                                    18205,
                                    6393};

    unsigned int remainder = 0;
    int address = 0;
    int inverse = 0;
    unsigned int value = 0;
    remainder = input - input/8;
    
    
    if (remainder == 1) {
        address = 0;
    } else if ( remainder == 3) {
        address = 1;
    } else if (remainder == 5) {
        address = 2;
    } else if (remainder == 7) {
        address = 3;
    } else {
        address = 0;
    }

    if (input >8)
        inverse = 1;
    
    if (inverse == 1) {
        value = 65536-cosine_values[address];
    } else {
        value = cosine_values[address];
    }


/*#ifdef DEBUG_COS
    printf("COSINE:\n");
    printf("input : %3d\n",input);  
    printf("address : %1d, neq : %1d\n",address,inverse);
    printf("cos : %d\n",value);
#endif*/
    return value;
}

unsigned int fix_mul_16(unsigned int num1, unsigned int num2){
    unsigned int temp,prod;
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

    return prod;
}

unsigned int fix_add_16(unsigned int num1, unsigned int num2){
    int temp1,temp2;
    int neg1 = 0;
    int neg2 = 0;
    unsigned int sum;

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

    return sum;
}
