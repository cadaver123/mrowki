
//#include "stdafx.h"
#include "CAnt.h"
#include "CField.h"
#include <time.h>
#include <stdlib.h>
#include <cmath>

typedef complex<float> complx;


using namespace std;


inline complx complx_norm(complx a) {
	return abs(a) > 1? (1/abs(a))*a:a;
}

template <typename Type>
inline Type positive(Type a) {
    return a > Type(0) ? a : Type(0);
}


inline void CAnt::AStartSearchFood() {
	_direction = complx (0.,0.);
	ABasicStatus = 1;	
}

inline void CAnt::AGoToBase() {
	_direction = complx (0.,0.);	
	ABasicStatus = 2;
}

//dopisać template do obcinania w wartości mniejszych od 0

CAnt::CAnt(CField * Plain[max_x][max_y], CField * start_field) {
	this->Plain = Plain;
	this->pos = start_field;
	pos->FBusy = 1;
	x_old = 0;
	y_old = 0;

	_direction = complx(-1,-1);

	AHungerInc = 0.1;
	srand ( time(NULL) );
	AHunger = 0.0;
	APhero_strenght =  float((500 + rand() % 500))/1000; 
	
	Invetory = new CAntInvetory(this);
	NearFieldsPheroLvL = new ASniffResult;
	ABasicStatus = 1;
}

CAnt::~CAnt() {
	delete Invetory;
	delete NearFieldsPheroLvL;
}

void CAnt::CAntLoop() {
		if ((Invetory->Food > 0.) && (ABasicStatus != 2)) {
			AGoToBase();
		}
		else if ((Invetory->Food = 0.) && (ABasicStatus != 1)) {AStartSearchFood();} 
		AHunger += AHungerInc;
		AMove(ASniff());
}


CAntInvetory::CAntInvetory(CAnt* ant) {
		Owner  = ant;
		Food = 0;
}



complx CAnt::ASniff() {
	int x = pos->_x;
	int y = pos->_y;
	char xtrans = x - x_old;
	char ytrans = y - y_old;
	complx res = complx(0.,0.);
	NearFieldsPheroLvL->Up = (((y+1) < max_y ) && (ytrans != -1))? complx(0, Plain[x][y+1]->FPhero_lvl) : 0;
	NearFieldsPheroLvL->Down = (((y-1) < max_y ) && (y != 0) && (ytrans != 1)) ? complx(0,-1 * Plain[x][y-1]->FPhero_lvl) : 0; 
	NearFieldsPheroLvL->Left = (((x-1) < max_x ) && (x != 0) && (xtrans != 1)) ? complx(-1 * Plain[x-1][y]->FPhero_lvl,0) : 0; 
	NearFieldsPheroLvL->Right = (((x+1) < max_x ) && (xtrans != -1)) ? complx(Plain[x+1][y]->FPhero_lvl,0) : 0; 
	
	NearFieldsPheroLvL->RightUpperCorn = (((x+1) < max_x) && ((y+1) < max_y) && (xtrans != -1) && (ytrans != -1)) ? Plain[x+1][y+1]->FPhero_lvl*complx(sqrt(float(2))/2,sqrt(float(2))/2) : 0;
	NearFieldsPheroLvL->LeftUpperCorn = ((x != 0) && ((y+1) < max_y)  && (xtrans != 1) && (ytrans != -1)) ? Plain[x-1][y+1]->FPhero_lvl*complx(-sqrt(float(2))/2,sqrt(float(2))/2) : 0;
	NearFieldsPheroLvL->LeftBottomCorn = ((x != 0) && (y != 0) && (xtrans != 1) && (ytrans != 1)) ? Plain[x-1][y-1]->FPhero_lvl*complx(-sqrt(float(2))/2,-sqrt(float(2))/2) : 0;
	NearFieldsPheroLvL->RightBottomCorn = (((x+1) < max_x) && (y != 0) && (xtrans != -1) && (ytrans != 1))? Plain[x+1][y-1]->FPhero_lvl*complx(sqrt(float(2))/2,-sqrt(float(2))/2) : 0;
	
	if (_direction != complx (0.,0.)) {
		float _direction_arg = arg(_direction);
		res = (positive(sin(_direction_arg))*NearFieldsPheroLvL->Up
		+ positive(sin(-1*_direction_arg))*NearFieldsPheroLvL->Down
		+ positive(-1*cos(_direction_arg))*NearFieldsPheroLvL->Left
		+ positive(cos(_direction_arg))*NearFieldsPheroLvL->Right
		+ positive(cos(_direction_arg + float(M_PI_4)))*NearFieldsPheroLvL->RightUpperCorn
		+ positive(cos(_direction_arg + float(3*M_PI_4)))*NearFieldsPheroLvL->LeftUpperCorn
		+ positive(cos(_direction_arg + float(5*M_PI_4)))*NearFieldsPheroLvL->LeftBottomCorn
		+ positive(cos(_direction_arg + float(7*M_PI_4)))*NearFieldsPheroLvL->RightBottomCorn);
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
	
	return complx_norm(res);
	 
}




ASniffResult::ASniffResult() {
	complx Left = complx(0.,0.);
	complx Right = complx(0.,0.);
	complx Up = complx(0.,0.);
	complx Down = complx(0.,0.);
	complx LeftUpperCorn = complx(0.,0.);
	complx RightUpperCorn = complx(0.,0.);
	complx LeftBottomCorn = complx(0.,0.);
	complx RightBottomCorn = complx(0.,0.);
	
}


void CAnt::AMove(complx _sniff /*, bool FoodFound*/) {
	_direction += _sniff; 
	_direction = complx_norm(_direction);
	



	srand ( time(NULL));

	signed char move_x, move_y;
	move_x  = fabs(real(_direction)) >= float(rand()%1000)/1000 ? (real(_direction) > 0 ? 1 : -1) : 0;
	move_y  = fabs(imag(_direction)) >= float(rand()%1000)/1000 ? (imag(_direction) > 0 ? 1 : -1) : 0;

/*	if (FoodFound) { 
			 pos->FLeaveF((*this));
			 pos = Plain[x_old][y_old];
			 _direction = complx(-real(_direction),-imag(_direction));
			 pos->FEnterOnF((*this));
			 }*/
	//else {
			x_old = pos->_x;
			y_old = pos->_y;
			if	(((move_x + x_old) >= max_x) || ((move_x + x_old) < 0)) {
				_direction = complx(-real(_direction),imag(_direction));
			}
			else if (((move_y + y_old) >= max_y) || ((move_y + y_old) < 0)) {
				_direction = complx(real(_direction),-imag(_direction));
			}
			else {
			 pos->FLeaveF((*this));
			 pos = Plain[(pos->_x + move_x)][(pos->_y + move_y)];
			 pos->FEnterOnF((*this));
			}
		//}
	}


