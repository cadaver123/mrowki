#ifndef COMPLEXX_H_
#define COMPLEXX_H_


#include <complex>
#include <math.h>
#include <stdlib.h>
#include <time.h>

typedef std::complex<float> complx;

 complx complx_norm(complx a);

//template <typename Type>
 float positive(float a);
 
//random complex number implementation
template <typename T>
std::complex<T> rand_cmplx() {
	srand(time(NULL));
	float rand_phi = float(M_PI)*float(rand()%10000)/10000; 
	srand ( time(NULL)+	time(NULL)%100);
	float rand_r = float(rand()%10000)/10000;
	return  rand_r * std::complex<T>(cos(rand_phi),sin(rand_phi));
	}

  #endif	