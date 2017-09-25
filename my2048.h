#ifndef _MY2048_H_
#define _MY2048_H_
#include<stdio.h>
#include<unistd.h>
#include<termios.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<iostream>
#define MAX_LN			4
#define MAX_COL		4
#define MOVE_UP		'i'
#define MOVE_DOWN		'k'
#define MOVE_LEFT		'j'
#define MOVE_RIGHT	'l'
#define GO_BACK		'b'
#define Easy 			8
#define Normal			4
#define Hard			2
#define PUNISH			50
#define STOP_NUM		2048
using namespace std;
static struct termios oldt;
void restore_terminal_settings(void);
void disable_terminal_return(void);

class my2048
{
	int 				maxNum;
	int 				Score;
	int 				step;
	char 				gameMode;
	char				strMode[10];
	bool 				isChange;
	bool 				isgetPre;
	time_t			totalTime;
	short int 		save_step;
	short int 		data[MAX_LN][MAX_COL];
	short int 		back1[MAX_LN][MAX_COL];
	short int 		back2[MAX_LN][MAX_COL];
	short int 		back3[MAX_LN][MAX_COL];
	short int 		swap_buf[4];
public:
	my2048();
	void showMember();
	void RandNum();
	bool change();
	void stepCount();
	bool test_up();
	bool test_down();
	bool test_left();
	bool test_right();
	void move_up(short int maxlen,short int maxcol);
	void move_down(short int maxlen,short int maxcol);
	void move_left(short int maxlen,short int maxcol);
	void move_right(short int maxlen,short int maxcol);
	void deal_buf(short int ln,short int col);
	bool deal_buf();
	void save_current();
	bool isGoback();
	void get_pre();
	void isWin(short int sum);
	void isGameOver();
};
#endif


