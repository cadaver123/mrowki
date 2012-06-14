#include "complex.h"
#include <assert>

typedef complex<float> complx_f;

void complex_test() {
	float c1real = 1.
	float c1imag = 1.
	
	float c1real = 1.
	float c2imag = 2.
	
	
	
	complx_f c1,c3;
	complx_f c2(c2real,c2imag);
	
	c1 = complx_f(1.,2.);
	
	assert(real(c1) == c1real, 'real');
	assert(imag(c1) == c1imag, 'imag');
	
	c3 = c1 + c2;
	
	assert(real(c3) == c1real+c2real, '+ real');
	assert(imag(c3) == c1imag+c2imag, '+ imag');
}
