#include "my2048.h"



void my2048::save_current()
{
		switch(save_step)
		{
			case 0:
				memcpy(back1,data,sizeof(data));
				save_step=1;
				break;
			case 1:
				memcpy(back2,data,sizeof(data));
				save_step=2;
				break;
			case 2:
				memcpy(back3,data,sizeof(data));
				save_step=3;
				break;
			default:
				memcpy(back1,back2,sizeof(back2));
				memcpy(back2,back3,sizeof(back3));
				memcpy(back3,data,sizeof(data));
				break;
		}
	isgetPre=false;
}

void my2048::get_pre()
{	
	if(save_step<4&&save_step>0)
		switch(save_step)
		{
			case 1:
				memcpy(data,back1,sizeof(back1));
				memset(back1,0,sizeof(back1));
				save_step=0;
				isgetPre=true;
				stepCount();
				isChange=false;
				Score-=PUNISH;
				break;
			case 2:
				memcpy(data,back2,sizeof(back2));
				memset(back2,0,sizeof(back2));
				save_step=1;
				isgetPre=true;
				stepCount();
				isChange=false;
				Score-=PUNISH;
				break;
			case 3:
				memcpy(data,back3,sizeof(back3));
				memset(back3,0,sizeof(back3));
				save_step=2;
				isgetPre=true;
				stepCount();
				isChange=false;
				Score-=PUNISH;
				break;
			default:
				break;
		}
		
}








bool my2048::deal_buf()
{
	for(int i=0;i<MAX_LN-1;i++)
		for(int j=0;j<MAX_LN;j++)
		{
			if(j<3&&swap_buf[j]==0&&swap_buf[j+1]!=0)
				return false;
			else if(j==3&&swap_buf[j-1]==0&&swap_buf[j]!=0)
				return false;
		}
		
	for(int i=0;i<MAX_LN;i++)
	{
		if(swap_buf[i]!=0 && i<3)
		{
			if(swap_buf[i]==swap_buf[i+1])
				return false;
		}else if(i==3&&swap_buf[i]!=0&&swap_buf[i-1]==swap_buf[i])
				return false;
	}
	return true;
}


void my2048::isGameOver()
{
	if(test_right()&&test_left()&&test_down()&&test_up())
	{
		//system("clear");
		cout<<"\n\n\n";
		cout<<"\tI'm so sorry,you lost the game. :("<<endl;
		cout<<"\n\n\n\n\n";
		getchar();
		exit(0);
	}
}


















void my2048::deal_buf(short int ln,short int direction)
{
	static bool start=true;
	if(start)
		totalTime=time(NULL),start=false;	

	for(int i=0;i<MAX_LN-1;i++)
		for(int j=0;j<MAX_LN;j++)
		{
			if(j<3&&swap_buf[j]==0&&swap_buf[j+1]!=0)
			{
				swap(swap_buf[j],swap_buf[j+1]);
				isChange=true;
			}else if(j==3&&swap_buf[j-1]==0&&swap_buf[j]!=0){
				swap(swap_buf[j],swap_buf[j-1]);
				isChange=true;
			}
		}
		
	for(int i=0;i<MAX_LN;i++)
		if(swap_buf[i]!=0 && i<3)
		{
			if(swap_buf[i]==swap_buf[i+1])
			{
				swap_buf[i]+=swap_buf[i+1];
				swap_buf[i+1]=0;
				isChange=true;
				Score+=swap_buf[i];
				isWin(swap_buf[i]);
			}
		}else if(i==3&&swap_buf[i]!=0&&swap_buf[i-1]==swap_buf[i]){
				swap_buf[i-1]+=swap_buf[i];
				swap_buf[i]=0;
				isChange=true;
				Score+=swap_buf[i-1];
				isWin(swap_buf[i]);
		}


	for(int i=0;i<MAX_LN;i++)
		for(int j=0;j<MAX_LN;j++)
		{
			if(j<3&&swap_buf[j]==0&&swap_buf[j+1]!=0)
				swap(swap_buf[j],swap_buf[j+1]);
			else if(j==3&&swap_buf[j-1]==0&&swap_buf[j]!=0)
				swap(swap_buf[j],swap_buf[j-1]);
		}
			

	switch(direction)
	{
		case MOVE_UP:
			for(int i=0;i<MAX_LN;i++)
				data[i][ln]=swap_buf[i];
				break;
		case MOVE_DOWN:
			for(int i=0,j=MAX_LN-1;i<MAX_LN;i++,j--)
				data[j][ln]=swap_buf[i];
				break;	
		case MOVE_LEFT:
			for(int i=0;i<MAX_LN;i++)
				data[ln][i]=swap_buf[i];
				break;
		case MOVE_RIGHT:
			for(int i=0,j=MAX_LN-1;i<MAX_LN;i++,j--)
				data[ln][j]=swap_buf[i];
				break;
	}
}	



