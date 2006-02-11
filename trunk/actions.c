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
	  FadeScreenMessage (UMDLoadT, UMDLoad2T, WaitT, "");
	  PrintScreen ();
	  UMD_Run ();
	}
      else
	{
	  MessageWindow (NoUMDT, NoUMD2T);
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
	
	char            *data_ptr;
	unsigned long   data_size;
	FILE * fp;	   
	SceUID file;
	int filesize;

	sprintf (skinpath, "ms0:/PSP-OSS/SKINS/%s", NewSkin);
	fp = fopen(skinpath, "rb");
	urarlib_get(&data_ptr, &data_size, "version.cfg", fp, NULL); 	
	fclose(fp);
	fp = fopen("ms0:/PSP-OSS/SYSTEM/CONFIG/versionc.cfg", "wb");
	fwrite(data_ptr, 1, data_size, fp);
	fclose(fp);
	
	char version[20];
	file = sceIoOpen ("ms0:/PSP-OSS/SYSTEM/CONFIG/versionc.cfg", PSP_O_RDONLY, 0);
  sceIoRead (file, version, 20);
  filesize = sceIoLseek (file, 0, SEEK_END);
  sceIoClose (file);
  version[filesize] = 0x00;						
  
  if (strcmp (version, "PSP-OSS_03") == 0)
  {	  															  	
		  SceUID file;
		  file =
		    sceIoOpen ("ms0:/PSP-OSS/SYSTEM/SKIN.cfg",
			       PSP_O_WRONLY | PSP_O_CREAT | PSP_O_TRUNC, 0777);
		  sceIoWrite (file, NewSkin, strlen (NewSkin));
		  sceIoClose (file);
		  ReloadSkin ();													
  }	
  else
  {
 				 MessageWindow ("Skin Error", "Skin is not supported in PSP-OSS_0.3");
	}
}

void
ReloadSkin ()
{
  FadeScreenMessage (ReloadSkinT, ReloadSkin2T, WaitT, "");
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

  sprintf (buffer, "ms0:/PSP-OSS/SKINS/%s", skin);
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
 	textcolour ();

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
      DrawFullscreenWindow (FSImageT);	// Draw Window with Title "Image Viewer"
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
	  PutTextFont (400, 245, FSImageUseT, FSImageUseC);
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
		if (fbimager == 1)
		{
			fbimager = 0;
			BrowseDirectory (imageDic);
		}
		else
		{
	  break;
		}	
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
  Write_config ("ms0:/PSP-OSS/SYSTEM/CONFIG/CALLBACK.cfg", "1");
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

  Write_config ("ms0:/PSP-OSS/SYSTEM/CONFIG/LUA_TEMP.CFG", filename);

  FadeScreenMessage (LUALoadT, LUALoad2T, WaitT, "");
  PrintScreen ();
  PauseVbl (10);		// Pause

  ELF_Run ("ms0:/PSP-OSS/SYSTEM/LUA.elf");	// Load the LUA Launcher

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
 	char *suffix = strrchr (Temp_Shortcut, '/');
 	
				  if (stricmp (suffix, "/") == 0)
				    {
				      BrowseDirectory (Temp_Shortcut);
				    }
				    else
				    { 
							//should check to see if the shortcut exitsts				
					      FILE *File = NULL;
					      File = fopen (Temp_Shortcut, "r");	// Check To See If The File Exists         
					      fclose (File);
			
					      if (File)	// Does The File Exist?
								{
									  OpenFile (Temp_Shortcut);	// Open the Short Cut
								}
						}
	




}

void
PMP_Run (const char *filename)
{

  struct SceKernelLoadExecParam execParam;
  const u32 total_length = (strlen (filename) + 1);

  execParam.args = total_length;
  execParam.argp = (const char *) filename;
  execParam.key = NULL;
  execParam.size = sizeof (execParam) + total_length;

  pspAudioEnd ();
  sceKernelLoadExec (filename, &execParam);
}

//Api Stuff
//Write a txt file
void
WriteTxtFile (const char *filename, const char *texttowrite)
{
  SceUID file;
  file = sceIoOpen (filename, PSP_O_WRONLY | PSP_O_CREAT | PSP_O_TRUNC, 0777);
  sceIoWrite (file, texttowrite, strlen (texttowrite));
  sceIoClose (file);
}

//Random Number
int
Random (int low, int high)
{
  return (rand () % (high + 1));
}
