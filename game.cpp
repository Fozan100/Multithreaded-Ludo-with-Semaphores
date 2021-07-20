
//MUHAMMAD FOZAN 19I-0507
//MUHAMMAD BILAL 19I-0636

#ifndef CENTIPEDE_CPP_
#define CENTIPEDE_CPP_
//#include "Board.h"
#include "util.h"
#include <iostream>
#include<string>
#include<cmath> 
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <semaphore.h>
using namespace std;

pthread_t mainId,killerthread;
int totaltokens=1;
int stopmaster=false;

int previousturn=0;

pthread_t playerID1[4];
int allpassed[4];
sem_t SemDice;
sem_t SemBoard;
int playing=1;
int playingboard=1;
int Diceonboard=0;
int window=1;
int Winningplayer[3]={1,2,3};
int counter1=0;

int Totalkills[4]={0,0,0,0};	//Kills count for all Players 1,2,3,4

int IndexVariable=0;			//Variable used for deciding randomly that which token should be moved
int diceroll=0;				//Value after rolling dice

int loc[4][4]=
{
	{0,0,0,0},	//Current location of 4 tokens of 4 Players
	{0,0,0,0},
	{0,0,0,0},
	{0,0,0,0},
};

int HomeX[4][4]=		//Used for returning a token to homeyard after a hit
{
	{743,800,743,686},	//X axis of all tokens Green
	{302,358,302,245},		//X axis of all tokens Red
	{302,358,302,245},	//X axis of all tokens Blue
	{743,800,743,686},	//X axis of all tokens Yellow
};
int HomeY[4][4]=		//Used for returning a token to homeyard after a hit
{
	{152,200,255,200},	//Y axis of all tokens Green
	{152,200,255,200},	//Y axis of all tokens Red
	{590,641,700,641},	//Y axis of all tokens Blue
	{590,641,700,641},	//Y axis of all tokens Yellow
};
int tokenX[4][4]=		//X-axis Location of all 4 tokens of 4 players
{
	{743,800,743,686},	//X axis of all tokens Green
	{302,358,302,245},		//X axis of all tokens Red
	{302,358,302,245},	//X axis of all tokens Blue
	{743,800,743,686},	//X axis of all tokens Yellow
};
int tokenY[4][4]=		//Y-axis Location of all 4 tokens of 4 players
{
	{152,200,255,200},	//Y axis of all tokens Green
	{152,200,255,200},	//Y axis of all tokens Red
	{590,641,700,641},	//Y axis of all tokens Blue
	{590,641,700,641},	//Y axis of all tokens Yellow
};

bool status[4][4]=		//Status of 4 tokens of 4 players that Where move is possible or not
{
	{0,0,0,0},
	{0,0,0,0},
	{0,0,0,0},
	{0,0,0,0},
};		//Board entry on 6 status


double COR[4][58][2] =
{
	{
		{770,165},{809.6,365},{762.6,365},{715.6,365},{668.6,365},{621.6,365},{574.6,318},{574.6,271},{574.6,224},{574.6,177},{574.6,130},{574.6,83},{521.3,83}, {468,83},{468,130},{468,177},{468,224},{468,271},{468,318},{421,365},{374,365},{327,365},{280,365},{233,365},{186,365},{186,418.3},{186,471.6},{233,471.6},{280,471.6},{327,471.6},{374,471.6},{421,471.6},{468,524.9},{468,571.9},{468,618.9},{468,665.9},{468,712.9},{468,759.9},{521.3,759.9},{574.6,759.9},{574.6,712.9},{574.6,665.9},{574.6,618.9},{574.6,571.9},{574.6,524.9},{621.6,471.6},{668.6,471.6},{715.6,471.6},{762.6,471.6},{809.6,471.6},{856.6,471.6},{856.6,418.3},{809.6,418.3},{762.6,418.3},{715.6,418.3},{668.6,418.3},{621.6,418.3},{574.6,418.3},
	},
	{
		{360,200},{468,130},{468,177},{468,224},{468,271},{468,318},{421,365},{374,365},{327,365},{280,365},{233,365},{186,365},{186,418.3},{186,471.6},{233,471.6},{280,471.6},{327,471.6},{374,471.6},{421,471.6},{468,524.9},{468,571.9},{468,618.9},{468,665.9},{468,712.9},{468,759.9},{521.3,759.9},{574.6,759.9},{574.6,712.9},{574.6,665.9},{574.6,618.9},{574.6,571.9},{574.6,524.9},{621.6,471.6},{668.6,471.6},{715.6,471.6},{762.6,471.6},{809.6,471.6},{856.6,471.6},{856.6,418.3},{856.6,365},{809.6,365},{762.6,365},{715.6,365},{668.6,365},{621.6,365},{574.6,318},{574.6,271},{574.6,224},{574.6,177},{574.6,130},{574.6,83},{521.3,83},{521.3,130},{521.3,177},{521.3,224},{521.3,271},{521.3,318},{521.3,365},
	},
	{
		{310,635},{233,471.6},{280,471.6},{327,471.6},{374,471.6},{421,471.6},{468,524.9},{468,571.9},{468,618.9},{468,665.9},{468,712.9},{468,759.9},{521.3,759.9},{574.6,759.9},{574.6,712.9},{574.6,665.9},{574.6,618.9},{574.6,571.9},{574.6,524.9},{621.6,471.6},{668.6,471.6},{715.6,471.6},{762.6,471.6},{809.6,471.6},{856.6,471.6},{856.6,418.3},{856.6,365},{809.6,365},{762.6,365},{715.6,365},{668.6,365},{621.6,365},{574.6,318},{574.6,271},{574.6,224},{574.6,177},{574.6,130},{574.6,83},{521.3,83}, {468,83},{468,130},{468,177},{468,224},{468,271},{468,318},{421,365},{374,365},{327,365},{280,365},{233,365},{186,365},{186,418.3},{233,418.3},{280,418.3},{327,418.3},{374,418.3},{421,418.3},{468,418.3},
	},
	{
		{770,635},{574.6,712.9},{574.6,665.9},{574.6,618.9},{574.6,571.9},{574.6,524.9},{621.6,471.6},{668.6,471.6},{715.6,471.6},{762.6,471.6},{809.6,471.6},{856.6,471.6},{856.6,418.3},{856.6,365},{809.6,365},{762.6,365},{715.6,365},{668.6,365},{621.6,365},{574.6,318},{574.6,271},{574.6,224},{574.6,177},{574.6,130},{574.6,83},{521.3,83},{468,83},{468,130},{468,177},{468,224},{468,271},{468,318},{421,365},{374,365},{327,365},{280,365},{233,365},{186,365},{186,418.3},{186,471.6},{233,471.6},{280,471.6},{327,471.6},{374,471.6},{421,471.6},{468,524.9},{468,571.9},{468,618.9},{468,665.9},{468,712.9},{468,759.9},{521.3,759.9},{521.3,712.9},{521.3,665.9},{521.3,618.9},{521.3,571.9},{521.3,524.9},{521.3,477.9},
	},
};

void SetCanvasSize(int width, int height) {
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
}
double safeplace[8][2]=
{
	{468,130},
	{280,365},
	{233,471.6},
	{468,665.9},
	{574.6,712.9},
	{762.6,471.6},
	{809.6,365},
	{574.6,177},
};
void Dice(int number)
{
	if (number==1)
	{
		DrawSquare( 50 , 80 ,80,colors[NAVY]);
		DrawCircle(90,120,8,colors[RED]);
	}
	else if(number==2)
	{
		DrawSquare( 50 , 80 ,80,colors[NAVY]);
		DrawCircle(70,140,8,colors[WHITE]);
		DrawCircle(110,100,8,colors[WHITE]);
	}
	else if (number==3)
	{
		DrawSquare( 50 , 80 ,80,colors[NAVY]);
		DrawCircle(70,140,8,colors[WHITE]);
		DrawCircle(90,120,8,colors[WHITE]);
		DrawCircle(110,100,8,colors[WHITE]);
	}
	else if(number ==4)
	{
	DrawSquare( 50 , 80 ,80,colors[NAVY]);
	DrawCircle(70,140,8,colors[WHITE]);
	DrawCircle(70,100,8,colors[WHITE]);
	DrawCircle(110,100,8,colors[WHITE]);
	DrawCircle(110,140,8,colors[WHITE]);
	}
	else if(number ==5)
	{
	DrawSquare( 50 , 80 ,80,colors[NAVY]);
	DrawCircle(70,140,8,colors[WHITE]);
	DrawCircle(70,100,8,colors[WHITE]);
	DrawCircle(90,120,8,colors[WHITE]);
	DrawCircle(110,100,8,colors[WHITE]);
	DrawCircle(110,140,8,colors[WHITE]);
	}
	else if (number==6)
	{
	DrawSquare( 50 , 80 ,80,colors[NAVY]);
	DrawCircle(70,140,8,colors[WHITE]);
	DrawCircle(70,100,8,colors[WHITE]);
	DrawCircle(70,120,8,colors[WHITE]);
	DrawCircle(110,120,8,colors[WHITE]);
	DrawCircle(110,100,8,colors[WHITE]);
	DrawCircle(110,140,8,colors[WHITE]);
	}
}	

