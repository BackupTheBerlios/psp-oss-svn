/*
*****   ****  *****         *****     ****   **** 
****** ****** ******       *******   ****** ******
**  ** **  *  **  **      **    ***  **  *  **  * 
**  **  **    **  **     **      **   **     **   
******   **   ****** *** **      **    **     **  
*****      ** *****  *** **      **     **     ** 
**         ** **         ***    **      **     ** 
**     ****** **          *******   ****** ****** 
**      ****  **           *****     ****   ****  

-PlayStation Portable Open-Source Shell Source

WwW.PsP-OsS.CoM

*/

/*
PSP-OSS
*/

//PSP-OSS Startup code
#include "startup.h"
#include "functions.h"
#include "keyboard.h"
#include "actions.h"
#include "cursor.h"
#include "filebrowser.h"
#include "main.h"

void
StartUp (void)
{
  pspDebugScreenInit ();
  pspDebugScreenClear ();
  pspDebugScreenPrintf ("Please wait...");

  //If it's not a 1.5
  if (sceKernelDevkitVersion () != 0x01050001)
    {
      pspDebugScreenPrintf ("\n");
      pspDebugScreenPrintf ("\n");
      pspDebugScreenPrintf ("You are not using 1.5.");
      pspDebugScreenPrintf ("\n");
      pspDebugScreenPrintf
	("PSP-OSS was designed to run primarily on 1.5, as a result you may experience reduced functionality.");
      PauseVbl (5 * 60);
    }

  int filesize;
  SceUID file;
  char buffer[256];
	scePowerSetClockFrequency (333, 333, 166);
  
  /*
     Load Wallpaper
   */
  file = sceIoOpen ("ms0:/PSP-OSS/SYSTEM/WALLPAPER.cfg", PSP_O_RDONLY, 0);
  char tempwallpaper[255];
  sceIoRead (file, tempwallpaper, 255);
  filesize = sceIoLseek (file, 0, SEEK_END);
  sceIoClose (file);
  tempwallpaper[filesize] = 0x00;
  wallpaper = LoadGFX (tempwallpaper);

  /*
     What SKIN do we use? Let's check...
   */
  file = sceIoOpen ("ms0:/PSP-OSS/SYSTEM/SKIN.cfg", PSP_O_RDONLY, 0);
  sceIoRead (file, skin, 20);
  filesize = sceIoLseek (file, 0, SEEK_END);
  sceIoClose (file);
  skin[filesize] = 0x00;

  // Load Default Font
  sprintf (buffer, "ms0:/PSP-OSS/SKINS/%s/SYSTEM/FONT.ttf", skin);
  defaultFont = LoadFont (buffer);
  //defaultFont=SetPixelSize(defaultFont,0,10);

  /*
     Load the images we need for the startup screen
   */
  //sprintf (buffer, "ms0:/PSP-OSS/SKINS/%s/SYSTEM/taskbar.png", skin);
  //taskbar = LoadGFX (buffer);
  
  sprintf (buffer, "ms0:/PSP-OSS/SKINS/%s.rar", skin);
  taskbar = LoadGFX_RAR (buffer, "SYSTEM/taskbar.png");
  TopBar = LoadGFX_RAR (buffer, "SYSTEM/top_bar.png");
  cursor = LoadGFX_RAR (buffer, "SYSTEM/cursor.png");

  //Messagebox
  Message_Window_Top1 = LoadGFX_RAR (buffer, "WINDOWS/Message_top1.png");
  Message_Window_Top2 = LoadGFX_RAR (buffer, "WINDOWS/Message_top2.png");
  Message_Window_Body = LoadGFX_RAR (buffer, "WINDOWS/Message_body.png");
  Loadingbar = LoadGFX_RAR (buffer, "WINDOWS/Loadingbar.png");
  Loadingbar2 = LoadGFX_RAR (buffer, "WINDOWS/Loadingbar2.png");

  //Fade
  Fade = LoadGFX_RAR (buffer, "SYSTEM/fade.png");


  /*
     Display startup screen
   */
  initGraphics ();
  FadeScreenMessage ("Booting up...", "PSP-OSS is booting up",
		     "Please wait...", "");
		     PutGFX (0, 0, 206, 15, Loadingbar, 150, 157);	//Loading		     		     
  PrintScreen (); 
  
  /*
     Load the rest of the images
   */

  //Keyboard layout
  Keyboard_Output = LoadGFX_RAR (buffer, "SYSTEM/keyboard_output.png");
  Keyboard_Button1 = LoadGFX_RAR (buffer, "SYSTEM/keyboard_button1.png");
  Keyboard_Button2 = LoadGFX_RAR (buffer, "SYSTEM/keyboard_button2.png");
  Keyboard_ButtonOver = LoadGFX_RAR (buffer, "SYSTEM/keyboard_buttonOver.png");

  //Fullscreen window
  Fullscreen_Window_Top1 = LoadGFX_RAR (buffer, "WINDOWS/Fullscreen_top1.png");
  Fullscreen_Window_Top2 = LoadGFX_RAR (buffer, "WINDOWS/Fullscreen_top2.png");
  Fullscreen_Window_Body = LoadGFX_RAR (buffer, "WINDOWS/Fullscreen_body.png");

  Settings_Window = LoadGFX_RAR (buffer, "WINDOWS/Settings_Window.png");
  Settings_Window_Bottom = LoadGFX_RAR (buffer, "WINDOWS/Settings_Window_Bottom.png");


  //Window icons
  Window_Exit1 = LoadGFX_RAR (buffer, "WINDOWS/Exit1.png");
  Window_Exit2 = LoadGFX_RAR (buffer, "WINDOWS/Exit2.png");

  //Buttons
  Button1 = LoadGFX_RAR (buffer, "SYSTEM/button1.png");
  Button2 = LoadGFX_RAR (buffer, "SYSTEM/button2.png");

  USB_Icon = LoadGFX_RAR (buffer, "SYSTEM/usb.png");
  No_USB_Icon = LoadGFX_RAR (buffer, "SYSTEM/usb2.png");


  WLAN_Icon = LoadGFX_RAR (buffer, "SYSTEM/wlan.png");

  Music_play1 = LoadGFX_RAR (buffer, "SYSTEM/music_play1.png");
  Music_play2 = LoadGFX_RAR (buffer, "SYSTEM/music_play2.png");
  Music_pause1 = LoadGFX_RAR (buffer, "SYSTEM/music_pause1.png");
  Music_pause2 = LoadGFX_RAR (buffer, "SYSTEM/music_pause2.png");

  Battery_full = LoadGFX_RAR (buffer, "SYSTEM/battery_full.PNG");
  Battery_half = LoadGFX_RAR (buffer, "SYSTEM/battery_half.png");
  Battery_low = LoadGFX_RAR (buffer, "SYSTEM/battery_almost_empty.png");
  Battery_empty = LoadGFX_RAR (buffer, "SYSTEM/battery_empty.png");
  Battery_charging = LoadGFX_RAR (buffer, "SYSTEM/battery_charge.png");

  //WLANBackground = LoadGFX_RAR (buffer, "SYSTEM/WLAN_background.png");


  //Icons
  Icon_UMD = LoadGFX_RAR (buffer, "ICONS/UMD1.png");
  Icon_UMD_Over = LoadGFX_RAR (buffer, "ICONS/UMD2.png");
  Icon_Quit = LoadGFX_RAR (buffer, "ICONS/Quit1.png");
  Icon_Quit_Over = LoadGFX_RAR (buffer, "ICONS/Quit2.png");
  Icon_No_UMD = LoadGFX_RAR (buffer, "ICONS/No_UMD1.png");
  Icon_No_UMD_Over = LoadGFX_RAR (buffer, "ICONS/No_UMD2.png");
  Icon_GFX = LoadGFX_RAR (buffer, "ICONS/GFX1.png");
  Icon_GFX_Over = LoadGFX_RAR (buffer, "ICONS/GFX2.png");
  Icon_Audio = LoadGFX_RAR (buffer, "ICONS/Audio1.png");
  Icon_Audio_Over = LoadGFX_RAR (buffer, "ICONS/Audio2.png");
  Icon_Settings = LoadGFX_RAR (buffer, "ICONS/SETTINGS1.PNG");
  Icon_Settings_Over = LoadGFX_RAR (buffer, "ICONS/SETTINGS2.PNG");
  Icon_Themes = LoadGFX_RAR (buffer, "ICONS/THEMES1.png");
  Icon_Themes_Over = LoadGFX_RAR (buffer, "ICONS/THEMES2.png");
  Icon_Wallpapers = LoadGFX_RAR (buffer, "ICONS/WALLPAPERS1.png");
  Icon_Wallpapers_Over = LoadGFX_RAR (buffer, "ICONS/WALLPAPERS2.png");
  Icon_Eboot = LoadGFX_RAR (buffer, "ICONS/EBOOT1.png");
  Icon_Eboot_Over = LoadGFX_RAR (buffer, "ICONS/EBOOT2.png");
  Icon_Unknown = LoadGFX_RAR (buffer, "ICONS/UNKNOWN1.png");
  Icon_Unknown_Over = LoadGFX_RAR (buffer, "ICONS/UNKNOWN2.png");
  Icon_Video = LoadGFX_RAR (buffer, "ICONS/Video1.png");
  Icon_Video_Over = LoadGFX_RAR (buffer, "ICONS/Video2.png");
  Icon_Lua = LoadGFX_RAR (buffer, "ICONS/LUA1.png");
  Icon_Lua_Over = LoadGFX_RAR (buffer, "ICONS/LUA2.png");


  Audio_Player = LoadGFX_RAR (buffer, "SYSTEM/audio_player.png");
  Music_stop1 = LoadGFX_RAR (buffer, "SYSTEM/music_stop1.png");
  Music_stop2 = LoadGFX_RAR (buffer, "SYSTEM/music_stop2.png");

  Icon_Folder = LoadGFX_RAR (buffer, "ICONS/Folder1.png");
  Icon_Folder_Over = LoadGFX_RAR (buffer, "ICONS/Folder2.png");

  Icon_QuickLink = LoadGFX_RAR (buffer, "ICONS/QuickLink1.png");
  Icon_QuickLink_Over = LoadGFX_RAR (buffer, "ICONS/QuickLink2.png");

  Back = LoadGFX_RAR (buffer, "WINDOWS/Back1.png");
  Back_Over = LoadGFX_RAR (buffer, "WINDOWS/Back2.png");
  FBRight = LoadGFX_RAR (buffer, "WINDOWS/right.png");
  FBLeft = LoadGFX_RAR (buffer, "WINDOWS/left.png");

  //PowerButtons = LoadGFX_RAR (buffer, "WINDOWS/power_buttons.png");

  RightclickMenu_Top = LoadGFX_RAR (buffer, "SYSTEM/rightclick_top.png");
  RightclickMenu_Body = LoadGFX_RAR (buffer, "SYSTEM/rightclick_body1.png");
  RightclickMenu_Body_Over = LoadGFX_RAR (buffer, "SYSTEM/rightclick_body2.png");
  RightclickMenu_Bottom = LoadGFX_RAR (buffer, "SYSTEM/rightclick_bot.png");

  Start_menu = LoadGFX_RAR (buffer, "SYSTEM/Start1.png");
  Start_menu_Over = LoadGFX_RAR (buffer, "SYSTEM/Start2.png");
  Start_menu_Open = LoadGFX_RAR (buffer, "SYSTEM/Start3.png");

  Start_Menu_Body = LoadGFX_RAR (buffer, "SYSTEM/startmenu_body1.png");
  Start_Menu_Body_Over = LoadGFX_RAR (buffer, "SYSTEM/startmenu_body2.png");
  Start_Menu_Top = LoadGFX_RAR (buffer, "SYSTEM/startmenu_top.png");

  //Start Menu Pics
  SubMenuSelect = LoadGFX_RAR (buffer, "SYSTEM/START/submenu_select.png");
  SubMenuTop = LoadGFX_RAR (buffer, "SYSTEM/START/submenutop.png");
  SubMenuTopLeft = LoadGFX_RAR (buffer, "SYSTEM/START/submenutopleft.png");
  SubMenuTopRight = LoadGFX_RAR (buffer, "SYSTEM/START/submenutopright.png");
  SubMenuMiddle = LoadGFX_RAR (buffer, "SYSTEM/START/submenumiddle.png");
  SubMenuSideLeft = LoadGFX_RAR (buffer, "SYSTEM/START/submenusideleft.png");
  SubMenuSideRight = LoadGFX_RAR (buffer, "SYSTEM/START/submenusideright.png");
  SubMenuBottom = LoadGFX_RAR (buffer, "SYSTEM/START/submenubottom.png");
  SubMenuBottomLeft = LoadGFX_RAR (buffer, "SYSTEM/START/submenubottomleft.png");
  SubMenuBottomRight = LoadGFX_RAR (buffer, "SYSTEM/START/submenubottomright.png");
  
  textlang ();
  
	FadeScreenMessage ("Booting up...", "PSP-OSS is booting up",
		     "Please wait...", "");
		     PutGFX (0, 0, 10, 11, Loadingbar2, 152, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 162, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 172, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 182, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 192, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 202, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 212, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 222, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 232, 159);	//Loading
		     PutGFX (0, 0, 10, 11, Loadingbar2, 242, 159);	//Loading
		     PutGFX (0, 0, 206, 15, Loadingbar, 150, 157);	//Loading		     		     
  PrintScreen ();        		     
    
  textcolour ();
  
  //Run at 333mHz?
  file = sceIoOpen ("ms0:/PSP-OSS/SYSTEM/CONFIG/CPU.CFG", PSP_O_RDONLY, 0);
  char CPU[3];
  sceIoRead (file, CPU, 3);
  sceIoClose (file);
  CPU[3] = 0x00;  

  if (strcmp (CPU, "222") == 0)
    {
      scePowerSetClockFrequency (222, 222, 133);
    }
  else if (strcmp (CPU, "265") == 0 || strcmp (CPU, "266") == 0)
    {
      scePowerSetClockFrequency (266, 266, 133);
    }  
    
    else if (strcmp (CPU, "333") == 0)
    {
      scePowerSetClockFrequency (333, 333, 166);
    }

  /*
     Initialize some stuff...
   */

  //Timezone
  initTimezone ();

  //Audio output
  pspAudioInit ();

  //Init USB mode
  usbState = 0;
  LoadStartModule ("flash0:/kd/semawm.prx");
  LoadStartModule ("flash0:/kd/usbstor.prx");
  LoadStartModule ("flash0:/kd/usbstormgr.prx");
  LoadStartModule ("flash0:/kd/usbstorms.prx");
  LoadStartModule ("flash0:/kd/usbstorboot.prx");



  file = sceIoOpen ("ms0:/PSP-OSS/SYSTEM/CONFIG/KEYS.cfg", PSP_O_RDONLY, 0);
  char keys[2];
  sceIoRead (file, keys, 2);
  sceIoClose (file);
  keys[2] = 0x00;

  //KEYS
  if (strcmp (keys, "EN") == 0)
    {
      PSP_CTRL_CONFIRM = 0x004000;	//CROSS
      PSP_CTRL_BACK = 0x002000;	//CIRCLE
    }
  else if (strcmp (keys, "JP") == 0)
    {
      PSP_CTRL_CONFIRM = 0x002000;	//CIRCLE
      PSP_CTRL_BACK = 0x004000;	//CROSS
    }
  else
    {
      //No key settings. Create one
      file =
	sceIoOpen ("ms0:/PSP-OSS/SYSTEM/CONFIG/KEYS.cfg",
		   PSP_O_WRONLY | PSP_O_CREAT | PSP_O_TRUNC, 0777);
      sceIoWrite (file, "EN", 2);
      sceIoClose (file);

      //Set keys to EN
      PSP_CTRL_CONFIRM = 0x004000;	//CROSS
      PSP_CTRL_BACK = 0x002000;	//CIRCLE
    }
  /*
     //Toggle wallpapers
     // START OF CODE
   */
  file =
    sceIoOpen ("ms0:/PSP-OSS/SYSTEM/CONFIG/TOGGLE_WALLPAPERS.cfg",
	       PSP_O_RDONLY, 0);
  char toggle_wall[3];
  sceIoRead (file, toggle_wall, 3);
  sceIoClose (file);
  toggle_wall[3] = 0x00;

  if (strcmp (toggle_wall, "LRT") == 0)
    {
      toggle_wallpapers = "LRT";
    }
  else if (strcmp (toggle_wall, "SEL") == 0)
    {
      toggle_wallpapers = "SEL";
    }
  else if (strcmp (toggle_wall, "OFF") == 0)
    {
      toggle_wallpapers = "OFF";
    }
  /*
     //Toggle wallpapers
     // END OF CODE
   */

  //Effects
  file = sceIoOpen ("ms0:/PSP-OSS/SYSTEM/CONFIG/EFFECT.CFG", PSP_O_RDONLY, 0);
  char effect[20];
  sceIoRead (file, effect, 20);
  filesize = sceIoLseek (file, 0, SEEK_END);
  sceIoClose (file);
  effect[filesize] = 0x00;

  if (strcmp (effect, "Snow") == 0)
    {
      Effect_GFX1 = LoadGFX ("ms0:/PSP-OSS/SYSTEM/IMAGES/snow.png");

      DesktopEffect = "Snow";
      Effect_Snow_PositionX = 0;
      Effect_Snow_PositionY = 0;
    }
  else if (strcmp (effect, "Stripes") == 0)
    {
      DesktopEffect = "Lines";
    }
  else
    {
      DesktopEffect = "None";
    }

  //Mouse Speed
  file =
    sceIoOpen ("ms0:/PSP-OSS/SYSTEM/CONFIG/MOUSE_SPEED.cfg", PSP_O_RDONLY, 0);
  char Mspeed[1];
  sceIoRead (file, Mspeed, 1);
  sceIoClose (file);
  Mspeed[1] = 0x00;

  if (strcmp (Mspeed, "1") == 0)
    {
      mousespeed = 2;
    }
  else if (strcmp (Mspeed, "2") == 0)
    {
      mousespeed = 3;
    }
  else if (strcmp (Mspeed, "3") == 0)
    {
      mousespeed = 4;
    }
  else if (strcmp (Mspeed, "4") == 0)
    {
      mousespeed = 5;
    }
  else if (strcmp (Mspeed, "5") == 0)
    {
      mousespeed = 6;
    }
  else if (strcmp (Mspeed, "6") == 0)
    {
      mousespeed = 7;
    }


  //Place cursor in the middle of the screen
  cursorPosition.x = 208;
  cursorPosition.y = 104;

  FilebrowserRightclickActive = 0;

  //Remove tempfile (for copy/cut/paste)
  Pastefile = 0;
  sceIoRemove ("ms0:/PSP-OSS/SYSTEM/tempfile");
  sceIoRemove ("ms0:/PSP-OSS/SYSTEM/tempfile_name");

  //Controls
  sceCtrlSetSamplingCycle (0);
  sceCtrlSetSamplingMode (PSP_CTRL_MODE_ANALOG);
  MediaStatus = "stop";		//We're not playing any music, so set startus to stop, so mp3 controls wont show up

  frtd = 1;

  LR_Wallpapers_current = 0;
  LR_Wallpapers_ran = 0;

  //Desktop is active :)
  DesktopActive = 1;
  DesktopIconsActive = 1;

  //Clear screen
  pspDebugScreenClear ();
  pspDebugScreenInit ();

}
