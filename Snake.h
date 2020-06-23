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
#define  PANEL_OKBUTTON                   4       /* control type: command, callback function: OkCallback */

     /* tab page panel controls */
#define  GAMEPANEL_CANVAS                 2       /* control type: canvas, callback function: (none) */
#define  GAMEPANEL_StartBUTTON            3       /* control type: command, callback function: StartCallback */
#define  GAMEPANEL_NUMERIC                4       /* control type: numeric, callback function: score */
#define  GAMEPANEL_BINARYSWITCH           5       /* control type: binary, callback function: difficulty */
#define  GAMEPANEL_TIMER                  6       /* control type: timer, callback function: timer */

     /* tab page panel controls */
#define  STATPANEL_GRAPH                  2       /* control type: graph, callback function: (none) */
#define  STATPANEL_NUMERIC_2              3       /* control type: numeric, callback function: (none) */
#define  STATPANEL_NUMERIC                4       /* control type: numeric, callback function: (none) */
#define  STATPANEL_COMMANDBUTTON          5       /* control type: command, callback function: (none) */
#define  STATPANEL_COMMANDBUTTON_2        6       /* control type: command, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK difficulty(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OkCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK QuitCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK score(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK StartCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK timer(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif