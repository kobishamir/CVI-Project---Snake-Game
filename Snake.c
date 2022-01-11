#include "bass.h"
#include "toolbox.h"
#include <ansi_c.h>
#include <utility.h>
#include <cvirte.h>		
#include <userint.h>
#include "Snake.h"
#include <stdio.h>


static int panelHandle;

struct location
{
	int x;
	int y;
};
struct location arr [100];

		
BOOL game_over = 0;

int dir  = 2;
int tabhandle0, tabhandle1, clk = 0,H,W,apple,arr_size = 1;
int dx=20,dy=20,rndx,rndy,blocksize=20;
int score1 = 0;
int counter;

char linebuffer[300];

double diff = 0.25;

FILE* fp;

void moveSnake();
void DrawApple(int rndx,int rndy);
void DrawSnake();
void generate_random_coardinate();

int CVICALLBACK Thread1 (void *functionData),lock1;

////for sound:

HSTREAM Apple_bite;
HSTREAM headshot;
HSTREAM game_music;

////
/////////// Main Function
int main (int argc, char *argv[])
{
	srand(time(0));
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((panelHandle = LoadPanel (0, "Snake.uir", PANEL)) < 0)
		return -1;
	// TODO: Get the panel handle associated with a tab page with GetPanelHandleFromTabPage
	GetPanelHandleFromTabPage (panelHandle, PANEL_TAB, 0, &tabhandle0);
	GetPanelHandleFromTabPage (panelHandle, PANEL_TAB, 1, &tabhandle1);
	
	//// adding sound:
	
	BASS_Init( -1,44100, 0,0,NULL);
	Apple_bite = BASS_StreamCreateFile(FALSE,"bite.mp3",0,0,0);
	headshot = BASS_StreamCreateFile(FALSE,"headshot.mp3",0,0,0);
	game_music = BASS_StreamCreateFile(FALSE,"game_music.mp3",0,0,0);
	////
	
	DisplayPanel (panelHandle);
	CmtNewLock (NULL, 0, &lock1);
	RunUserInterface ();
	CmtDiscardLock (lock1);
	DiscardPanel (panelHandle);
	return 0;
}



int CVICALLBACK QuitCallback (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			QuitUserInterface (0);

			break;
	}
	return 0;
}


int CVICALLBACK StartCallback (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{
		
	switch (event)
	{
		case EVENT_COMMIT:
				
			GetCtrlAttribute (tabhandle0, GAMEPANEL_CANVAS, ATTR_HEIGHT, &H);
			GetCtrlAttribute (tabhandle0, GAMEPANEL_CANVAS, ATTR_WIDTH, &W);
			game_over = 0;
			arr_size = 1;
			score1 = 0;
			SetCtrlVal (tabhandle0, GAMEPANEL_NUMERIC, score1);
			BASS_ChannelSetAttribute(game_music, BASS_ATTRIB_VOL, 0.3);
			BASS_ChannelPlay(game_music,TRUE);
			if (diff == 0.25000000)
			SetCtrlAttribute (tabhandle0, GAMEPANEL_TIMER, ATTR_INTERVAL, diff);
			
			else if (diff == 0.12500000)
			SetCtrlAttribute (tabhandle0, GAMEPANEL_TIMER, ATTR_INTERVAL, diff);
			
			SetCtrlAttribute (tabhandle0, GAMEPANEL_TIMER, ATTR_ENABLED, TRUE);
			score1 = 0;
			arr[0].x = W/2;
			arr[0].y = H/2;
			generate_random_coardinate();
	
			break;
	}
	return 0;
}


///////////// controlling the snake with arrows
int CVICALLBACK Snakefunc (int panel, int control, int event,
						   void *callbackData, int eventData1, int eventData2)
/*
	1- left
	2- right
	3- up
	4-down
	*/
{
	switch (event)
	{
		case EVENT_KEYPRESS:
		{
		
			switch(eventData1)
			{
				case VAL_UP_ARROW_VKEY:
				{	
					dir = 3;
					break;
				}
				
				case VAL_DOWN_ARROW_VKEY:
				{	
					dir = 4;
					break;
				}
				
				case VAL_LEFT_ARROW_VKEY:
				{	
					dir = 1;
					break;
				}
				
				case VAL_RIGHT_ARROW_VKEY:
				{	
					dir = 2;
					break;
				}
			}
		}
	}	
	return 0;
}


struct location newHeadLocation(dir)
{
	struct location new_head = arr[0];
	
	 switch (dir)
	 {
	 case 2://right
		 new_head.x += dx;
		 break;
	 
	 case 3://up
		 new_head.y -= dy;
		 break;
	 
	 case 4://down
		 new_head.y += dy;
		 break;
	 
	 case 1://left
		 new_head.x -= dx;
		 break;
		 
	 default:
	 	break;
	 }
	 
	 return new_head;
}

// function to make runcdom coardinates for DrawApple
void generate_random_coardinate()

{
		rndx = rand()%(W-blocksize);
		rndy = rand()%(H-blocksize);
		rndx -= rndx%blocksize;
		rndy -= rndy%blocksize;	
}
	

int CVICALLBACK timer (int panel, int control, int event,
					   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_TIMER_TICK:
			{
			CmtScheduleThreadPoolFunction (DEFAULT_THREAD_POOL_HANDLE, Thread1, NULL, NULL);
			break;	
			}
	}
	return 0;	
}


