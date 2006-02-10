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
#include <psputils.h>
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
Image *Loadingbar;
Image *Loadingbar2;
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
Image *Icon_Video;
Image *Icon_Video_Over;
Image *Icon_Lua;
Image *Icon_Lua_Over;

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
int LR_Wallpapers_previous;

int LR_MUSIC_ran;
char *LR_MUSIC[256];
int LR_MUSIC_amount;
int LR_MUSIC_current;

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

char skin[20];
char fontcolour[20];
//Custom Text Colours
float StartMenuC;		// Text Colour
float StartSubMenuC;		// Text Colour
float StartSubMenuOverC;	// Text Colour
float StartSubMenuTypeC;	// Text Colour
float StartSubMenuEmptyC;	// Text Colour
float BrowseC;
float GamesC;
float MusicC;
float PicturesC;
float SystemC;
float QuitC;

//Image Related
float FSImageUseC;
float OpenC;
float CopyC;
float PasteC;
float RenameC;
float DeleteC;
float MakeQLC;

//Desktop Right Click Menu Related
float BackgrC;
float ThemeC;
float DesktopTextC;
float DesktopTextOverC;

//Settings
float WallpaperTextTBC;
float WallpaperTextC;
float WallpaperTextHLC;
float WallpaperTextOverC;
float SkinTextTBC;
float SkinTextC;
float SkinTextHLC;
float SkinTextOverC;
float FileBrowserTextC;
float FileBrowserTextOverC;

//Desktop
float OSSVersionC;
float BatteryC;
float TimeC;
float ExitOSSC;
float StartUMDC;
float NoUMDC;
float SettingsC;
float USBC;

//Music
float PlayC;
float PauseC;
float StopC;

//General
float DirectoryC;
float GraphicC;
float MusicC;
float ExecutableC;
float QuickLinkC;
float LUAC;
float UnknownC;
float PreviousPageC;
float NextPageC;
float KeyboardC;
float Keyboard2C;

//Settings
float LanguageC;
float CPUC;
float ConfirmC;
float ToggleWallpaperC;
float DeasktopEffectC;
float MouseSpeedC;
float SettingsC;
float Settings2C;

//Windows
float OKC;
float ShutdownC;
float Shutdown2C;
float RebootC;
float QuestionC;
float WindowHeaderC;
float WindowMessageC;
float FSChangeSkinC;
float FSChangeWallC;
float FSWindowHeaderC;

//Custom Language Text
//UMD Related
char UMDLoadT[50];
char UMDLoad2T[50];
char NoUMDT[50];
char NoUMD2T[50];

//Skin Related
char ReloadSkinT[50];
char ReloadSkin2T[50];

//Lua Related

char LUALoadT[50];
char LUALoad2T[50];

//Full Sceen Window
char FSImageT[50];
char FSImageUseT[50];
char FSWallpaperT[50];
char FSThemeT[50];
char FSConfigurationT[50];
char FSChangeWallT[50];
char FSChangeSkinT[50];

//Right Click Menu Related
char OpenT[50];
char CopyT[50];
char PasteT[50];
char RenameT[50];
char DeleteT[50];
char MakeQLT[50];

//Desktop Right Click Menu Related
char BackgrT[50];
char ThemeT[50];

//Desktop
char USBT[50];
char UsingACT[50];
char ExitOSST[50];
char StartUMDT[50];
char NoUMDT[50];
char SettingsT[50];

//Music
char PlayT[50];
char PauseT[50];
char StopT[50];

//General
char WaitT[50];
char DirectoryT[50];
char GraphicT[50];
char MusicT[50];
char ExecutableT[50];
char QuickLinkT[50];
char LUAT[50];
char UnknownT[50];
char PreviousPageT[50];
char NextPageT[50];
char UnknownQLT[50];
char UnknownQL2T[50];
char CrashT[50];
char Crash2T[50];

//Settings
char LanguageT[50];
char CPUT[50];
char ConfirmT[50];
char ToggleWallpaperT[50];
char DeasktopEffectT[50];
char MouseSpeedT[50];

//Start Menu
char BrowseT[50];
char GamesT[50];
char MusicT[50];
char PicturesT[50];
char SystemT[50];
char QuitT[50];
char MoreT[50];
char EmptyT[50];
char SMWallpapersT[50];
char SMSettingsT[50];
char SMThemesT[50];

//USB
char USBModeT[50];
char USBActiveT[50];
char USBCableT[50];

//Windows
char OKT[50];
char ShutdownT[50];
char RebootT[50];
char QuestionT[50];

//MP3
 char Audiofolder[255];
