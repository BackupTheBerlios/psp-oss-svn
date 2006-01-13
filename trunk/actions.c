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
PSP-OSS Event Handlers
*/
#include "main.h"
#include "functions.h"
#include "usb.h"

// Handle System Icon Selection
void
Execute ()
{

  // Display the Shutdown/Reboot Menu
  if (iconSelected.row == 8 && iconSelected.col == 4)
    {
      ShutDown_Prompt ();
    }

  // Load/Run the UMD
  else if (iconSelected.row == 8 && iconSelected.col == 3)
    {
      int UMD_CHK = sceUmdCheckMedium (0);
      if (!UMD_CHK == 0)
	{
	  FadeScreenMessage ("Loading UMD...", "PSP-OSS is loading UMD",
			     "Please wait...", "");
	  PrintScreen ();
	  UMD_Run ();
	}
      else
	{
	  MessageWindow ("No UMD", "Please insert a UMD and try again");
	}
    }

  // Display Configuration/Settings Panel
  else if (iconSelected.row == 8 && iconSelected.col == 2)
    {
      Configuration ();
    }

  // Open Start Menu
  else if (cursorPosition.x > 0 && cursorPosition.x < 70
	   && cursorPosition.y > 257 && cursorPosition.y < 272)
    {
      StartMenu ();
    }

  //USB Mode
  else if (cursorPosition.x > 417 && cursorPosition.x < 433
	   && cursorPosition.y > 0 && cursorPosition.y < 12)
    {
      USB_Mode ();
    }
 
}

// Set the Wallpaper
void
SetWallpaper (const char *NewWallpaper)
{
  SceUID file;
  file =
    sceIoOpen ("ms0:/PSP-OSS/SYSTEM/WALLPAPER.cfg",
	       PSP_O_WRONLY | PSP_O_CREAT | PSP_O_TRUNC, 0777);
  sceIoWrite (file, NewWallpaper, strlen (NewWallpaper));
  sceIoClose (file);

  //Free the old image before we load a new one, to avoid an overflow.
  freeImage (wallpaper);

  // Load the New Wallpaper
  wallpaper = LoadGFX (NewWallpaper);
}

// Set new skin
void
SetSkin (const char *NewSkin)
{
  SceUID file;
  file =
    sceIoOpen ("ms0:/PSP-OSS/SYSTEM/SKIN.cfg",
	       PSP_O_WRONLY | PSP_O_CREAT | PSP_O_TRUNC, 0777);
  sceIoWrite (file, NewSkin, strlen (NewSkin));
  sceIoClose (file);
  ReloadSkin ();
}

void
ReloadSkin ()
{
  FadeScreenMessage ("Reloading skin", "Reloading skin...", "Please wait...",
		     "");
  PrintScreen ();

  freeImage (taskbar);
  freeImage (TopBar);
  freeImage (cursor);
  freeImage (Keyboard_Output);
  freeImage (Keyboard_Button1);
  freeImage (Keyboard_Button2);
  freeImage (Keyboard_ButtonOver);
  freeImage (Message_Window_Top1);
  freeImage (Message_Window_Top2);
  freeImage (Message_Window_Body);
  freeImage (Fullscreen_Window_Top1);
  freeImage (Fullscreen_Window_Top2);
  freeImage (Fullscreen_Window_Body);
  freeImage (Window_Exit1);
  freeImage (Window_Exit2);
  freeImage (USB_Icon);
  freeImage (No_USB_Icon);
  freeImage (Fade);
  freeImage (Battery_full);
  freeImage (Battery_half);
  freeImage (Battery_low);
  freeImage (Battery_empty);
  freeImage (Battery_charging);
  freeImage (Icon_Eboot);
  freeImage (Icon_Eboot_Over);
  freeImage (Icon_Unknown);
  freeImage (Icon_Unknown_Over);
  freeImage (Icon_Settings);
  freeImage (Icon_Settings_Over);
  freeImage (Icon_Themes);
  freeImage (Icon_Themes_Over);
  freeImage (Icon_Wallpapers);
  freeImage (Icon_Wallpapers_Over);
  freeImage (Icon_Quit);
  freeImage (Icon_Quit_Over);
  freeImage (Icon_GFX);
  freeImage (Icon_GFX_Over);
  freeImage (Icon_Audio);
  freeImage (Icon_Audio_Over);
  freeImage (Icon_UMD);
  freeImage (Icon_UMD_Over);
  freeImage (Icon_No_UMD);
  freeImage (Icon_No_UMD_Over);
  freeImage (Icon_QuickLink);
  freeImage (Icon_QuickLink_Over);
  freeImage (Button1);
  freeImage (Button2);
  freeImage (Music_play1);
  freeImage (Music_play2);
  freeImage (Music_pause1);
  freeImage (Music_pause2);
  freeImage (Music_stop1);
  freeImage (Music_stop2);
  freeImage (Icon_Folder);
  freeImage (Icon_Folder_Over);
  freeImage (Back);
  freeImage (Back_Over);
  freeImage (RightclickMenu_Top);
  freeImage (RightclickMenu_Body);
  freeImage (RightclickMenu_Body_Over);
  freeImage (RightclickMenu_Bottom);
  freeImage (Start_menu);
  freeImage (Start_menu_Over);
  freeImage (Start_menu_Open);
  freeImage (Start_Menu_Body);
  freeImage (Start_Menu_Body_Over);
  freeImage (Start_Menu_Top);
  freeImage (SubMenuTop);
  freeImage (SubMenuTopLeft);
  freeImage (SubMenuTopRight);
  freeImage (SubMenuMiddle);
  freeImage (SubMenuSelect);
  freeImage (SubMenuSideLeft);
  freeImage (SubMenuSideRight);
  freeImage (SubMenuBottom);
  freeImage (SubMenuBottomLeft);
  freeImage (SubMenuBottomRight);
  freeImage (Settings_Window);
  freeImage (Settings_Window_Bottom);

  int filesize;
  SceUID file;
  char buffer[200];

  /*
     What SKIN do we use? Let's check...
   */
  file = sceIoOpen ("ms0:/PSP-OSS/SYSTEM/SKIN.cfg", PSP_O_RDONLY, 0);
  char skin[20];
  sceIoRead (file, skin, 20);
  filesize = sceIoLseek (file, 0, SEEK_END);
  sceIoClose (file);
  skin[filesize] = 0x00;

  /*
     Load the images we need for the startup screen
   */

  sprintf (buffer, "ms0:/PSP-OSS/SKINS/%s/WINDOWS/Settings_Window.png", skin);
  Settings_Window = LoadGFX (buffer);
  sprintf (buffer, "ms0:/PSP-OSS/SKINS/%s/WINDOWS/Settings_Window_Bottom.png",
	   skin);
  Settings_Window_Bottom = LoadGFX (buffer);

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

}