void* Player1thread(void* arg)
{
	int playerno=*(int*)arg;
	int diceinthread[3]={0,0,0};		//Sixe is 3 because 3 rolls are possible in some cases
	bool ThreeSixes=0;
	
		
		srand(time(NULL));
		bool turnagain=1;
		int counter=0;
		if(playerno==previousturn)		//if(same player appears after the iteration)
		{	sleep(3);
		}
		sem_wait(&SemDice);
		while(turnagain)				//If rolling dice generates 6 then bonus turn is provided
		{
			
			playing=playerno+1;
			diceroll = rand()%6+1;
			diceinthread[counter]=diceroll;		//"Diceroll" is the main reason for semaphore of dice so that it can be accessed by one player at a time
			cout<<"Dice : "<<diceinthread[counter]<<endl;
			
			turnagain=0;
			if(diceinthread[counter]==6)		//If dice = 6 then turn again
			{
				turnagain=1;
				counter++;
			}
			if(diceinthread[2]==6)		//If 3 Sixes are generated
			{
				ThreeSixes=true;
				break;
			}
			sleep(1);
			previousturn=playerno;		//Using Previous turn to check that it does not repeat in the next iteration
		}
		sem_post(&SemDice);
	
		if(!ThreeSixes)					//Do not access board if 3 sixes
		{
			sem_wait(&SemBoard);
			for(int k=0;k<3;k++)
			{
				playingboard=playerno+1;
				Diceonboard=diceinthread[k];
				IndexVariable = rand()%totaltokens;			//Random function to get the token number to move
				cout<<"Token No. : "<<IndexVariable<<endl;
				int Enterloop=1;
				if(diceinthread[k]==6)
					Enterloop=1;
				else if(diceinthread[k]!=6 && (status[playerno][0]!=0 || status[playerno][1]!=0 || status[playerno][2]!=0 || status[playerno][3]!=0))
				{
					while(status[playerno][IndexVariable]==0)
					{
						IndexVariable = rand()%totaltokens;
						cout<<"Token No. : "<<IndexVariable<<endl;
					}
					Enterloop=1;
				}
				else
					Enterloop=0; 
				
				if(Enterloop)
				{
					sleep(1);
					if( diceinthread[k]!=0)
					{
						
						if(diceinthread[k]==6 && status[playerno][IndexVariable]==0 && loc[playerno][IndexVariable]==0)			//If dice = 6 and token is in homeyard.
						{
							tokenX[playerno][IndexVariable]=int(COR[playerno][1][0]);		//Move the token to starting point
							tokenY[playerno][IndexVariable]=int(COR[playerno][1][1]);
							status[playerno][IndexVariable]=1;
							loc[playerno][IndexVariable]=0;
						}
						else if( status[playerno][IndexVariable]==1 )		//When move is possible on selected token
						{
							if(loc[playerno][IndexVariable]+1+diceinthread[k]<52)		//Move the tokken based on dice only if moving the token based on dice does not move it in the winning line of the player
							{
								//if(IndexVariable!=0 ){
								cout<<loc[playerno][IndexVariable]<<" "<<diceinthread[k]<<endl;
								tokenX[playerno][IndexVariable]=int(COR[playerno][1+loc[playerno][IndexVariable]+diceinthread[k]][0]);
								tokenY[playerno][IndexVariable]=int(COR[playerno][1+loc[playerno][IndexVariable]+diceinthread[k]][1]);
								loc[playerno][IndexVariable]+=diceinthread[k];
								//}
							}
							else if(loc[playerno][IndexVariable]+1+diceinthread[k]<58 && loc[playerno][IndexVariable]+1+diceinthread[k]>51 && Totalkills[playerno]>0)		//Enter the token in the winning lane it it has removed even one of the opponent
							{
								cout<<loc[playerno][IndexVariable]<<" "<<diceinthread[k]<<endl;
								tokenX[playerno][IndexVariable]=int(COR[playerno][1+loc[playerno][IndexVariable]+diceinthread[k]][0]);
								tokenY[playerno][IndexVariable]=int(COR[playerno][1+loc[playerno][IndexVariable]+diceinthread[k]][1]);
								loc[playerno][IndexVariable]+=diceinthread[k];
							}
							else if(loc[playerno][IndexVariable]+1+diceinthread[k]>51 && Totalkills[playerno]<1)		//If the player has not removed an opponent token on the board and is about to enter the winning lane
							{
								tokenX[playerno][IndexVariable]=int(COR[playerno][1][0]);				//Move the token to starting position
								tokenY[playerno][IndexVariable]=int(COR[playerno][1][1]);
								status[playerno][IndexVariable]=1;
								loc[playerno][IndexVariable]=0;

								cout<<loc[playerno][IndexVariable]<<" "<<diceinthread[k]<<endl;			//Then move according to the dice
								tokenX[playerno][IndexVariable]=int(COR[playerno][1+loc[playerno][IndexVariable]+diceinthread[k]][0]);
								tokenY[playerno][IndexVariable]=int(COR[playerno][1+loc[playerno][IndexVariable]+diceinthread[k]][1]);
								loc[playerno][IndexVariable]+=diceinthread[k];
							}
							else
							{
								int reservestatus[totaltokens];			//An array to store the status of all the tokens of the player
								for(int res=0;res<totaltokens;res++)
									reservestatus[res]=status[playerno][res];

								for(int chang=0;chang<totaltokens;chang++)		
								{
									if(loc[playerno][chang]+1+diceinthread[k]>51 && Totalkills[playerno]<1)		//Change the status of those tokens to Zero which have 0 kills
										status[playerno][chang]=0;
								}
								for(int chang=0;chang<totaltokens;chang++)
								{
									if(loc[playerno][chang]+1+diceinthread[k]>57 && Totalkills[playerno]>0)		//Change the status of those tokens to Zero which have kills but the if moves according to dice it will get out of board
										status[playerno][chang]=0;
								}

								if( status[playerno][0]!=0 || status[playerno][1]!=0 || status[playerno][2]!=0 || status[playerno][3]!=0)	//if status of any token in not 0
								{
									while(status[playerno][IndexVariable]==0)
									{
										IndexVariable = rand()%totaltokens;		//Random function to get the token number to move
										cout<<"Token No. : "<<IndexVariable<<endl;
									}
									tokenX[playerno][IndexVariable]=int(COR[playerno][1+loc[playerno][IndexVariable]+diceinthread[k]][0]);
									tokenY[playerno][IndexVariable]=int(COR[playerno][1+loc[playerno][IndexVariable]+diceinthread[k]][1]);
									loc[playerno][IndexVariable]+=diceinthread[k];


								}

								for(int res=0;res<totaltokens;res++)
									status[playerno][res]=reservestatus[res];	//Assign the status again which was stored before

							}

						}
						for(int complete=0;complete<totaltokens;complete++)
						{
							if(loc[playerno][complete]==56)
								status[playerno][complete]=0;
						}
						
					}
				}
				
				
				if(k+1<3 && diceinthread[k+1]==0)
					break;
				sleep(1);
				
			}
			
			cout<<endl;
			sem_post(&SemBoard);
		}

			pthread_exit(NULL);
	

}

