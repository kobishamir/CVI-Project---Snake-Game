/**************************************************************************/
/* LabWindows/CVI User Interface Resource (UIR) Include File              */
/*                                                                        */
/* WARNING: Do not add to, delete from, or otherwise modify the contents  */
/*          of this include file.                                         */
/**************************************************************************/

#include <userint.h>

#ifdef __cplusplus
    extern "C" {
#endif

     /* Panels and Controls: */

#define  PANEL                            1
#define  PANEL_TAB                        2       /* control type: tab, callback function: (none) */
#define  PANEL_QUITBUTTON                 3       /* control type: command, callback function: QuitCallback */

     /* tab page panel controls */
#define  GAMEPANEL_CANVAS                 2       /* control type: canvas, callback function: Snakefunc */
#define  GAMEPANEL_StartBUTTON            3       /* control type: command, callback function: StartCallback */
#define  GAMEPANEL_NUMERIC                4       /* control type: numeric, callback function: score */
#define  GAMEPANEL_BINARYSWITCH           5       /* control type: binary, callback function: difficulty */
#define  GAMEPANEL_TIMER                  6       /* control type: timer, callback function: timer */
#define  GAMEPANEL_SPLITTER_2             7       /* control type: splitter, callback function: (none) */
#define  GAMEPANEL_SPLITTER               8       /* control type: splitter, callback function: (none) */
#define  GAMEPANEL_SPLITTER_4             9       /* control type: splitter, callback function: (none) */
#define  GAMEPANEL_SPLITTER_3             10      /* control type: splitter, callback function: (none) */

     /* tab page panel controls */
#define  STATPANEL_NUMERIC_2              2       /* control type: numeric, callback function: (none) */
#define  STATPANEL_LOAD_SCORE             3       /* control type: command, callback function: loadscores */
#define  STATPANEL_TEXTBOX                4       /* control type: textBox, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK difficulty(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK loadscores(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK QuitCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK score(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Snakefunc(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK StartCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK timer(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif