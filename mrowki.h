extern const float AMaxFoodLoadCap;
extern const int max_x;
extern const int max_y;

extern	const float	phi;
extern	const float	phi_m;
extern	const float	AMaxLoot;
	
class CAnt;
class CField{
public:
	int FieldID;
	int _x;
	int _y;
	float FPhero_lvl;
	float FFood_lvl;
	CField * FUp; 
	CField * FDown; 
	CField * FLeft; 
	CField * FRight; 

	CField(int x ,int y);
	void CField_loop();
	int FEnterOnF(CAnt *);
	int FLeaveF(CAnt *);
private:
	bool FBusy;
};

class CAntInvetory
{
public:
	CAnt*Owner; 
	float Food;
	CAntInvetory(CAnt*);
};

class CAnt {
public:
	CField *pos;
	float APhero_strenght;
	float AHunger;
	CAntInvetory * Invetory;

	CAnt(CField *);
	~CAnt();
	void CAntLoop();
	char ASniff();
	void AMove(char);


};


