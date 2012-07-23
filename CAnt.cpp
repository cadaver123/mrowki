
//#include "stdafx.h"
#include "CAnt.h"
#include "CField.h"
#include "complexx.h"
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include "curses.h"
#include <complex>




using namespace std;


inline void CAnt::AStartSearchFood() {
	_direction = complx (0.,0.);
	ABasicStatus = 1;	
}

inline void CAnt::AGoToBase() {
	_direction = complx (0.,0.);	
	ABasicStatus = 2;
}
template <typename T>
 inline T sgn(T t) 
{
    if( t == 0 )
        return T(0);
    else
        return (t < 0) ? T(-1) : T(1);
}

//dopisać template do obcinania w wartości mniejszych od 0

CAnt::CAnt(CField * Plain[max_x][max_y], CField * start_field) {
	this->Plain = Plain;
	this->pos = start_field;
	pos->FBusy = 1;
	x_old = 0;
	y_old = 0;

	_direction = rand_cmplx<float>();

	AHungerInc = 0.1;
	srand ( time(NULL) );
	AHunger = 0.0;
	APhero_strenght =  float((500 + rand() % 500))/1000; 
	
	Invetory = new CAntInvetory(this);
	NearFieldsPheroLvL = new AntSniffResult;
	ABasicStatus = 1;
}

CAnt::~CAnt() {
	delete Invetory;
	delete NearFieldsPheroLvL;
}

void CAnt::CAntLoop() {
		//ant will try return to base
		if ((Invetory->Food > 0.) && (ABasicStatus != 2)) {
			AGoToBase();
		}
		//ant is searching food
		else if ((Invetory->Food == 0.) && (ABasicStatus != 1)) {
			AStartSearchFood();
		} 
		AHunger += AHungerInc;
		AMove(ASniff());
		
		if (pos->FFood_lvl > 0) {
			float FoodTaken;
			float foodLvl = pos->FFood_lvl;
			if(Invetory->Food < AMaxFoodLoadCap) {
				FoodTaken = (AMaxLoot > foodLvl)?foodLvl:AMaxLoot;
				Invetory->Food =  ((FoodTaken + Invetory->Food)>0)?AMaxFoodLoadCap:(FoodTaken + Invetory->Food);
				pos->FFood_lvl = foodLvl - FoodTaken;
			}			
	}
	if(pos->FBase) Invetory->Food = 0.; 
	pos->FPhero_lvl += APhero_strenght; 
}


CAntInvetory::CAntInvetory(CAnt* ant) {
		Owner  = ant;
		Food = 0;
}


//
AntSniffResult & CAnt::ASniff() {	
	int x = pos->_x;
	int y = pos->_y;
	complx res = complx(0.,0.);
	

	char nearbaseIndicator[8] = {0};
	char nearfood[8] = {0};
	
	if (doesFieldExist(x,y+1) && ~areThoseOldCoordsOfAnt(*this,x,y+1)) {
		NearFieldsPheroLvL->Up = complx(0, Plain[x][y+1]->FPhero_lvl);
		//if ( Plain[x][y+1]-> )
	}
	if (doesFieldExist(x,y-1) && ~areThoseOldCoordsOfAnt(*this,x,y-1)) {
		NearFieldsPheroLvL->Down = complx(0,-1 * Plain[x][y-1]->FPhero_lvl); 
	}
	if (doesFieldExist(x-1,y) && ~areThoseOldCoordsOfAnt(*this,x-1,y)) {
		NearFieldsPheroLvL->Left = complx(-1 * Plain[x-1][y]->FPhero_lvl,0) ;
	}
	if (doesFieldExist(x+1,y) && ~areThoseOldCoordsOfAnt(*this,x+1,y)) { 
		NearFieldsPheroLvL->Right =  complx(Plain[x+1][y]->FPhero_lvl,0);
 
	}
	if (doesFieldExist(x+1,y+1) && ~areThoseOldCoordsOfAnt(*this,x+1,y+1)) { 
		NearFieldsPheroLvL->RightUpperCorn =Plain[x+1][y+1]->FPhero_lvl*complx(sqrt(float(2))/2,sqrt(float(2))/2);
	}	
	if (doesFieldExist(x-1,y+1) && ~areThoseOldCoordsOfAnt(*this,x-1,y+1)) { 
		NearFieldsPheroLvL->LeftUpperCorn = Plain[x-1][y+1]->FPhero_lvl*complx(-sqrt(float(2))/2,sqrt(float(2))/2);
	}
	if (doesFieldExist(x-1,y-1) && ~areThoseOldCoordsOfAnt(*this,x-1,y-1)) { 
		NearFieldsPheroLvL->LeftBottomCorn = Plain[x-1][y-1]->FPhero_lvl*complx(-sqrt(float(2))/2,-sqrt(float(2))/2);
	}	
	if (doesFieldExist(x+1,y-1) && ~areThoseOldCoordsOfAnt(*this,x+1,y-1)) { 	
		NearFieldsPheroLvL->RightBottomCorn = Plain[x+1][y-1]->FPhero_lvl*complx(sqrt(float(2))/2,-sqrt(float(2))/2);
	}
	
	if (_direction != complx (0.,0.)) {
		const float base = 0.3;
		float _direction_arg = arg(_direction);
		res = (pow(positive(sin(_direction_arg)),base)*NearFieldsPheroLvL->Up
		+ pow(positive(sin(-1*_direction_arg)),base)*NearFieldsPheroLvL->Down
		+ pow(positive(-1*cos(_direction_arg)),base)*NearFieldsPheroLvL->Left
		+ pow(positive(cos(_direction_arg)),base)*NearFieldsPheroLvL->Right
		+ pow(positive(cos(_direction_arg + float(M_PI_4))),base)*NearFieldsPheroLvL->RightUpperCorn
		+ pow(positive(cos(_direction_arg + float(3*M_PI_4))),base)*NearFieldsPheroLvL->LeftUpperCorn
		+ pow(positive(cos(_direction_arg + float(5*M_PI_4))),base)*NearFieldsPheroLvL->LeftBottomCorn
		+ pow(positive(cos(_direction_arg + float(7*M_PI_4))),base)*NearFieldsPheroLvL->RightBottomCorn);
	}
	else {
	res = NearFieldsPheroLvL->Up
		+ NearFieldsPheroLvL->Down
		+ NearFieldsPheroLvL->Left
		+ NearFieldsPheroLvL->Right
		+ NearFieldsPheroLvL->RightUpperCorn
		+ NearFieldsPheroLvL->LeftUpperCorn
		+ NearFieldsPheroLvL->LeftBottomCorn
		+ NearFieldsPheroLvL->RightBottomCorn;
	}
	
	NearFieldsPheroLvL -> phero = complx_norm(res);

	
}