void my2048::isWin(short int sum)
{
	if(sum==STOP_NUM)
	{
		int over_time=time(NULL)-totalTime;
		system("clear");
		cout<<"\n\n\n\n\n";
		cout<<"\t$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n";
		cout<<"\t$      You're  Winner!!!      $\n";
		cout<<"\t$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n";
		cout<<"\t\tGame  mode:"<<strMode<<endl;
		cout<<"\t\tYour Scoue:"<<Score<<endl;
		cout<<"\t\tStep Count:"<<step<<endl;
		cout<<"\t\tTotal Time:"<<over_time<<endl;//<<endl;
		cout<<"\n\n\n\n\n";
		getchar();
		exit(0);
	}else if(sum > maxNum){
		maxNum=sum;
	}

}

void my2048::RandNum()
{
	short int value=0;
	while(true)
	{	
		char ln=rand()%MAX_LN;
		char col=rand()%MAX_COL;
		switch(gameMode)
		{
			case Easy:
				value=rand()%2 ? 4:8 ;
				break;
			case Normal:
				value=rand()%2 ? 2:4;
				break;
			case Hard:
				value=2;
				break;
			default:
				break;
		}
		if(!this->data[ln][col])
		{
			this->data[ln][col]=value;
			break;
		}
	}
}

void my2048::stepCount()
{
	step++;
}
bool my2048::isGoback()
{
	return !isgetPre;
}
bool my2048::change()
{
	bool old=this->isChange;
	this->isChange=false;
	return old;
}

void my2048::showMember()
{
	system("clear");
	cout<<endl<<endl;
	cout<<"\t[i](up),[k](down),[j](left),[l](right)"<<endl;
	cout<<"\t[b]Restore the previous step,Saved["<<save_step<<"]"<<endl;
	cout<<"\tStep:"<<step<<"\tCurrent Score:"<<Score<<endl;
	cout<<"\tDifficulty:"<<strMode<<endl;
	cout<<endl<<endl;
	for(int i=0;i<MAX_LN;i++)
	{	
		cout<<"\t\t";
		for(int j=0;j<MAX_COL;j++)
		{
			if(data[i][j])
				cout<<data[i][j];
			else
				cout<<" ";
			cout<<(j==MAX_COL-1 ? "\n\n":"\t");
		}
	}
}

my2048::my2048()
{
	memset(data,0,sizeof(data));
	memset(back1,0,sizeof(back1));
	memset(back2,0,sizeof(back2));
	memset(back3,0,sizeof(back3));
	memset(strMode,0,sizeof(strMode));
	memset(swap_buf,0,sizeof(swap_buf));
	maxNum=0;
	isChange=false;
	isgetPre=false;
	save_step=0;
	step=0;
	Score=0;
	system("clear");
	cout<<endl<<endl<<"\tPlease select the game difficulty:"<<endl;
	cout<<"\t[1]:Easy  [2]:Normal  [3]:Hard"<<endl;
	bool isSelect=true;
	while(isSelect)
	{
		gameMode=getchar();
		switch(gameMode)
		{
			case 49:
				gameMode=Easy;
				strcat(strMode,"Easy");
				isSelect=false;
				break;
			case 50:
				gameMode=Normal;
				strcat(strMode,"Normal");
				isSelect=false;
				break;
			case 51:
				gameMode=Hard;
				strcat(strMode,"Hard");
				isSelect=false;
				break;
			default:
				break;
		}
	}
}

