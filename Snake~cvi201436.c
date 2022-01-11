#include "toolbox.h"
#include <utility.h>
#include <cvirte.h>		
#include <userint.h>
#include "Snake.h"
#include <stdio.h>


static int panelHandle;
/*
typedef enum Direction;
// changes made by ran start
typedef enum {
	up, down, left, right, none
}Direction;
// we will set default value (in begining as none. left it will be changed
Direction dir = right;
// changes made by ran end
*/

struct location
{
	int x;
	int y;
};

struct location arr[100];

		
BOOL game_over = 0;
int dir  = 2;
int tabhandle0, tabhandle1, clk = 0,H,W,apple,arr_size = 1;
int dx=20,dy=20,rndx,rndy,blocksize=20; // size of movment for the snake: arr[0].x is for X, and arr[0].y is for the Y, dx for movment step
//double selection;

void DrawApple(int rndx,int rndy);
void DrawSnake(int x, int y); //makeing squre in the middle
void generate_random_coardinate();
//double move_snake(double dir);
CmtThreadLockHandle lockhandle, threadhandle3; // locking movement i think
CmtThreadFunctionID val3;

int CVICALLBACK snakethread (void *callbackData);


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
	DisplayPanel (panelHandle);
	RunUserInterface ();
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

int CVICALLBACK OkCallback (int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:

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
			SetCtrlAttribute (tabhandle0, GAMEPANEL_TIMER, ATTR_ENABLED, TRUE);
			arr[0].x = W/2;
			arr[0].y = H/2;
			generate_random_coardinate();
			
			
			//CmtNewLock(NULL,OPT_TL_SUPPORT_TIMEOUT, &lockhandle);
			break;
	}
	return 0;
}

/*
VAL_UP_ARROW_VKEY = 0x0600
VAL_DOWN_ARROW_VKEY = 0x0700
VAL_LEFT_ARROW_VKEY = 0x0800
VAL_RIGHT_ARROW_VKEY = 0x0900
*/

//next function must be uncomment to make it work
///////////// controlling the snake with arrows
int CVICALLBACK Snakefunc (int panel, int control, int event,
						   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_KEYPRESS:
		{
		
			switch(eventData1)
			{
				case VAL_UP_ARROW_VKEY:
				{	
				//CmtScheduleThreadPoolFunction (threadhandle, threadfunction3, NULL, &val1); // coppied from RAN
					dir = 3; // changes made by ran
					//SetCtrlAttribute (tabhandle0, GAMEPANEL_CANVAS, ATTR_CTRL_VAL, dir);
					break; // changes made by ran
				}
				
				case VAL_DOWN_ARROW_VKEY:
				{	
					//	CmtScheduleThreadPoolFunction (threadhandle, threadfunction4, NULL, &val1);// coppied from RAN
					dir = 4;// changes made by ran
					//SetCtrlAttribute (tabhandle0, GAMEPANEL_CANVAS, ATTR_CTRL_VAL, dir);
					break; // changes made by ran
				}
				
				case VAL_LEFT_ARROW_VKEY:
				{	
					dir = 1;// changes made by ran
					//SetCtrlAttribute (tabhandle0, GAMEPANEL_CANVAS, ATTR_CTRL_VAL, dir);
					break; // changes made by ran
				}
				
				case VAL_RIGHT_ARROW_VKEY:
				{	
					dir = 2; // changes made by ran
					//SetCtrlAttribute (tabhandle0, GAMEPANEL_CANVAS, ATTR_CTRL_VAL, dir);
					break; // changes made by ran
				}
			}
		}
	}	
	return 0;
}


 void move_snake(dir)