void CAnt::AMove(AntSniffResult & _sniff /*, bool FoodFound*/) {
	x_old = pos->_x;
	y_old = pos->_y;
	//while((x_old == pos->_x) && (y_old = pos->_y)) {
		_direction += float(5.0) * _sniff;
		_direction = complx_norm(_direction);
		//ant's moves depend on its status
		switch(ABasicStatus) {
			case 1:
			_direction += float(0.9) * rand_cmplx<float>(); //ant random walk
			break;
			case 2:
			_direction += float(0.1)*abs(_direction)* rand_cmplx<float>(); //ant has found food 
			break;
		}
		_direction = complx_norm(_direction);
		 mvprintw(1,30, "Sniff.: \( %.4f, %.4f \)   ",real(_sniff), imag(_sniff));

			signed char move_x, move_y; 
			complx rand_c = rand_cmplx<float>();
			move_x  = fabs(real(_direction)) >= fabs(abs(rand_c)*cos(arg(rand_c))) ? (real(_direction) > 0 ? 1 : -1) : 0;
			move_y  = fabs(imag(_direction)) >= fabs(abs(rand_c)*sin(arg(rand_c))) ? (imag(_direction) > 0 ? 1 : -1) : 0;

	/*	if (FoodFound) { 
				 pos->FLeaveF((*this));
				 pos = Plain[x_old][y_old];
				 _direction = complx(-real(_direction),-imag(_direction));
				 pos->FEnterOnF((*this));
				 }*/
		//else {
			

				if	(((move_x + x_old) >= max_x) || ((move_x + x_old) < 0) ) {
					_direction = complx(-real(_direction),imag(_direction));
				}
				else if (((move_y + y_old) >= max_y) || ((move_y + y_old) < 0)) {
					_direction = complx(real(_direction),-imag(_direction));
				}
				else if (Plain[(pos->_x + move_x)][(pos->_y + move_y)]->isAvailable()) {
				 pos->FLeaveF((*this));
				 pos = Plain[(pos->_x + move_x)][(pos->_y + move_y)];
				 pos->FEnterOnF((*this));

				}
			//}
	//}
}	
	
	


bool AntSniffResult::isBaseNear() {return abs(nearbase) == 0.?false:true; }
bool AntSniffResult::isFoodNear() {return abs(nearfood) == 0.?false:true; }
AntSniffResult::AntSniffResult() {
		complx Left = complx(0.,0.);
	complx Right = complx(0.,0.);
	complx Up = complx(0.,0.);
	complx Down = complx(0.,0.);
	complx LeftUpperCorn = complx(0.,0.);
	complx RightUpperCorn = complx(0.,0.);
	complx LeftBottomCorn = complx(0.,0.);
	complx RightBottomCorn = complx(0.,0.);
	phero = complx(0.,0.); nearbase = complx(0., 0.); nearfood = complx(0., 0.);int numOfmembers_ = 3; }



