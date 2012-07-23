#define max_x 30
#define max_y 25
#define _USE_MATH_DEFINES
#ifndef M_PI_4
#define M_PI_4 0.785398163397448309616
#endif  //  M_PI_4


#include <complex>
#include "complexx.h"




extern const float AMaxLoot;
extern const float AMaxFoodLoadCap;
extern const float AHungerInc;
/*
typedef struct complex {
	float x,y;
} complex;
*/
class CField;
class CAntInvetory;




class AntSniffResult {
public:
	complx Left;
	complx Right;
	complx Up;
	complx Down;
	complx LeftUpperCorn;
	complx RightUpperCorn;
	complx LeftBottomCorn;
	complx RightBottomCorn;
	complx phero;
	complx nearbase; 
	complx nearfood;
	bool isBaseNear();
	bool isFoodNear();
	AntSniffResult() ;
private:
	int numOfmembers_;
};

	
class CAnt {
public:
		CField  *(*Plain)[max_y];
		CField *pos;
		float APhero_strenght; //moc z jaką mrówka rozsiewa feromony
		float AHunger,AHungerInc; //poziom głodu mrówki i wielkość o jaką rośnie
		
		CAntInvetory * Invetory; //inwentarz
		complx _direction; //kierunek marszu
		int x_old,y_old; //współrzędne ostatnio zajmowanego pola
		

		CAnt(CField  *[max_x][max_y],CField * ); // 
		~CAnt();
		
		void CAntLoop(); //podstawowa pętla dla mrówki
		AntSniffResult & ASniff(); //funkcja badajca podstawowe feromony 
		void AMove(AntSniffResult & /*, bool*/); //funkcja odpowiedzialna za ruch mrówki
		
		//Obsługa statutusu mrówki Status:
		inline void AStartSearchFood(); //Mrówka zaczyna szukać jedzenia
		inline void AGoToBase();


		protected:
		AntSniffResult * NearFieldsPheroLvL;
		short int ABasicStatus;
		inline void AStatSet(int);
};

class CAntInvetory
{
	public:
		CAnt*Owner; 
		float Food;
		
		CAntInvetory(CAnt*);
};