{
	 switch (dir)
	 {
	 case 2://right
		 arr[0].x += dx;
		 break;
	 
	 case 3://up
		 arr[0].y -= dy;
		 break;
	 
	 case 4://down
		 arr[0].y += dy;
		 break;
	 
	 case 1://left
		 arr[0].x -= dx;
		 break;
		 
	 default:
	 	break;
	 }
		 
}
	
	  
	  /*
	 // arr[0].y += dy;
	 
	  if (arr[0].x <= 0)
	  {
		 // score[1]+=1; //right
		//  sprintf(str2, "%d", score[1]);   
		  arr[0].x = W/2;
		  arr[0].y = H/2;
		  dy = 10*selection;
		  clearcanvas(); 
		  DrawSnake(arr[0].x+20, arr[0].y);
	  }
	  if (arr[0].x >= W)
	  {
		  //score[0]+=1; //left
		//  sprintf(str1, "%d", score[0]);
		  arr[0].x = W/2;
		  arr[0].y = H/2;
		  clearcanvas();
		  dy = 10*selection;
		  DrawSnake(arr[0].x, arr[0].y);
	  }
	   if (arr[0].y <=5 || arr[0].y >= H-5)
	   {
		  dy=-dy;
	   }
	  */


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
	//int character;
	//static int z=0;
	//GetCtrlAttribute(tabhandle0, GAMEPANEL_TIMER, ATTR_CTRL_VAL, &dir);
	//static double dir; 
	/*
	1- left
	2- right
	3- up
	4-down
	*/
	
	switch (event)
	{
		case EVENT_TIMER_TICK:
		{
			clk=!clk;
	
     	//CanvasDrawRect (tabhandle0, GAMEPANEL_CANVAS, MakeRect(y,x,15,15), VAL_DRAW_FRAME);
		//	x = x + 15;
		//	CanvasClear (tabhandle0, GAMEPANEL_CANVAS, VAL_ENTIRE_OBJECT);
		//	CanvasDrawRect (tabhandle0, GAMEPANEL_CANVAS, MakeRect(y,x,15,15), VAL_DRAW_FRAME);
		//CmtScheduleThreadPoolFunction (threadhandle3, snakethread, NULL, &val3);
		//clk=0;
		//SetCtrlAttribute (tabhandle0, GAMEPANEL_TIMER, ATTR_ENABLED, clk);
		//CanvasDrawRect(tabhandle0, GAMEPANEL_CANVAS, MakeRect(arr[0].y,arr[0].x ,15 ,15 ), VAL_DRAW_FRAME_AND_INTERIOR);
	
			// get snake directions now by move_snake function:
			move_snake(dir);
			CanvasClear (tabhandle0, GAMEPANEL_CANVAS, VAL_ENTIRE_OBJECT);
			for (int i=0; i <arr_size; i++)
			{
			DrawSnake(arr[0].x,arr[0].y);
			}
			//CanvasDrawRect(tabhandle0, GAMEPANEL_CANVAS, MakeRect(arr[0].y,arr[0].x ,blocksize ,blocksize ), VAL_DRAW_FRAME_AND_INTERIOR);
			
			if (arr[0].x+blocksize > W || arr[0].x < 0 || arr[0].y+blocksize > H || arr[0].y < 0) // when snake hit a wall
		 		game_over = 1;
			
			//printf("sx = %d  sy = %d  rx = %d  ry = %d \n ",arr[0].x,arr[0].y,rndx,rndy);
			if (arr[0].x > rndx-blocksize && arr[0].x < rndx+blocksize && arr[0].y > rndy-blocksize && arr[0].y < rndy+blocksize) // when sanek eat apple
			{
				generate_random_coardinate();
			//	arr[arr_size] = 
			
			//printf("sx = %d  sy = %d  rx = %d  ry = %d \n ",arr[0].x,arr[0].y,rndx,rndy);
			}
				
			DrawApple(rndy,rndx);
			//CanvasDrawRect(tabhandle0, GAMEPANEL_CANVAS, MakeRect(rndy,rndx ,blocksize ,blocksize ), VAL_DRAW_FRAME_AND_INTERIOR);
			clk=0;
		}
			break;			

	}

	return 0;	
}

