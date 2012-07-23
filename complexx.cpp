#include "complexx.h"


#include <complex>


using namespace std;





 complx complx_norm(complx a) {
	return abs(a) > 1? (1/abs(a))*a:a;
}

//template <typename Type>
 float positive(float a) {
    return a > float(0) ? a : float(0);

}