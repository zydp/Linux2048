#include "my2048.h"

int main()
{
	unsigned char ch;
	disable_terminal_return();
	srand(time(NULL));
	my2048 game;  
	game.RandNum();
	game.RandNum();
	game.showMember();
	while(true)
	{
		ch = getchar();
		cout<<"\b"<<endl;
		switch(ch)
		{
			case MOVE_UP:
				game.save_current();
				game.move_up(MAX_LN,MAX_COL);
				break;
			case MOVE_DOWN:
				game.save_current();
				game.move_down(MAX_LN,MAX_COL);
				break;
			case MOVE_LEFT:
				game.save_current();
				game.move_left(MAX_LN,MAX_COL);
				break;
			case MOVE_RIGHT:
				game.save_current();
				game.move_right(MAX_LN,MAX_COL);
				break;
			case GO_BACK:
				game.get_pre();
			default:
				break;
		}
		if(game.isGoback())
			if(game.change())
			{
				game.RandNum();
				game.stepCount();
			}
			game.showMember();
			game.isGameOver();
	}
	return 0;
}


