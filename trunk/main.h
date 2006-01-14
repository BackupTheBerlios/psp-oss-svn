#define OSSVersion "PSP-OSS_0,2c"
#include <ctype.h>
#include <pspumd.h>
#include <pspkernel.h>
#include <pspdebug.h>
#include <pspctrl.h>
#include <stdlib.h>
#include <string.h>
#include <pspdisplay.h>
#include <png.h>
#include <math.h>
#include <stdio.h>
#include <pspumd.h>
#include <psppower.h>
#include <pspwlan.h>
#include <pspiofilemgr.h>
#include <pspiofilemgr_fcntl.h>
#include <pspmodulemgr.h>
#include <pspusb.h>
#include <pspusbstor.h>
#include <pspthreadman.h>
#include <pspsdk.h>
#include <psprtc.h>
#include <time.h>
#include <pspaudiolib.h>
#include <pspaudio.h>
#include <limits.h>
#include <psploadexec.h>
#include <psptypes.h>
#include <pspkerneltypes.h>

#include "codec/mp3player.h"
#include "codec/oggplayer.h"

#define RGB(r, g, b) ((b << 16) | (g << 8) | r)	// RGB Handler Macro
#define BLACK RGB(0, 0, 0)	// Black
#define WHITE RGB(255, 255, 255)	// White
#define RED RGB(255, 0, 0)	// Red
#define GREEN RGB(0, 255, 0)	// Green
#define BLUE RGB(0, 0, 255)	// Blue
#define YELLOW RGB(255, 255, 0)	// Yellow
#define CYAN RGB(255, 255, 0)	// Cyan
#define MAGENTA RGB(255, 0, 255)	// Magenta
#define ORANGE RGB(255, 97, 3)	// Orange
#define DARK_RED RGB(139, 26, 26)	// Dark Red
#define PINK RGB(255, 105, 180)	// Pink

#include "lib/OSSgraphics.h"

// Defaults Desktop Icon Size
#define IconXSize 60
#define IconYSize 60

Font *defaultFont;

Image *wallpaper;		// System Wallpaper
Image *taskbar;			//
Image *TopBar;
Image *cursor;
Image *Keyboard_Output;
Image *Keyboard_Button1;
Image *Keyboard_Button2;
Image *Keyboard_ButtonOver;
Image *Message_Window_Top1;
Image *Message_Window_Top2;
Image *Message_Window_Body;
Image *Settings_Window;
Image *Settings_Window_Over;
Image *Settings_Window_Bottom;
Image *Fullscreen_Window_Top1;
Image *Fullscreen_Window_Top2;
Image *Fullscreen_Window_Body;
Image *Window_Exit1;
Image *Window_Exit2;
Image *USB_Icon;
Image *No_USB_Icon;
Image *Fade;
Image *WLAN_Icon;
Image *Battery_full;
Image *Battery_half;
Image *Battery_low;
Image *Battery_empty;
Image *Battery_charging;
Image *WLANBackground;
Image *Progressbar;
Image *Progressbar_fill;

// Custom Icons
Image *Icon_Customs[32];
int Icon_Custom_Index[32];

// Icons
Image *Icon_Eboot;
Image *Icon_Eboot_Over;
Image *Icon_Unknown;
Image *Icon_Unknown_Over;
Image *Icon_Settings;
Image *Icon_Settings_Over;
Image *Icon_Themes;
Image *Icon_Themes_Over;
Image *Icon_Wallpapers;
Image *Icon_Wallpapers_Over;
Image *Icon_Quit;
Image *Icon_Quit_Over;
Image *Icon_GFX;
Image *Icon_GFX_Over;
Image *Icon_Audio;
Image *Icon_Audio_Over;
Image *Icon_UMD;
Image *Icon_UMD_Over;
Image *Icon_No_UMD;
Image *Icon_No_UMD_Over;
Image *Icon_QuickLink;
Image *Icon_QuickLink_Over;

// Dialog Button Images
Image *Button1;
Image *Button2;

Image *Music_play1;
Image *Music_play2;
Image *Music_pause1;
Image *Music_pause2;
Image *Music_stop1;
Image *Music_stop2;
Image *Audio_Player;
Image *Menu_Button;
Image *Menu_Button_Over;
Image *Menu_Content;
Image *Menu_Content_Over;
Image *Menu_Top;
Image *Icon_Folder;
Image *Icon_Folder_Over;
Image *Back;
Image *Back_Over;
Image *FBLeft;
Image *FBRight;
Image *PowerButtons;
Image *RightclickMenu_Top;
Image *RightclickMenu_Body;
Image *RightclickMenu_Body_Over;
Image *RightclickMenu_Bottom;

// Start Menu Images
Image *Start_menu;
Image *Start_menu_Over;
Image *Start_menu_Open;
Image *Start_Menu_Body;
Image *Start_Menu_Body_Over;
Image *Start_Menu_Top;
Image *SubMenuTop;
Image *SubMenuTopLeft;
Image *SubMenuTopRight;
Image *SubMenuMiddle;
Image *SubMenuSelect;
Image *SubMenuSideLeft;
Image *SubMenuSideRight;
Image *SubMenuBottom;
Image *SubMenuBottomLeft;
Image *SubMenuBottomRight;

Image *Effect_GFX1;
int Effect_Snow_PositionX;
int Effect_Snow_PositionY;

// Temporary Storage Image
Image *TempImage;

SceCtrlData pad;

struct IconPosition
{
  int row;
  int col;
};

struct CursorPosition
{
  int x;
  int y;
};

struct IconPosition iconSelected;
struct CursorPosition cursorPosition;

int usbState;

//Is the desktop active?
int DesktopActive;
int DesktopIconsActive;

int old_buttons;

//For Restart
char *ebootpath;

int DesktopDirectory;

int frtd;
int LR_Wallpapers_ran;
char *LR_Wallpapers[256];
int LR_Wallpapers_amount;
int LR_Wallpapers_current;

SceIoDirent dir;

char *obj;
char *obj_x;
char *obj_y;

int Pastefile;

char *Keyboard_Output_Text;

int PSP_CTRL_CONFIRM;
int PSP_CTRL_BACK;

int DesktopEffect;
int toggle_wallpapers;
int mousespeed;
int mstart;
