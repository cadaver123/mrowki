
//#include "stdafx.h"
#include <math.h>
#include "CField.h"
#include "CAnt.h"

using namespace std;

int CField_cnt; 

CField::CField(int x, int y){
	//Warunki brzegowe - jeli pole ich nie spe³nia to pope³nia samobójstwo. 
	_x = x;
	_y = y;
	//Definicja p³aszczyzny
	
	FFood_lvl = 0;
	FPhero_lvl = 0;
	FBusy = 0;
	available = true;
	FBase = false;
	++CField_cnt;
}

//Glownej petla pola.
void CField::CField_loop() {
	if (!FBusy) {
		FPhero_lvl = ((FPhero_lvl - phi)<0)?0:(FPhero_lvl - phi); 
		//If field is border then phero should get smaller faster
		if (this->_x == 1 || this->_x == max_x - 1 || this->_y == 1 || this->_y == max_y - 1)
			FPhero_lvl = FPhero_lvl - 0.2*FPhero_lvl; 
		//FFood_lvl = ((FFood_lvl + phi_m)<1)?(FFood_lvl + phi_m):1;
	}
}

//Funkcja pojawienia sie mrowki na polu
int CField::FEnterOnF(CAnt &ant) {
	if (FFood_lvl > 0) {
			float FoodTaken;
			if(ant.Invetory->Food < AMaxFoodLoadCap) {
				FoodTaken = (AMaxLoot > FFood_lvl)?FFood_lvl:AMaxLoot;
				ant.Invetory->Food =  ((FoodTaken + ant.Invetory->Food)>0)?AMaxFoodLoadCap:(FoodTaken + ant.Invetory->Food);
				FFood_lvl = FFood_lvl - FoodTaken;
			}			
	}
	if(FBase) ant.Invetory->Food = 0.; 
	FPhero_lvl += ant.APhero_strenght; 
	FBusy = 1;
	return 1;
}

int CField::FLeaveF(CAnt &) { 
	FBusy = 0;
	return 1;
}

bool CField::isAvailable() {return available;}
void CField::setAvailable(bool b) {this->available = b;}

bool doesFieldExist(int x,int y) { return (x >= 0) && (x <= max_x - 1) && (y >= 0) && (y <= max_y - 1)?true:false;}
bool areThoseOldCoordsOfAnt(CAnt const & a,int x, int y) {
	return ((a.x_old == x) && (a.y_old ==y))?true:false;
}

	bool CField::isFoodHere(){return FBase;}
	bool CField::isBaseHere(){return FFood_lvl > 0.?true:false;};