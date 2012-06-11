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
	
	
	bool FBase;

};