// JPEG Suffix Check
int
isJpegFile (const char *filename)
{
  char *suffix = strrchr (filename, '.');
  if (suffix)
    {
      if (stricmp (suffix, ".jpg") == 0 || stricmp (suffix, ".jpeg") == 0
	  || stricmp (suffix, ".thm") == 0)
	return 0;
      // Check for .JPG, .JPEG, and .THM File Suffixes
    }
  return 1;
}

// View Image File
void
ViewImage (const char *filename)
{
  int ftb = 0;
  int jpg = 0;

  if (isJpegFile (filename) == 0)
    {				// Check if the File is a JPEG
      TempImage = loadJpegImage (filename);	// Load the Image into Memory as a JPG File
      jpg = 1;			// The File is a JPEG
    }
  else
    {
      TempImage = LoadGFX (filename);	// Load the Image into Memory
    }

  if ((TempImage->imageHeight > 512 || TempImage->imageWidth > 512))
    {
      ftb = 1;			// The File is too Big
      freeImage (TempImage);	// Release the Image from Memory
      TempImage = LoadGFX ("ms0:/PSP-OSS/SYSTEM/IMAGES/TooLarge.png");	// Display "Too Large" Error Image
    }
  int ty = 15;
  int tx = 0;

  // Center the Top-Left Position of the Image
  tx = 480 / 2 - TempImage->imageWidth / 2;
  ty = ((272 / 2) - (TempImage->imageHeight / 2)) + 15;

  while (1)
    {
      GetUserInput ();		// Get Control Input
      DrawFullscreenWindow ("Image viewer");	// Draw Window with Title "Image Viewer"
      PutGFX (0, 0, TempImage->imageWidth, TempImage->imageHeight, TempImage, tx, ty);	// Place Image Center of Screen/Window

      /*
         If the Image is not a JPEG and is the Maximum Screen Width and Height then
         Allow the User to set the Image as the Wallpaper
         Upon Selecting the Button
       */
      if (TempImage->imageWidth == 480 && TempImage->imageHeight == 272
	  && ftb != 1 & jpg != 1)
	{
	  if (cursorPosition.x > 380 && cursorPosition.x < (380 + 75)
	      && cursorPosition.y > 240 && cursorPosition.y < (240 + 20))
	    {
	      PutGFX (0, 0, 75, 20, Button2, 380, 240);
	    }
	  else
	    {
	      PutGFX (0, 0, 75, 20, Button1, 380, 240);
	    }
	  PutTextFont (400, 245, "Use", 0x00000000);
	}

      // Move the Image One Pixel Up
      if (pad.Buttons & PSP_CTRL_UP)
	{
	  ty--;
	}
      // Move the Image One Pixel Down
      if (pad.Buttons & PSP_CTRL_DOWN)
	{
	  ty++;
	}
      // Move the Image One Pixel Left
      if (pad.Buttons & PSP_CTRL_LEFT)
	{
	  tx--;
	}
      // Move the Image One Pixel Right
      if (pad.Buttons & PSP_CTRL_RIGHT)
	{
	  tx++;
	}

      // Close and Return
      if (pad.Buttons & PSP_CTRL_CONFIRM && cursorPosition.x > 465
	  && cursorPosition.x < 475 && cursorPosition.y > 3
	  && cursorPosition.y < 13)
	{
	  break;
	}

      //Use as wallpaper
      if (TempImage->imageWidth == 480 && TempImage->imageHeight == 272
	  && ftb != 1 && jpg != 1)
	{
	  if (pad.Buttons & PSP_CTRL_CONFIRM && cursorPosition.x > 380
	      && cursorPosition.x < (380 + 75) && cursorPosition.y > 240
	      && cursorPosition.y < (240 + 20))
	    {
	      SetWallpaper (filename);
	      PauseVbl (10);
	      break;
	    }
	}
      PutGFX (0, 0, 32, 32, cursor, cursorPosition.x, cursorPosition.y);
      PrintScreen ();
    }
  // Release the Image from Memory
  freeImage (TempImage);
}

