#include <utility.h>
#include <cvirte.h>		
#include <userint.h>
#include "Snake.h"

static int panelHandle;
int tabhandle0, tabhandle1;
//double easy =  

int main (int argc, char *argv[])
{
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
	
	static int c = 0;
	double selection;
	switch (event)
	{
		case EVENT_COMMIT:
			//CanvasDrawRect (tabhandle0, GAMEPANEL_CANVAS, MakeRect(187,187,25,25), VAL_DRAW_FRAME);
			//Delay (0.5);
			c=!c;
			if (c);{
				GetCtrlVal (tabhandle0, GAMEPANEL_BINARYSWITCH, &selection);
				SetCtrlAttribute (tabhandle0, GAMEPANEL_TIMER, ATTR_INTERVAL, selection);
				SetCtrlAttribute (tabhandle0, GAMEPANEL_TIMER, ATTR_ENABLED, c);
			}
				
			
			//CanvasClear (tabhandle0, GAMEPANEL_CANVAS, VAL_ENTIRE_OBJECT);
			
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
int CVICALLBACK timer (int panel, int control, int event,
					   void *callbackData, int eventData1, int eventData2)
{
	static int x = 187;
	static int y = 187;
	//int character;
	switch (event)
	{
		case EVENT_TIMER_TICK:
			CanvasDrawRect (tabhandle0, GAMEPANEL_CANVAS, MakeRect(y,x,25,25), VAL_DRAW_FRAME);
			x = x + 25;
			CanvasClear (tabhandle0, GAMEPANEL_CANVAS, VAL_ENTIRE_OBJECT);
			CanvasDrawRect (tabhandle0, GAMEPANEL_CANVAS, MakeRect(y,x,25,25), VAL_DRAW_FRAME);
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



