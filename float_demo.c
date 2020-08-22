#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX 31
#define MANT_MAX 22

unsigned two_comp(unsigned val)
{
	unsigned fill = (1 << 8) - 1;  //filled 8 bit register: 0x000000ff
	unsigned new_val = val ^ fill; //XOR of input value with fill
	return new_val + 1;            //returning the 2's complement of the input value
}

void f_point(unsigned a);

int main(void)
{
	unsigned a = 0x45ff84e1;
	printf("The input is: %x\n\n", a);
	f_point(a);
}

void f_point(unsigned a)
{
	unsigned raw_mant = a & 0x003fffff;
	printf("The raw mantisa is: %x\n", raw_mant);
	float mant = 0.0;
	int i;
	for(i = 0; i < MAX-8; ++i){
		if(a & (1 << MANT_MAX - i)){
			mant += pow(0.5,i);
		} else {
			continue;
		}
	}
	printf("the mantisa is: %f\n", mant);

	unsigned a_e = a & 0x7f800000; //Isolating the exp bits
	a_e = a_e >> 23; //shifting the exp to look at actual value

	printf("\nThe raw exponent part is: %x\n", a_e);
	printf("Which gives a value of: ");

	double val;
	if(a_e > (1 << 7) - 1){
		a_e = two_comp(a_e);
		val = -(int)a_e*log10(2.0);
	} else {
		val = (int)a_e*log10(2);
	}

	double round_val;
	if(val < 0){
		round_val = ceil(val);
	} else {
		round_val = floor(val);
	}
	double frac_val = val - round_val;

	if(a & 0x80000000){
		printf("\nThe floating point value is: -%fe%d\n", mant*pow(10,frac_val), (int)round_val);
	} else {
		printf("\nThe floating point value is: %fe%d\n", mant*pow(10,frac_val), (int)round_val);
	}
}