void* CollissionAndWinThread(void* arg)
{

	int CurrPlayr=*(int*)arg;
	sem_wait(&SemBoard);
	for(int i=0;i<4;i++)			//4 Players tokkens
	{
		for(int j=0;j<4;j++)		//Matching with 3 other Players' Tokens
		{
			if(i!=j)
			{
				for(int k=0;k<totaltokens;k++)	//total Tokens Matching
				{
					for(int l=0;l<totaltokens;l++)	//Matching with other total tokens of opponent
					{
						if(tokenX[i][k]==tokenX[j][l] && tokenY[i][k]==tokenY[j][l])		//If two tokens position match
						{
							
							bool SafeP=0;
							for(int S=0;S<8;S++)		//Loop to check whether it is a safeplace or not
							{
								if(tokenX[i][k]==int(safeplace[S][0]) && tokenY[i][k]==int(safeplace[S][1]))
								{
									SafeP=1;
									break;
								}
							}
							if(!SafeP)		//If matching point is not a safe point
							{
								int Kill=0;			//Player which is to be killed
								int KillNo=0;		//Token No to be killed
								if(i!=CurrPlayr)
								{
									Kill=i;
									KillNo=k;
								}
								else
								{
									Kill=j;
									KillNo=l;
								}
								status[Kill][KillNo]=0;
								loc[Kill][KillNo]=0;
								tokenX[Kill][KillNo]=HomeX[Kill][KillNo];
								tokenY[Kill][KillNo]=HomeY[Kill][KillNo];
								Totalkills[CurrPlayr]++;

								cout<<"Player "<<Kill+1<<" Token : "<<KillNo+1<<" Killed\n";
							}
							else
								cout<<"\nMatching but safepoint of Player "<<i+1<<" Token "<<k+1<<" with Player "<<j+1<<" Token "<<l+1<<"\n\n";
						}
					}
				}
			}
		}
	}
	allpassed[CurrPlayr]=0;
	for(int pass=0;pass<totaltokens;pass++)		
	{	cout<<loc[CurrPlayr][pass]<<' ';
		if(loc[CurrPlayr][pass]==56)		//If Tokens enter the triangle then increment allpassed
			allpassed[CurrPlayr]++;
	}
	if(counter1<3)
	{
		if(allpassed[CurrPlayr]==totaltokens)
		{
			Winningplayer[counter1]=CurrPlayr+1;
			counter1++;
		}
	}
	sem_post(&SemBoard);
	sleep(1);
	
	pthread_exit(NULL);
}
void* Mainthreadfunction(void* arg)
{
	/*
	tokenX[2][0]=int(COR[2][1+56][0]);
	tokenY[2][0]=int(COR[2][1+56][1]);
	loc[2][0]=56;
	status[2][0]=1;
	Totalkills[2]=1;*/

	while(1)
	{
		for(int i=0;i<4;i++)
		{
			if(allpassed[i]!=totaltokens)		//Check if all tokens have entered triangle
			{
				pthread_create(&playerID1[i], NULL, Player1thread, &i);
				
				sleep(1);
				pthread_create(&killerthread,NULL,CollissionAndWinThread,&i);		//Thread to check Collission and Winning
				
			}
			else
			{
				cout<<"\n\n\nPlayer "<<i+1<<" all Tokens finished.\n\n\n";
			}
		}
		for(int i=0;i<4;i++)
		{
			if(allpassed[i]!=totaltokens)		//Check if all tokens have entered triangle
			{
				pthread_join(playerID1[i],NULL);
			}
			if(stopmaster)						//Stopping condition for Game and Master thread
				pthread_exit(NULL);
		}

		
	}
	
}
//
void displayTurn()		//Function to display Turn and Hit Rate
{

	DrawString( 20, 500, "Player on Board", colors[BLACK]);
	DrawString( 30, 480, "Turn : "+to_string(playingboard), colors[BLACK]);
	DrawString( 30, 460, "Hit rate : ", colors[BLACK]);
	DrawString( 80, 440, to_string(Totalkills[playingboard-1]), colors[BLACK]);
	DrawString( 30, 420, "Dice on board : ", colors[BLACK]);
	DrawString( 80, 400, to_string(Diceonboard), colors[BLACK]);

	DrawString( 30, 220, "Player on Dice : ", colors[BLACK]);
	DrawString( 80, 200, to_string(playing), colors[BLACK]);
}
void displayYellowTokens()
{
	for(int i=0;i<totaltokens;i++)
	{
		DrawRoundRect(tokenX[3][i],tokenY[3][i],35,35,colors[YELLOW],5);
		DrawString( tokenX[3][i]+11, tokenY[3][i]+11, to_string(i+1), colors[WHITE]);
	}
}
void displayBlueTokens()
{
	for(int i=0;i<totaltokens;i++)
	{
		DrawRoundRect(tokenX[2][i],tokenY[2][i],35,35,colors[BLUE],5);
		DrawString( tokenX[2][i]+11, tokenY[2][i]+11, to_string(i+1), colors[WHITE]);
	}
}
void displayRedTokens()
{
	for(int i=0;i<totaltokens;i++)
	{
		DrawRoundRect(tokenX[1][i],tokenY[1][i],35,35,colors[RED],5);
		DrawString( tokenX[1][i]+11, tokenY[1][i]+11, to_string(i+1), colors[WHITE]);
	}
}
void displayGreentokens()
{
	for(int i=0;i<totaltokens;i++)
	{
		DrawRoundRect(tokenX[0][i],tokenY[0][i],35,35,colors[GREEN],5);
		DrawString( tokenX[0][i]+11, tokenY[0][i]+11, to_string(i+1), colors[WHITE]);
	}
}


