#include <stdio.h>
#include <stdlib.h>

unsigned two_comp(unsigned val)
{
	unsigned fill = (1 << 32) - 1; //filled 32 bit register: 0xffffffff
	unsigned new_val = val ^ fill; //XOR of input value with fill
	return new_val + 1;            //returning the 2's complement of the input value
}

void handle_neg(unsigned a)
{
	if( a > (1 << 31) - 1){
		a = two_comp(a);
		printf("\n\n-%u\n", a);
	}
	else printf("\n\n%u\n", a);
}

void issue_demo(int val);
void addition_demo(int a, int b);
void subtraction_demo(int a, int b);
void multiplication_demo(int a, int b);
void division_demo(int a, int b);

int main()
{
	int val = 1 << 31; //minimum value for an int
	issue_demo(val);   //demos an issue with 2's comp
	addition_demo(54,9021);      //add(a,b)  == a+b
	subtraction_demo(54,9021); //sub(a,b)  == a-b
	multiplication_demo(54,9021);   //mult(a,b) == a*b
	division_demo(54,9021);         //div(a,b)  == a/b
}

void issue_demo(int val)
{
	printf("Value: %d, hexidecimal rep: %x\n", val, (unsigned) val);

	printf("\nValue plus itself: %d\n", val + val);

	printf("\nTwo's Complement of the value: %x\n", two_comp((unsigned) val));
}

void addition_demo(int a, int b)
{
	unsigned u_sum = (unsigned) a + (unsigned) b;

	handle_neg(u_sum);
}

void subtraction_demo(int a, int b)
{
	unsigned diff = (unsigned) a + two_comp(b);

	handle_neg(diff); 
}

void multiplication_demo(int a, int b)
{
	unsigned a_1 = (unsigned) a & 0xffff0000; //isolating most sig bits of a
	unsigned a_2 = (unsigned) a & 0x0000ffff; //isolating least sig bits of a
	unsigned b_1 = (unsigned) b & 0xffff0000; //isolating most sig bits of b
	unsigned b_2 = (unsigned) b & 0x0000ffff; //isolating least sig bits of b
	unsigned mult = a_1*b_1 + a_1*b_2 + a_2*b_1 + a_2*b_2;

	handle_neg(mult);
}

void division_demo(int a, int b)
{
	unsigned a_1 = (unsigned) a & 0xffff0000; //isolating most sig bits of a
	unsigned a_2 = (unsigned) a & 0x0000ffff; //isolating least sig bits of a
	unsigned div = a_1/(unsigned)b + a_2/(unsigned)b;

	handle_neg(div);
}