
//#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <curses.h>
#include<unistd.h>

#include "CAnt.h"
#include "CField.h"
#include <time.h> 
//#include <windows.h>

using namespace std;



extern const float AMaxFoodLoadCap = 1;
const int Ant_count = 2;

extern const float	phi = float(1.0)/100; //liczba o jak¹ zmniejsza siê poziom feromonu na polu
extern const float	phi_m = float(0.10);
extern const float	AMaxLoot = float(0.2);

extern int CField_cnt; 



int main(int argc, char* argv[])
{
		
	CField  *Plain[max_x][max_y];
	
		for(int x = 0; x < max_x; ++x) {
			for(int y = 0; y < max_y; ++y) {
				Plain[x][y] = new CField(x,y);
			};
		};
	CAnt ant(Plain, Plain[0][0]);
	CAnt ant1(Plain, Plain[0][1]);
	CAnt ant2(Plain, Plain[1][1]);
	CAnt ant3(Plain, Plain[1][0]);
	CAnt ant4(Plain, Plain[1][0]);
	CAnt ant5(Plain, Plain[1][0]);
	CAnt ant6(Plain, Plain[1][0]);
	
	Plain[2][2]	->FBase = true;	
	Plain[1][1]	->FBase = true;
	Plain[2][1]	->FBase = true;
	Plain[1][2]	->FBase = true;
	Plain[0][0]	->FBase = true;
	Plain[1][0]	->FBase = true;
	Plain[1][1]	->FBase = true;
	Plain[0][1]	->FBase = true;
	Plain[0][2]	->FBase = true;
	Plain[2][0]	->FBase = true;

	Plain[max_x -5][max_y - 5]	->FFood_lvl = 1;
	Plain[max_x -6][max_y - 5]		->FFood_lvl = 1;
	Plain[max_x -5][max_y - 6]		->FFood_lvl = 1;
	Plain[max_x -6][max_y - 6]		->FFood_lvl = 1;


	Plain[10][10]	->setAvailable(false);
	Plain[11][10]	->setAvailable(false);
	Plain[12][10]	->setAvailable(false);
	Plain[13][10] ->setAvailable(false);


	Plain[5][13]	->setAvailable(false);
	Plain[5][14]	->setAvailable(false);
	Plain[5][15]	->setAvailable(false);
	Plain[5][16] ->setAvailable(false);

	//display	
	srand(time(NULL));
	initscr(); 

	int row,col;	
	getmaxyx(stdscr,row,col);

	cbreak();
	noecho();
	nodelay(stdscr, TRUE);

	while(getch() != 'q') {
	 mvprintw(0,30, "Wektor kier.: \( %.4f, %.4f \)   ",real(ant._direction), imag(ant._direction));
	for(int x = 0; x < max_x; ++x) {
		for(int y = 0; y < max_y; ++y) {
			 if(Plain[x][y]->isAvailable()) mvaddch(y,x,'0');
				else  mvaddch(y,x,'+');
			 if(Plain[x][y]->FPhero_lvl > 0) mvaddch(y,x,'.');
			 if(Plain[x][y]->FBase == 1) mvaddch(y,x,'B');
			 if(Plain[x][y]->FFood_lvl > 0) mvaddch(y,x,'F');
			 if(Plain[x][y]->FBusy == 1) mvaddch(y,x,'X');
			 Plain[x][y]->CField_loop();
		
			};
		};
		ant.CAntLoop();
		ant1.CAntLoop();
		ant2.CAntLoop();
		ant3.CAntLoop();
		ant4.CAntLoop();
		ant5.CAntLoop();
		ant6.CAntLoop();
		
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