void board_display() //Funtion to display Board
{
	DrawSquare( 180 , 80 ,280,colors[RED]); 
	DrawSquare( 620 , 80 ,280,colors[GREEN]);
	DrawSquare( 620 , 520 ,280,colors[ORANGE]);
	DrawSquare( 180 , 520 ,280,colors[DEEP_SKY_BLUE]);

	//safepoints draw
	DrawRectangle(273.5,360,48,58,colors[GRAY]);
	DrawRectangle(758,465,48,58,colors[GRAY]);
	DrawRectangle(461,658,58,48,colors[GRAY]);
	DrawRectangle(567.5,171,54,48,colors[GRAY]);

	//small blocks between blue and red
	DrawRectangle(226.5,413.3,235,55,colors[DEEP_SKY_BLUE]);
	DrawRectangle(226.5,463.2,48,58,colors[DEEP_SKY_BLUE]);
	
	
	//SMALL BLOCKS BETWEEN BLUE AND YELLOW
	DrawRectangle(513.3,520,54.2,230,colors[ORANGE]);
	DrawRectangle(566.6,703.2,55,46.2,colors[ORANGE]);
	
	//SMALL BLOCKS BETWEEN YELLOW AND GREEN
	DrawRectangle(620,413.1,233,54,colors[GREEN]);
	DrawRectangle(806.3,360,48,54,colors[GREEN]);
	
	//SMALL BLOCKS BETWEEN RED AND GREEN
	DrawRectangle(513.3,126,53.6,235,colors[RED]);
	DrawRectangle(460,126.6,53.6,47.6,colors[RED]);
	

		//BLOCK INSIDE RED BLOCK 
	DrawLine( 180 , 220 ,  320 , 360 ,20 , colors[BLACK] );
	DrawLine( 320 , 360 ,  460 , 220 ,20 , colors[BLACK] );
	DrawLine( 460 , 220 ,  320 , 80 ,20 , colors[BLACK] );
	DrawLine( 320 , 80 ,  180 , 220 ,20 , colors[BLACK] );

		//BLOCK INSIDE GREEN BLOCK
	DrawLine( 620 , 220 ,  760 , 360 ,20 , colors[BLACK] );
	DrawLine( 760 , 360 ,  900 , 220 ,20 , colors[BLACK] );
	DrawLine( 900 , 220 ,  760 , 80 ,20 , colors[BLACK] );
	DrawLine( 760 , 80 ,  620 , 220 ,20 , colors[BLACK] );
	
		//BLOCK INSIDE YELLOW BLOCK
	DrawLine( 620 , 659 ,  760 , 798 ,20 , colors[BLACK] );
	DrawLine( 760 , 798 ,  900 , 659 ,20 , colors[BLACK] );
	DrawLine( 900 , 659 ,  760 , 520 ,20 , colors[BLACK] );
	DrawLine( 760 , 520 ,  620 , 659 ,20 , colors[BLACK] );
	
		//BLOCK INSIDE BLUE BLOCK
	DrawLine( 180 , 659 ,  320 , 798 ,20 , colors[BLACK] );
	DrawLine( 320 , 798 ,  460 , 659 ,20 , colors[BLACK] );
	DrawLine( 460 , 659 ,  320 , 520 ,20 , colors[BLACK] );
	DrawLine( 320 , 520 ,  180 , 659 ,20 , colors[BLACK] );
	
	//DrawLine(int x1, int y1, int x2, int y2, int lwidth, float *color)
		//boundary square
	DrawLine( 180 , 80 ,  180 , 799 ,5 , colors[BLACK] );	
	DrawLine( 180 , 80 ,  900 , 80 ,5 , colors[BLACK] );
	DrawLine( 900 , 78 ,  900 , 799 ,5 , colors[BLACK] );
	DrawLine( 180 , 798 ,  900 , 798 ,5 , colors[BLACK] );
		//center square
	DrawLine( 460 , 360 ,  460 , 520 ,2 , colors[BLACK] );
	DrawLine( 460 , 360 ,  620 , 360 ,2 , colors[BLACK] );
	DrawLine( 620 , 360 ,  620 , 520 ,2 , colors[BLACK] );
	DrawLine( 460 , 520 ,  620 , 520 ,2 , colors[BLACK] );
		//TRIANGLES 
	DrawTriangle( 540, 440 , 620, 520 , 620 , 360, colors[GREEN] );
	DrawTriangle( 540, 440 , 460, 360 , 620 , 360, colors[RED] );
	DrawTriangle( 540, 440 , 460, 360 , 460 , 520, colors[DEEP_SKY_BLUE] );
	DrawTriangle( 540, 440 , 460, 520 , 620 , 520, colors[ORANGE] );
		//CROSS AT CENTER
	DrawLine( 460 , 360 ,  620 , 520 ,2 , colors[BLACK] );
	DrawLine( 460 , 520 ,  620 , 360 ,2 , colors[BLACK] );	
	
	
	
		//small blocks between blue and red (VERTICLE)
	DrawLine( 226.6 , 360 ,  226.6 , 520 ,2 , colors[BLACK] );
	DrawLine( 273.2 , 360 ,  273.2 , 520 ,2 , colors[BLACK] );
	DrawLine( 319.8 , 360 ,  319.8 , 520 ,2 , colors[BLACK] );
	DrawLine( 366.4 , 360 ,  366.4 , 520 ,2 , colors[BLACK] );
	DrawLine( 413 , 360 ,  413 , 520 ,2 , colors[BLACK] );
	            //(HORIZONTAL LINES)
	DrawLine( 180 , 360 ,  460 , 360 ,2 , colors[BLACK] );
	DrawLine( 180 , 413.3 ,  460 , 413.3 ,2 , colors[BLACK] );
	DrawLine( 180 , 466.6 ,  460 , 466.6 ,2 , colors[BLACK] );
	DrawLine( 180 , 520 ,  460 , 520 ,2 , colors[BLACK] );
	
	
		//small blocks between blue and yellow (VERTICLE)
	DrawLine( 460 , 520 ,  460 , 798 ,2 , colors[BLACK] );
	DrawLine( 513.3 , 520 ,  513.3 , 798 ,2 , colors[BLACK] );
	DrawLine( 566.6 , 520 ,  566.6 , 798 ,2 , colors[BLACK] );
	DrawLine( 620 , 520 ,  620 , 798 ,2 , colors[BLACK] );
		//HORIZONTAL LINES
	DrawLine( 460 , 565.8 ,  620 , 565.8 ,2 , colors[BLACK] );
	DrawLine( 460 , 611.6 ,  620 , 611.6 ,2 , colors[BLACK] );
	DrawLine( 460 , 657.4 ,  620 , 657.4 ,2 , colors[BLACK] );
	DrawLine( 460 , 703.2 ,  620 , 703.2 ,2 , colors[BLACK] );
	DrawLine( 460 , 749 ,  620 , 749 ,2 , colors[BLACK] );
	
	
	//SMALL BLOCKS BETWEEN RED AND GREEN (VERTICLE)
	DrawLine( 460 , 360 ,  460 , 80 ,2 , colors[BLACK] );
	DrawLine( 513.3 , 360 ,  513.3 , 80 ,2 , colors[BLACK] );
	DrawLine( 566.6 , 360 ,  566.6 , 80 ,2 , colors[BLACK] );
	DrawLine( 620 , 360 ,  620 , 80 ,2 , colors[BLACK] );
		//HORIZONTAL LINES
	DrawLine( 460 , 313 ,  620 , 313 ,2 , colors[BLACK] );
	DrawLine( 460 , 266.4 ,  620 , 266.4 ,2 , colors[BLACK] );
	DrawLine( 460 , 219.8 ,  620 , 219.8 ,2 , colors[BLACK] );
	DrawLine( 460 , 173.2 ,  620 , 173.2 ,2 , colors[BLACK] );
	DrawLine( 460 , 126.8 ,  620 , 126.6 ,2 , colors[BLACK] );
	
	
		//SMALL BLOCKS BETWEEN YELLOW AND GREEN (HORIZONTAL LINES)
	DrawLine( 620 , 360 ,  900 , 360 ,2 , colors[BLACK] );
	DrawLine( 620 , 413.3 ,  900 , 413.3 ,2 , colors[BLACK] );
	DrawLine( 620 , 466.6 ,  900 , 466.6 ,2 , colors[BLACK] );
	DrawLine( 620 , 520 ,  900 , 520 ,2 , colors[BLACK] );
		   // VERTICLE LINES
	DrawLine( 666.6 , 360 ,  666.6 , 520 ,2 , colors[BLACK] );
	DrawLine( 713.2 , 360 ,  713.2 , 520 ,2 , colors[BLACK] );
	DrawLine( 759.8 , 360 ,  759.8 , 520 ,2 , colors[BLACK] );
	DrawLine( 806.4 , 360 ,  806.4 , 520 ,2 , colors[BLACK] );
	DrawLine( 853 , 360 ,  853 , 520 ,2 , colors[BLACK] );
	
		//CIRCLE IN YELLOW BLOCK
	DrawCircle(760,659,97,colors[WHITE]);
	DrawCircle(760,659,92,colors[ORANGE]);
		//CIRCLE IN BLUE BLOCK
	DrawCircle(320,659,97,colors[WHITE]);
	DrawCircle(320,659,92,colors[DEEP_SKY_BLUE]);
		//CIRCLE IN RED BLOCK
	DrawCircle(320,220,97,colors[WHITE]);
	DrawCircle(320,220,92,colors[RED]);
		//CIRCLE IN YELLOW BLOCK
	DrawCircle(760,220,97,colors[WHITE]);
	DrawCircle(760,220,92,colors[GREEN]);

		//place for token in red
	DrawCircle(320,275,30,colors[WHITE]);
	DrawCircle(320,168,30,colors[WHITE]);
	DrawCircle(376,218,30,colors[WHITE]);
	DrawCircle(265,218,30,colors[WHITE]);
		//place for token in blue
	DrawCircle(320,715,30,colors[WHITE]);
	DrawCircle(320,606,30,colors[WHITE]);
	DrawCircle(376,658,30,colors[WHITE]);
	DrawCircle(265,658,30,colors[WHITE]);
		//place for token in green
	DrawCircle(760,275,30,colors[WHITE]);
	DrawCircle(760,168,30,colors[WHITE]);
	DrawCircle(816,218,30,colors[WHITE]);
	DrawCircle(705,218,30,colors[WHITE]);
		//place for token in yellow
	DrawCircle(760,715,30,colors[WHITE]);
	DrawCircle(760,606,30,colors[WHITE]);
	DrawCircle(816,658,30,colors[WHITE]);
	DrawCircle(705,658,30,colors[WHITE]);


	
	
}

