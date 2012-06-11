
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
	
	FPhero_lvl = 0;
	FBusy = 0;
	FBase = false;
	++CField_cnt;
}

//Procedura POLA do glownej petli.
void CField::CField_loop() {
	if (!FBusy) {
		FPhero_lvl = ((FPhero_lvl - phi)<0)?0:(FPhero_lvl - phi); 
		FFood_lvl = ((FFood_lvl + phi_m)<1)?(FFood_lvl + phi_m):1;
	}
}

//Funkcja pojawienia sie mrowki na polu
int CField::FEnterOnF(CAnt &ant) {
	if (FFood_lvl > 0) {
			float FoodTaken;
			this->FPhero_lvl = sqrt(this->FPhero_lvl + ant.APhero_strenght);
			if(ant.Invetory->Food < AMaxFoodLoadCap) {
				FoodTaken = (AMaxLoot > FFood_lvl)?FFood_lvl:AMaxLoot;
				ant.Invetory->Food =  ((FoodTaken + ant.Invetory->Food)>0)?AMaxFoodLoadCap:(FoodTaken + ant.Invetory->Food);
				FFood_lvl = FFood_lvl - FoodTaken;
			}			
	}
	if(FBase) ant.Invetory->Food = 0.; 
	FBusy = 1;
	return 1;
}

int CField::FLeaveF(CAnt &) { 
	FBusy = 0;
	return 1;
}
