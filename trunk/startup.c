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
  char buffer[200];

  //Run at 333mHz?
  file = sceIoOpen ("ms0:/PSP-OSS/SYSTEM/CONFIG/CPU.CFG", PSP_O_RDONLY, 0);
  char CPU[3];
  sceIoRead (file, CPU, 3);
  CPU[3] = 0x00;
  sceIoClose (file);

  if (strcmp (CPU, "333") == 0)
    {
      scePowerSetClockFrequency (333, 333, 166);
    }
  if (strcmp (CPU, "222") == 0)
    {
      scePowerSetClockFrequency (222, 222, 133);
    }
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
  char skin[20];
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
  sprintf (buffer, "ms0:/PSP-OSS/SKINS/%s/SYSTEM/taskbar.png", skin);
  taskbar = LoadGFX (buffer);
  sprintf (buffer, "ms0:/PSP-OSS/SKINS/%s/SYSTEM/top_bar.png", skin);
  TopBar = LoadGFX (buffer);
  sprintf (buffer, "ms0:/PSP-OSS/SKINS/%s/SYSTEM/cursor.png", skin);
  cursor = LoadGFX (buffer);

  //Messagebox
  sprintf (buffer, "ms0:/PSP-OSS/SKINS/%s/WINDOWS/Message_top1.png", skin);
  Message_Window_Top1 = LoadGFX (buffer);
  sprintf (buffer, "ms0:/PSP-OSS/SKINS/%s/WINDOWS/Message_top2.png", skin);
  Message_Window_Top2 = LoadGFX (buffer);
  sprintf (buffer, "ms0:/PSP-OSS/SKINS/%s/WINDOWS/Message_body.png", skin);
  Message_Window_Body = LoadGFX (buffer);

  //Fade
  sprintf (buffer, "ms0:/PSP-OSS/SKINS/%s/SYSTEM/fade.png", skin);
  Fade = LoadGFX (buffer);


  /*
     Display startup screen
   */
  initGraphics ();
  FadeScreenMessage ("Booting up...", "PSP-OSS is booting up",
		     "Please wait...", "");
  PrintScreen ();

  /*
     Load the rest of the images
   */

  //Keyboard layout
  sprintf (buffer, "ms0:/PSP-OSS/SKINS/%s/SYSTEM/keyboard_output.png", skin);
  Keyboard_Output = LoadGFX (buffer);
  sprintf (buffer, "ms0:/PSP-OSS/SKINS/%s/SYSTEM/keyboard_button1.png", skin);
  Keyboard_Button1 = LoadGFX (buffer);
  sprintf (buffer, "ms0:/PSP-OSS/SKINS/%s/SYSTEM/keyboard_button2.png", skin);
  Keyboard_Button2 = LoadGFX (buffer);
  sprintf (buffer, "ms0:/PSP-OSS/SKINS/%s/SYSTEM/keyboard_buttonOver.png",
	   skin);
  Keyboard_ButtonOver = LoadGFX (buffer);

  //Fullscreen window
  sprintf (buffer, "ms0:/PSP-OSS/SKINS/%s/WINDOWS/Fullscreen_top1.png", skin);
  Fullscreen_Window_Top1 = LoadGFX (buffer);
  sprintf (buffer, "ms0:/PSP-OSS/SKINS/%s/WINDOWS/Fullscreen_top2.png", skin);
  Fullscreen_Window_Top2 = LoadGFX (buffer);
  sprintf (buffer, "ms0:/PSP-OSS/SKINS/%s/WINDOWS/Fullscreen_body.png", skin);
  Fullscreen_Window_Body = LoadGFX (buffer);

  sprintf (buffer, "ms0:/PSP-OSS/SKINS/%s/WINDOWS/Settings_Window.png", skin);
  Settings_Window = LoadGFX (buffer);
  sprintf (buffer, "ms0:/PSP-OSS/SKINS/%s/WINDOWS/Settings_Window_Over.png",
	   skin);
  Settings_Window_Over = LoadGFX (buffer);
  sprintf (buffer, "ms0:/PSP-OSS/SKINS/%s/WINDOWS/Settings_Window_Bottom.png",
	   skin);
  Settings_Window_Bottom = LoadGFX (buffer);


  //Window icons
  sprintf (buffer, "ms0:/PSP-OSS/SKINS/%s/WINDOWS/Exit1.png", skin);
  Window_Exit1 = LoadGFX (buffer);
  sprintf (buffer, "ms0:/PSP-OSS/SKINS/%s/WINDOWS/Exit2.png", skin);
  Window_Exit2 = LoadGFX (buffer);

  //Buttons
  sprintf (buffer, "ms0:/PSP-OSS/SKINS/%s/SYSTEM/button1.png", skin);
  Button1 = LoadGFX (buffer);
  sprintf (buffer, "ms0:/PSP-OSS/SKINS/%s/SYSTEM/button2.png", skin);
  Button2 = LoadGFX (buffer);

  sprintf (buffer, "ms0:/PSP-OSS/SKINS/%s/SYSTEM/usb.png", skin);
  USB_Icon = LoadGFX (buffer);
  sprintf (buffer, "ms0:/PSP-OSS/SKINS/%s/SYSTEM/usb2.png", skin);
  No_USB_Icon = LoadGFX (buffer);


  sprintf (buffer, "ms0:/PSP-OSS/SKINS/%s/SYSTEM/wlan.png", skin);
  WLAN_Icon = LoadGFX (buffer);

  sprintf (buffer, "ms0:/PSP-OSS/SKINS/%s/SYSTEM/music_play1.png", skin);
  Music_play1 = LoadGFX (buffer);
  sprintf (buffer, "ms0:/PSP-OSS/SKINS/%s/SYSTEM/music_play2.png", skin);
  Music_play2 = LoadGFX (buffer);
  sprintf (buffer, "ms0:/PSP-OSS/SKINS/%s/SYSTEM/music_pause1.png", skin);
  Music_pause1 = LoadGFX (buffer);
  sprintf (buffer, "ms0:/PSP-OSS/SKINS/%s/SYSTEM/music_pause2.png", skin);
  Music_pause2 = LoadGFX (buffer);

  sprintf (buffer, "ms0:/PSP-OSS/SKINS/%s/SYSTEM/battery_full.PNG", skin);
  Battery_full = LoadGFX (buffer);
  sprintf (buffer, "ms0:/PSP-OSS/SKINS/%s/SYSTEM/battery_half.png", skin);
  Battery_half = LoadGFX (buffer);
  sprintf (buffer, "ms0:/PSP-OSS/SKINS/%s/SYSTEM/battery_almost_empty.png",
	   skin);
  Battery_low = LoadGFX (buffer);
  sprintf (buffer, "ms0:/PSP-OSS/SKINS/%s/SYSTEM/battery_empty.png", skin);
  Battery_empty = LoadGFX (buffer);
  sprintf (buffer, "ms0:/PSP-OSS/SKINS/%s/SYSTEM/battery_charge.png", skin);
  Battery_charging = LoadGFX (buffer);

  sprintf (buffer, "ms0:/PSP-OSS/SKINS/%s/SYSTEM/WLAN_background.png", skin);
  WLANBackground = LoadGFX (buffer);

  sprintf (buffer, "ms0:/PSP-OSS/SKINS/%s/SYSTEM/Progressbar.png", skin);
  Progressbar = LoadGFX (buffer);
  sprintf (buffer, "ms0:/PSP-OSS/SKINS/%s/SYSTEM/Progressbar_fill.png", skin);
  Progressbar_fill = LoadGFX (buffer);

  //Icons
  sprintf (buffer, "ms0:/PSP-OSS/SKINS/%s/ICONS/UMD1.png", skin);
  Icon_UMD = LoadGFX (buffer);
  sprintf (buffer, "ms0:/PSP-OSS/SKINS/%s/ICONS/UMD2.png", skin);
  Icon_UMD_Over = LoadGFX (buffer);
  sprintf (buffer, "ms0:/PSP-OSS/SKINS/%s/ICONS/Quit1.png", skin);
  Icon_Quit = LoadGFX (buffer);
  sprintf (buffer, "ms0:/PSP-OSS/SKINS/%s/ICONS/Quit2.png", skin);
  Icon_Quit_Over = LoadGFX (buffer);
  sprintf (buffer, "ms0:/PSP-OSS/SKINS/%s/ICONS/No_UMD1.png", skin);
  Icon_No_UMD = LoadGFX (buffer);
  sprintf (buffer, "ms0:/PSP-OSS/SKINS/%s/ICONS/No_UMD2.png", skin);
  Icon_No_UMD_Over = LoadGFX (buffer);
  sprintf (buffer, "ms0:/PSP-OSS/SKINS/%s/ICONS/GFX1.png", skin);
  Icon_GFX = LoadGFX (buffer);
  sprintf (buffer, "ms0:/PSP-OSS/SKINS/%s/ICONS/GFX2.png", skin);
  Icon_GFX_Over = LoadGFX (buffer);
  sprintf (buffer, "ms0:/PSP-OSS/SKINS/%s/ICONS/Audio1.png", skin);
  Icon_Audio = LoadGFX (buffer);
  sprintf (buffer, "ms0:/PSP-OSS/SKINS/%s/ICONS/Audio2.png", skin);
  Icon_Audio_Over = LoadGFX (buffer);
  sprintf (buffer, "ms0:/PSP-OSS/SKINS/%s/ICONS/SETTINGS1.PNG", skin);
  Icon_Settings = LoadGFX (buffer);
  sprintf (buffer, "ms0:/PSP-OSS/SKINS/%s/ICONS/SETTINGS2.PNG", skin);
  Icon_Settings_Over = LoadGFX (buffer);
  sprintf (buffer, "ms0:/PSP-OSS/SKINS/%s/ICONS/THEMES1.png", skin);
  Icon_Themes = LoadGFX (buffer);
  sprintf (buffer, "ms0:/PSP-OSS/SKINS/%s/ICONS/THEMES2.png", skin);
  Icon_Themes_Over = LoadGFX (buffer);
  sprintf (buffer, "ms0:/PSP-OSS/SKINS/%s/ICONS/WALLPAPERS1.png", skin);
  Icon_Wallpapers = LoadGFX (buffer);
  sprintf (buffer, "ms0:/PSP-OSS/SKINS/%s/ICONS/WALLPAPERS2.png", skin);
  Icon_Wallpapers_Over = LoadGFX (buffer);
  sprintf (buffer, "ms0:/PSP-OSS/SKINS/%s/ICONS/EBOOT1.png", skin);
  Icon_Eboot = LoadGFX (buffer);
  sprintf (buffer, "ms0:/PSP-OSS/SKINS/%s/ICONS/EBOOT2.png", skin);
  Icon_Eboot_Over = LoadGFX (buffer);
  sprintf (buffer, "ms0:/PSP-OSS/SKINS/%s/ICONS/UNKNOWN1.png", skin);
  Icon_Unknown = LoadGFX (buffer);
  sprintf (buffer, "ms0:/PSP-OSS/SKINS/%s/ICONS/UNKNOWN2.png", skin);
  Icon_Unknown_Over = LoadGFX (buffer);

  sprintf (buffer, "ms0:/PSP-OSS/SKINS/%s/SYSTEM/audio_player.png", skin);
  Audio_Player = LoadGFX (buffer);
  sprintf (buffer, "ms0:/PSP-OSS/SKINS/%s/SYSTEM/music_stop1.png", skin);
  Music_stop1 = LoadGFX (buffer);
  sprintf (buffer, "ms0:/PSP-OSS/SKINS/%s/SYSTEM/music_stop2.png", skin);
  Music_stop2 = LoadGFX (buffer);

  sprintf (buffer, "ms0:/PSP-OSS/SKINS/%s/ICONS/Folder1.png", skin);
  Icon_Folder = LoadGFX (buffer);
  sprintf (buffer, "ms0:/PSP-OSS/SKINS/%s/ICONS/Folder2.png", skin);
  Icon_Folder_Over = LoadGFX (buffer);

  sprintf (buffer, "ms0:/PSP-OSS/SKINS/%s/ICONS/QuickLink1.png", skin);
  Icon_QuickLink = LoadGFX (buffer);
  sprintf (buffer, "ms0:/PSP-OSS/SKINS/%s/ICONS/QuickLink2.png", skin);
  Icon_QuickLink_Over = LoadGFX (buffer);

  sprintf (buffer, "ms0:/PSP-OSS/SKINS/%s/WINDOWS/Back1.png", skin);
  Back = LoadGFX (buffer);
  sprintf (buffer, "ms0:/PSP-OSS/SKINS/%s/WINDOWS/Back2.png", skin);
  Back_Over = LoadGFX (buffer);
  sprintf (buffer, "ms0:/PSP-OSS/SKINS/%s/WINDOWS/right.png", skin);
  FBRight = LoadGFX (buffer);
  sprintf (buffer, "ms0:/PSP-OSS/SKINS/%s/WINDOWS/left.png", skin);
  FBLeft = LoadGFX (buffer);

  sprintf (buffer, "ms0:/PSP-OSS/SKINS/%s/WINDOWS/power_buttons.png", skin);
  PowerButtons = LoadGFX (buffer);

  sprintf (buffer, "ms0:/PSP-OSS/SKINS/%s/SYSTEM/rightclick_top.png", skin);
  RightclickMenu_Top = LoadGFX (buffer);
  sprintf (buffer, "ms0:/PSP-OSS/SKINS/%s/SYSTEM/rightclick_body1.png", skin);
  RightclickMenu_Body = LoadGFX (buffer);
  sprintf (buffer, "ms0:/PSP-OSS/SKINS/%s/SYSTEM/rightclick_body2.png", skin);
  RightclickMenu_Body_Over = LoadGFX (buffer);
  sprintf (buffer, "ms0:/PSP-OSS/SKINS/%s/SYSTEM/rightclick_bot.png", skin);
  RightclickMenu_Bottom = LoadGFX (buffer);

  sprintf (buffer, "ms0:/PSP-OSS/SKINS/%s/SYSTEM/Start1.png", skin);
  Start_menu = LoadGFX (buffer);
  sprintf (buffer, "ms0:/PSP-OSS/SKINS/%s/SYSTEM/Start2.png", skin);
  Start_menu_Over = LoadGFX (buffer);
  sprintf (buffer, "ms0:/PSP-OSS/SKINS/%s/SYSTEM/Start3.png", skin);
  Start_menu_Open = LoadGFX (buffer);

  sprintf (buffer, "ms0:/PSP-OSS/SKINS/%s/SYSTEM/startmenu_body1.png", skin);
  Start_Menu_Body = LoadGFX (buffer);
  sprintf (buffer, "ms0:/PSP-OSS/SKINS/%s/SYSTEM/startmenu_body2.png", skin);
  Start_Menu_Body_Over = LoadGFX (buffer);

  sprintf (buffer, "ms0:/PSP-OSS/SKINS/%s/SYSTEM/startmenu_top.png", skin);
  Start_Menu_Top = LoadGFX (buffer);

  //Start Menu Pics
  sprintf (buffer, "ms0:/PSP-OSS/SKINS/%s/SYSTEM/START/submenu_select.png",
	   skin);
  SubMenuSelect = LoadGFX (buffer);
  sprintf (buffer, "ms0:/PSP-OSS/SKINS/%s/SYSTEM/START/submenutop.png", skin);
  SubMenuTop = LoadGFX (buffer);
  sprintf (buffer, "ms0:/PSP-OSS/SKINS/%s/SYSTEM/START/submenutopleft.png",
	   skin);
  SubMenuTopLeft = LoadGFX (buffer);
  sprintf (buffer, "ms0:/PSP-OSS/SKINS/%s/SYSTEM/START/submenutopright.png",
	   skin);
  SubMenuTopRight = LoadGFX (buffer);
  sprintf (buffer, "ms0:/PSP-OSS/SKINS/%s/SYSTEM/START/submenumiddle.png",
	   skin);
  SubMenuMiddle = LoadGFX (buffer);
  sprintf (buffer, "ms0:/PSP-OSS/SKINS/%s/SYSTEM/START/submenusideleft.png",
	   skin);
  SubMenuSideLeft = LoadGFX (buffer);
  sprintf (buffer, "ms0:/PSP-OSS/SKINS/%s/SYSTEM/START/submenusideright.png",
	   skin);
  SubMenuSideRight = LoadGFX (buffer);
  sprintf (buffer, "ms0:/PSP-OSS/SKINS/%s/SYSTEM/START/submenubottom.png",
	   skin);
  SubMenuBottom = LoadGFX (buffer);
  sprintf (buffer, "ms0:/PSP-OSS/SKINS/%s/SYSTEM/START/submenubottomleft.png",
	   skin);
  SubMenuBottomLeft = LoadGFX (buffer);
  sprintf (buffer,
	   "ms0:/PSP-OSS/SKINS/%s/SYSTEM/START/submenubottomright.png", skin);
  SubMenuBottomRight = LoadGFX (buffer);

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
  else if (strcmp (effect, "Fountain") == 0)
    {
      DesktopEffect = "Fountain";
    }
  else
    {
      DesktopEffect = "None";
    }

  //Mouse Speed
  file = sceIoOpen ("ms0:/PSP-OSS/SYSTEM/CONFIG/MOUSE_SPEED.cfg", PSP_O_RDONLY, 0);
  char Mspeed[1];
  sceIoRead (file, Mspeed, 1);
  sceIoClose (file);
  Mspeed[1] = 0x00;

  if (strcmp (Mspeed, "1") == 0)
    {
      mousespeed = 1;
    }
  else if (strcmp (Mspeed, "2") == 0)
    {
      mousespeed = 2;
    }
  else if (strcmp (Mspeed, "3") == 0)
    {
      mousespeed = 3;
    }
  else if (strcmp (Mspeed, "4") == 0)
    {
      mousespeed = 4;
    }
  else if (strcmp (Mspeed, "5") == 0)
    {
      mousespeed = 5;
    }
  else if (strcmp (Mspeed, "6") == 0)
    {
      mousespeed = 6;
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

  //Does the CONFIG file exist? if not, its most likely the first run, so display the wizard
  file = sceIoOpen ("ms0:/PSP-OSS/SYSTEM/SETTINGS.cfg", PSP_O_RDONLY, 0);
  sceIoClose (file);

  if (file < 0)
    {
      //FirstRun();
    }

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