void DrawRectangle(int sx, int sy, int width, int height, float *color);
void GameDisplay(){
	  

	glClearColor(1/*Red Component*/, 1,	//148.0/255/*Green Component*/,
			1/*Blue Component*/, 1 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClear (GL_COLOR_BUFFER_BIT); //Update the colors
	
	if (window==1)		//Input Screen
	{
		DrawString(150,520,"Enter Number of Tokens : ",colors[BLUE]);
	}
	else if (window==2)		//Game screen
	{
		board_display();
		Dice(diceroll);
		displayGreentokens();
		displayRedTokens();
		displayBlueTokens();
		displayYellowTokens();
		displayTurn();
		if(counter1>=2)
		{
			window=3;
			stopmaster=true;
		}
	}
	else if (window==3)			//Winning Screen
	{
		DrawString(150,520,"Winning Players : ",colors[BLACK]);
		DrawString(150, 480,"1 . Player "+to_string(Winningplayer[0]),colors[BLACK]);
		DrawString(150, 460,"2 . Player "+to_string(Winningplayer[1]),colors[BLACK]);
		DrawString(150, 440,"3 . Player "+to_string(Winningplayer[2]),colors[BLACK]);
	}
	
	
	

	glutSwapBuffers(); // do not modify this line..
	
}

void NonPrintableKeys(int key, int x, int y) {
	if (key
			== GLUT_KEY_LEFT /*GLUT_KEY_LEFT is constant and contains ASCII for left arrow key*/) {
		// what to do when left key is pressed...

	} else if (key
			== GLUT_KEY_RIGHT /*GLUT_KEY_RIGHT is constant and contains ASCII for right arrow key*/) {

	} else if (key
			== GLUT_KEY_UP/*GLUT_KEY_UP is constant and contains ASCII for up arrow key*/) {

	}

	else if (key
			== GLUT_KEY_DOWN/*GLUT_KEY_DOWN is constant and contains ASCII for down arrow key*/) {

	}

	/* This function calls the Display function to redo the drawing. Whenever you need to redraw just call
	 * this function*/

}
void PrintableKeys(unsigned char key, int x, int y) {
	if (key == 27) {
		exit(1);
	}
	if (window==1)
	{
		if(key==49)
		{
			totaltokens=1;
			window=2;
		}
	 	else if (key==50)
		{
			totaltokens=2;
			window=2;
		}
		else if (key==51)
		{
	        totaltokens=3;	
			window=2;	
		}
		else if (key==52)
		{
			totaltokens=4;
			window=2;
		}
	}
}
void Timer(int m) {
	glutTimerFunc(16.6, Timer, 0);
	glutPostRedisplay();
}
void MousePressedAndMoved(int x, int y) {
	y=840-y;
	cout << x << " " << y << endl;
}
void MouseMoved(int x, int y)
{}
void MouseClicked(int button, int state, int x, int y) {

	if (button == GLUT_LEFT_BUTTON)
			{
		
				y = 840-y;
				cout << x << ' ' << y << endl;

	} else if (button == GLUT_RIGHT_BUTTON)
			{

	}
}


int main(int argc, char*argv[])
{

	sem_init(&SemDice,0,1);
	sem_init(&SemBoard,0,1);

	pthread_create(&mainId, NULL, Mainthreadfunction, NULL);		//Master Thread
	
	sem_destroy(&SemDice);
	sem_destroy(&SemBoard);
	

	int width = 1020, height = 840; 
	InitRandomizer(); 
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); 
	glutInitWindowPosition(50, 50); 
	glutInitWindowSize(width, height); 
	glutCreateWindow("OS Project"); 
	SetCanvasSize(width, height); 

	glutDisplayFunc(GameDisplay);
	

	glutSpecialFunc(NonPrintableKeys);
	glutKeyboardFunc(PrintableKeys); 
	glutTimerFunc(16.6, Timer, 0);

	glutMouseFunc(MouseClicked);
	glutPassiveMotionFunc(MouseMoved); 
	glutMotionFunc(MousePressedAndMoved); 
	

	glutMainLoop();
	return 1;
}
#endif /* AsteroidS_CPP_ */
