extern const float	phi;
extern const float	phi_m;


class CAnt;

class CField{
public:
	bool FBusy;
	int FieldID;
	int _x;
	int _y;
	float FPhero_lvl;
	float FFood_lvl;
	
	CField(int x ,int y);
	void CField_loop();
	int FEnterOnF(CAnt &);
	int FLeaveF(CAnt &);

	void setAvailable(bool);
	
	bool FBase;
	
	inline bool isAvailable();
	inline bool isFoodHere();
	inline bool isBaseHere();
private:
	bool available;
};


bool doesFieldExist(int x,int y) ;
bool areThoseOldCoordsOfAnt(CAnt const &,int, int);