// Load/Run the UMD
void
UMD_Run ()
{
  char tmp2[1000];
  char tmp3[1000];

  // Disable Debugger Handling
  pspDebugInstallKprintfHandler (NULL);
  pspDebugInstallErrorHandler (NULL);

  // Prepare the System Settings
  scePowerSetClockFrequency (222, 222, 111);
  pspAudioEnd ();

  // Prepare the Execution Parameters
  sprintf (tmp3, "%s;%s;%s\0", "ms0:/PSP-OSS/SYSTEM/UMD_LOADER.prx",
	   "disc0:/PSP_GAME/SYSDIR/EBOOT.BIN", ebootpath);
  sprintf (tmp2, "%s", "ms0:/PSP-OSS/SYSTEM/BOOTLOADER.elf");

  struct SceKernelLoadExecParam execParam;
  u32 total_length = strlen (tmp3) + 1;	// The Total Length of the Parameters + 1
  execParam.args = total_length;
  execParam.argp = (const char *) tmp3;
  execParam.key = NULL;
  execParam.size = sizeof (execParam) + total_length;
  sceKernelLoadExec (tmp2, &execParam);	// Load
}

/*
Run .ELF PSP Executable
Code from: http://forums.ps2dev.org/viewtopic.php?t=3792&highlight=scekernelloadexec&sid=185b1619ceec7bb02500576e0177cb77
*/
void
ELF_Run (const char *filename)
{
	Write_config("ms0:/PSP-OSS/SYSTEM/CONFIG/CALLBACK.cfg", "1");
  char tmp2[1000];
  char tmp3[1000];

  // Disable Debugger Handling
  pspDebugInstallKprintfHandler (NULL);
  pspDebugInstallErrorHandler (NULL);

  // Prepare the System Settings
  scePowerSetClockFrequency (222, 222, 111);
  pspAudioEnd ();

  // Prepare the Execution Parameters
  sprintf (tmp3, "%s;%s;%s\0", "ms0:/PSP-OSS/SYSTEM/ELF_LOADER.prx", filename,
	   ebootpath);
  sprintf (tmp2, "%s", "ms0:/PSP-OSS/SYSTEM/BOOTLOADER.elf");

  struct SceKernelLoadExecParam execParam;
  u32 total_length = strlen (tmp3) + 1;	// The Total Length of the Parameters + 1
  execParam.args = total_length;
  execParam.argp = (const char *) tmp3;
  execParam.key = NULL;
  execParam.size = sizeof (execParam) + total_length;
  sceKernelLoadExec (tmp2, &execParam);	// Load
}


// Run LUA
void
LUA_Run (const char *filename)
{
  
     Write_config("ms0:/PSP-OSS/SYSTEM/CONFIG/LUA_TEMP.CFG",filename);

     FadeScreenMessage("Loading LUA","PSP-OSS is loading LUA","Please wait...","");
     PrintScreen();
     PauseVbl(10); // Pause

     ELF_Run("ms0:/PSP-OSS/SYSTEM/LUA.elf"); // Load the LUA Launcher
   
}

// Run Shorcut
void
Shortcut_Run (const char *filename)
{
  SceUID file;
  char Temp_Shortcut[255];

  file = sceIoOpen (filename, PSP_O_RDONLY, 0);	// Open the File
  sceIoRead (file, Temp_Shortcut, 255);	// Read 255 Bytes from the File
  int filesize = sceIoLseek (file, 0, SEEK_END);	// Determine the File's Size
  sceIoClose (file);
  Temp_Shortcut[filesize] = 0x00;	// Insert a Terminator Null at the End of the File (Cuts the String to the True Width)

  PauseVbl (10);		// Pause

  OpenFile (Temp_Shortcut);	// Open the Short Cut
}

//Api Stuff
//Write a txt file
void
WriteTxtFile (const char *filename, const char *texttowrite)
{
  SceUID file;
  file = sceIoOpen (filename,PSP_O_WRONLY | PSP_O_CREAT | PSP_O_TRUNC, 0777);
  sceIoWrite (file, texttowrite, strlen (texttowrite));
  sceIoClose (file);
}

//Random Number
int
Random (int low, int high)
{
  return (rand () % (high + 1));
}