//// no need to write anything to that function now:
int CVICALLBACK difficulty (int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:

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

//////////////////////////////////////////////////////////////////////////////////

/*
void clearcanvas() {
	
	/// Draw canvas:
	SetCtrlAttribute (tabhandle0, GAMEPANEL_CANVAS, ATTR_DRAW_POLICY, VAL_MARK_FOR_UPDATE);
	SetCtrlAttribute (tabhandle0, GAMEPANEL_CANVAS, ATTR_PEN_COLOR, 0x00B0FFF);
	SetCtrlAttribute (tabhandle0, GAMEPANEL_CANVAS, ATTR_PEN_FILL_COLOR, 0x00B0FFF);
	CanvasClear (tabhandle0, GAMEPANEL_CANVAS, VAL_ENTIRE_OBJECT);
	
	/// Draw black line in left side:
	SetCtrlAttribute (tabhandle0, GAMEPANEL_CANVAS, ATTR_DRAW_POLICY, VAL_MARK_FOR_UPDATE);
	SetCtrlAttribute (tabhandle0, GAMEPANEL_CANVAS, ATTR_PEN_COLOR, VAL_BLACK);
	SetCtrlAttribute (tabhandle0, GAMEPANEL_CANVAS, ATTR_PEN_FILL_COLOR, VAL_BLACK);
	CanvasDrawRect(tabhandle0, GAMEPANEL_CANVAS, MakeRect(0,0, H,2), VAL_DRAW_INTERIOR);
	
	/// Draw black line in top side:
	SetCtrlAttribute (tabhandle0, GAMEPANEL_CANVAS, ATTR_DRAW_POLICY, VAL_MARK_FOR_UPDATE);
	SetCtrlAttribute (tabhandle0, GAMEPANEL_CANVAS, ATTR_PEN_COLOR, VAL_BLACK);
	SetCtrlAttribute (tabhandle0, GAMEPANEL_CANVAS, ATTR_PEN_FILL_COLOR, VAL_BLACK);
	CanvasDrawRect(tabhandle0, GAMEPANEL_CANVAS, MakeRect(0,0, 2,W), VAL_DRAW_INTERIOR);
	
	/// Draw black line in right side:
	SetCtrlAttribute (tabhandle0, GAMEPANEL_CANVAS, ATTR_DRAW_POLICY, VAL_MARK_FOR_UPDATE);
	SetCtrlAttribute (tabhandle0, GAMEPANEL_CANVAS, ATTR_PEN_COLOR, VAL_BLACK);
	SetCtrlAttribute (tabhandle0, GAMEPANEL_CANVAS, ATTR_PEN_FILL_COLOR, VAL_BLACK);
	CanvasDrawRect(tabhandle0, GAMEPANEL_CANVAS, MakeRect(0,W-2, H,2), VAL_DRAW_INTERIOR);
	
	/// Draw black line in bottom side:
	SetCtrlAttribute (tabhandle0, GAMEPANEL_CANVAS, ATTR_DRAW_POLICY, VAL_MARK_FOR_UPDATE);
	SetCtrlAttribute (tabhandle0, GAMEPANEL_CANVAS, ATTR_PEN_COLOR, VAL_BLACK);
	SetCtrlAttribute (tabhandle0, GAMEPANEL_CANVAS, ATTR_PEN_FILL_COLOR, VAL_BLACK);
	CanvasDrawRect(tabhandle0, GAMEPANEL_CANVAS, MakeRect(H-2,0, 2,W), VAL_DRAW_INTERIOR);
	
	
	CanvasUpdate (tabhandle0, GAMEPANEL_CANVAS, VAL_ENTIRE_OBJECT);
}
*/


// func to make apple: equivalent to Ran's DrawWhiteRect:
/*
void DrawApple(Rect rect){
	
SetCtrlAttribute (tabhandle0, GAMEPANEL_CANVAS, ATTR_DRAW_POLICY, VAL_MARK_FOR_UPDATE);
SetCtrlAttribute (tabhandle0, GAMEPANEL_CANVAS, ATTR_PEN_COLOR, VAL_BLACK);	
SetCtrlAttribute (tabhandle0, GAMEPANEL_CANVAS, ATTR_PEN_FILL_COLOR, VAL_BLACK);
CanvasDrawRect(tabhandle0, GAMEPANEL_CANVAS, rect, VAL_DRAW_FRAME_AND_INTERIOR);
}*/


void DrawApple (int rndy, int rndx)
{
	
	SetCtrlAttribute (tabhandle0, GAMEPANEL_CANVAS, ATTR_DRAW_POLICY, VAL_MARK_FOR_UPDATE);
	SetCtrlAttribute (tabhandle0, GAMEPANEL_CANVAS, ATTR_PEN_COLOR, VAL_DK_RED);
	SetCtrlAttribute (tabhandle0, GAMEPANEL_CANVAS, ATTR_PEN_FILL_COLOR, VAL_DK_RED);
	CanvasDrawRect(tabhandle0, GAMEPANEL_CANVAS, MakeRect(rndy,rndx,blocksize ,blocksize), VAL_DRAW_FRAME_AND_INTERIOR);
	CanvasUpdate(tabhandle0,GAMEPANEL_CANVAS,VAL_ENTIRE_OBJECT);
}

// func to make a squre represent the snake: equivalent to Ran's DrawRightUser:
void DrawSnake (int X, int Y)
{
	SetCtrlAttribute (tabhandle0, GAMEPANEL_CANVAS, ATTR_DRAW_POLICY, VAL_MARK_FOR_UPDATE);
	SetCtrlAttribute (tabhandle0, GAMEPANEL_CANVAS, ATTR_PEN_COLOR, VAL_BLACK);
	SetCtrlAttribute (tabhandle0, GAMEPANEL_CANVAS, ATTR_PEN_FILL_COLOR, VAL_BLACK);	
	CanvasDrawRect(tabhandle0, GAMEPANEL_CANVAS, MakeRect(Y,X ,blocksize ,blocksize), VAL_DRAW_FRAME_AND_INTERIOR);
	CanvasUpdate(tabhandle0,GAMEPANEL_CANVAS,VAL_ENTIRE_OBJECT);
}

// func to make the snake move to direction controlled by arrows, starting moving right: equivalent to Ran's move_ball:


/*
int CVICALLBACK snakethread (void *callbackData) {
	
	CmtGetLock(lockhandle);
	move_snake();
	CmtReleaseLock(lockhandle);
	return 0;
}
*/


