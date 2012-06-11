
//#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <curses.h>

#include "CAnt.h"
#include "CField.h"
#include <time.h> 


using namespace std;



extern const float AMaxFoodLoadCap = 1;


extern const float	phi = float(0.10);
extern const float	phi_m = float(0.10);
extern const float	AMaxLoot = float(0.2);

extern int CField_cnt; 

const int Ant_count = 1;

int main(int argc, char* argv[])
{
		
	CField  *Plain[max_x][max_y];
	
		for(int x = 0; x < max_x; ++x) {
			for(int y = 0; y < max_y; ++y) {
				Plain[x][y] = new CField(x,y);
			};
		};
	CAnt ant(Plain, Plain[0][0]);
		
		

	//display	
	srand(time(NULL));
	initscr(); 

	int row,col;	
	getmaxyx(stdscr,row,col);

	cbreak();
	noecho();
	nodelay(stdscr, TRUE);

	while(getch() != 'q') {

	for(int x = 0; x < max_x; ++x) {
		for(int y = 0; y < max_y; ++y) {
			 mvaddch(y,x,Plain[x][y]->FBusy == 1? 'X': '0');
			 Plain[x][y]->CField_loop();
			};
		};
		ant.CAntLoop();

		refresh();
		usleep(100000);
		
		
	}
	 endwin(); 
	for(int x = 0; x < max_x; ++x) {
		for(int y = 0; y < max_y; ++y) {
			delete	Plain[x][y];
		};
	};
  
   
	return 0;
}