void DrawApple (int rndy, int rndx)
{
	SetCtrlAttribute (tabhandle0, GAMEPANEL_CANVAS, ATTR_DRAW_POLICY, VAL_MARK_FOR_UPDATE);
	SetCtrlAttribute (tabhandle0, GAMEPANEL_CANVAS, ATTR_PEN_COLOR, VAL_DK_RED);
	SetCtrlAttribute (tabhandle0, GAMEPANEL_CANVAS, ATTR_PEN_FILL_COLOR, VAL_DK_RED);
	CanvasDrawRect(tabhandle0, GAMEPANEL_CANVAS, MakeRect(rndy,rndx,blocksize ,blocksize), VAL_DRAW_FRAME_AND_INTERIOR);
	CanvasUpdate(tabhandle0,GAMEPANEL_CANVAS,VAL_ENTIRE_OBJECT);
}


void DrawSnake ()
{
	for (int i=0; i <arr_size; i++)
	{
		SetCtrlAttribute (tabhandle0, GAMEPANEL_CANVAS, ATTR_DRAW_POLICY, VAL_MARK_FOR_UPDATE);
		SetCtrlAttribute (tabhandle0, GAMEPANEL_CANVAS, ATTR_PEN_COLOR, VAL_BLACK);
		SetCtrlAttribute (tabhandle0, GAMEPANEL_CANVAS, ATTR_PEN_FILL_COLOR, VAL_BLACK);	
		CanvasDrawRect(tabhandle0, GAMEPANEL_CANVAS, MakeRect(arr[i].y,arr[i].x ,blocksize ,blocksize), VAL_DRAW_FRAME_AND_INTERIOR);
		CanvasUpdate(tabhandle0,GAMEPANEL_CANVAS,VAL_ENTIRE_OBJECT);
	}
}

void moveSnake() 
{ // Add the begining of our Arr the new place of the head and move all the other Array members one place right.
	// return the amount of relevant Array members
    for(int i=arr_size;i>0;i--)
    {
        arr[i]=arr[i-1];
    }
}

int CVICALLBACK Thread1 (void *functionData)
{
 		
			// when snake hit a wall
			if (arr[0].x+blocksize > W || arr[0].x < 0 || arr[0].y+blocksize > H || arr[0].y < 0) 
			{
			 	BASS_ChannelStop(game_music);
				SetCtrlAttribute (tabhandle0, GAMEPANEL_TIMER, ATTR_ENABLED, FALSE);
				SetCtrlVal (tabhandle1, STATPANEL_NUMERIC_2, score1);
				BASS_ChannelPlay(headshot,TRUE);
				fp = fopen ("Scores.txt", "a");
				fprintf(fp,"%d \n",score1);
				game_over = 1;
			}	
				
			if  (game_over != 1)
			{
				CanvasClear(tabhandle0, GAMEPANEL_CANVAS, VAL_ENTIRE_OBJECT);
				
				// when snake eats apple
				if (arr[0].x > rndx-blocksize && arr[0].x < rndx+blocksize && arr[0].y > rndy-blocksize && arr[0].y < rndy+blocksize) // when sanek eat apple
				{
					generate_random_coardinate();
					BASS_ChannelPlay(Apple_bite,TRUE);
					arr_size++;
					score1++;
					SetCtrlVal (tabhandle0, GAMEPANEL_NUMERIC, score1);
				}
				// get snake directions now by move_snake function:
				moveSnake();
					
				arr[0]=newHeadLocation(dir);
				DrawSnake();
				DrawApple(rndy,rndx);
			}
				
				else 
				{
					CanvasClear(tabhandle0, GAMEPANEL_CANVAS, VAL_ENTIRE_OBJECT);
				}
 return 0;
}

//Binary Switch difficulty, easy is diffult
int CVICALLBACK difficulty (int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			
			GetCtrlAttribute (tabhandle0, GAMEPANEL_BINARYSWITCH, ATTR_ON_VALUE,&diff );
			GetCtrlAttribute (tabhandle0, GAMEPANEL_BINARYSWITCH, ATTR_OFF_VALUE, &diff);
			break;
	}
	return 0;
}


int CVICALLBACK score (int panel, int control, int event,
					   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:

			break;
	}
	return 0;
}


// second panel loading scores form txt file

int CVICALLBACK loadscores (int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
	
	switch (event)
	{
		case EVENT_COMMIT:
			
			fp = fopen ("Scores.txt", "r");
			
			while (fgets(linebuffer,100,fp)!=NULL)
			{
				SetCtrlVal (tabhandle1, STATPANEL_TEXTBOX,linebuffer);
				SetCtrlVal (tabhandle1, STATPANEL_TEXTBOX,"\n");
			}
			fclose(fp);
			
			SetCtrlVal (tabhandle1, STATPANEL_NUMERIC_2, score1);
			break;
	}
	return 0;
}