bool my2048::test_up()
{
	memset(swap_buf,0,sizeof(swap_buf));
	for(int i=0;i<MAX_LN;i++)
	{
		for(int j=0;j<MAX_COL;j++)
			swap_buf[j]=data[j][i];
		if(!this->deal_buf())return false;
	}
	return true;
}

bool my2048::test_down()
{
	memset(swap_buf,0,sizeof(swap_buf));
	for(int i=0;i<MAX_LN;i++)
	{
		for(int j=0,k=MAX_COL-1;k>=0;j++,k--)
			swap_buf[j]=data[k][i];
		if(!this->deal_buf())return false;
	}
	return true;
}

bool my2048::test_left()
{
	memset(swap_buf,0,sizeof(swap_buf));
	for(int i=0;i<MAX_LN;i++)
	{
		for(int j=0;j<MAX_COL;j++)
			swap_buf[j]=data[i][j];
		if(!this->deal_buf())return false;
	}
	return true;
}

bool my2048::test_right()
{
	memset(swap_buf,0,sizeof(swap_buf));
	for(int i=0;i<MAX_LN;i++)
	{
		for(int j=0,k=MAX_COL-1;j<MAX_COL;j++,k--)
			swap_buf[j]=data[i][k];
		if(!this->deal_buf())return false;
	}
	return true;
}


void my2048::move_up(short int maxlen,short int maxcol)
{
	memset(swap_buf,0,sizeof(swap_buf));
	for(int i=0;i<maxlen;i++)
	{
		for(int j=0;j<maxcol;j++)
			swap_buf[j]=data[j][i],data[j][i]=0;
		this->deal_buf(i,MOVE_UP);
	}
}

void my2048::move_down(short int maxlen,short int maxcol)
{
	memset(swap_buf,0,sizeof(swap_buf));
	for(int i=0;i<maxlen;i++)
	{
		for(int j=0,k=maxcol-1;k>=0;j++,k--)
			swap_buf[j]=data[k][i],data[k][i]=0;
		this->deal_buf(i,MOVE_DOWN);
	}
}

void my2048::move_left(short int maxlen,short int maxcol)
{
	memset(swap_buf,0,sizeof(swap_buf));
	for(int i=0;i<maxlen;i++)
	{
		for(int j=0;j<maxcol;j++)
			swap_buf[j]=data[i][j];
		this->deal_buf(i,MOVE_LEFT);
	}
}

void my2048::move_right(short int maxlen,short int maxcol)
{	
	memset(swap_buf,0,sizeof(swap_buf));
	for(int i=0;i<maxlen;i++)
	{
		for(int j=0,k=maxcol-1;j<maxcol;j++,k--)
			swap_buf[j]=data[i][k];
		this->deal_buf(i,MOVE_RIGHT);
	}
}


//restore terminal settings
void restore_terminal_settings(void)
{
    // Apply saved settings
    tcsetattr(0, TCSANOW, &oldt); 
}

//make terminal read 1 char at a time
void disable_terminal_return(void)
{
    struct termios newt;
    
    //save terminal settings
    tcgetattr(0, &oldt); 
    //init new settings
    newt = oldt;  
    //change settings
    newt.c_lflag &= ~(ICANON | ECHO);
    //apply settings
    tcsetattr(0, TCSANOW, &newt);
    
    //make sure settings will be restored when program ends
    atexit(restore_terminal_settings);
}
