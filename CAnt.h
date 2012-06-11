#define max_x 28
#define max_y 20
#include <complex>
using namespace std;

typedef complex<float> complx;

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


complx complx_norm(complx);


struct ASniffResult {
		complx Left, Right, Up, Down, LeftUpperCorn, RightUpperCorn, LeftBottomCorn, RightBottomCorn;
		ASniffResult();
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
		complx ASniff(); //funkcja badajca podstawowe feromony 
		void AMove(complx /*, bool*/); //funkcja odpowiedzialna za ruch mrówki
		
		//Obsługa statutusu mrówki Status:
		inline void AStartSearchFood(); //Mrówka zaczyna szukać jedzenia
		inline void AGoToBase();

		protected:
		ASniffResult * NearFieldsPheroLvL;
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


