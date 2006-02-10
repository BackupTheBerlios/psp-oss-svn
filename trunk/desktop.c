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

#include "main.h"
#include "desktop.h"
#include "functions.h"

void
DoActiveDesktop ()
{

  //Set the wallpaper and taskbar :)
  PutGFX (0, 0, 480, 272, wallpaper, 0, 0);	//Wallpaper

  if (DesktopActive == 1)
    {
      DoDesktopEffects ();	//Desktop effect
    }

  PutGFX (0, 0, 480, 15, taskbar, 0, 257);	//Taskbar
  PutGFX (0, 0, 480, 15, TopBar, 0, 0);	//Top Bar

  PutTextFont (5, 5, OSSVersion, OSSVersionC);	//Version

  //Draw the start menu
  DrawStartMenu ();

  //Draw the clock
  drawtime ();

  //Draw the desktop icons  
  drawIcons ();

  //USB
  DrawUSBState ();

  //Get battery information and display in the taskbar
  DrawBattery ();

  //Is the cursor over a icon?
  findIcon ();

  if (pad.Buttons & PSP_CTRL_START && pad.Buttons & PSP_CTRL_SELECT)
    {
      USB_Mode ();
    }

  if (pad.Buttons & PSP_CTRL_LTRIGGER && pad.Buttons & PSP_CTRL_RTRIGGER)
    {
      Screenshot ("ms0:/Screenshot.png", getVramDisplayBuffer (),
		  SCREEN_WIDTH, SCREEN_HEIGHT, PSP_LINE_SIZE, 0);
    }
  if (pad.Buttons & PSP_CTRL_HOME)
    {
      ShutDown_Prompt ();
    }

  DrawMediaStatus ();
  DoDesktopIcons ();

}

void
DoDesktopEffects ()
{
  if (DesktopEffect == "None")
    {
      //Do nothing?
    }

  else if (DesktopEffect == "Lines")
    {
      char *startX[100];
      char *startY[100];

      //allocate 30 x positions
      int a = 0;
      while (a != 30)
	{
	  startX[a] = Random (0, 480);
	  a++;
	}

      //allocate 30 y positions             
      int b = 0;
      while (b != 30)
	{
	  startY[b] = Random (0, 242);
	  startY[b] += 15;
	  b++;
	}

      //Draw lines
      int c = 1;
      while (c != 30)
	{
	  int templine = 0;
	  while (templine < 20)
	    {
	      PutPixel ((startX[c] + templine), startY[c], WHITE);
	      templine++;
	    }
	  c++;
	}
    }
}

//Is USB activated?
void
DrawUSBState ()
{
  PutGFX (0, 0, 16, 9, USB_Icon, 417, 3);	//Display USB icon on the taskbar

  if (cursorPosition.x > 417 && cursorPosition.x < 433
      && cursorPosition.y < 12)
    {
      PutTextFont (380, 260, USBT, USBC);
    }
}

//Battery status
void
DrawBattery ()
{

  if (scePowerGetBatteryLifePercent () > 65
      && scePowerGetBatteryLifePercent () > 35)
    {
      PutGFX (0, 0, 23, 11, Battery_full, 385, 1);
    }

  else if (scePowerGetBatteryLifePercent () > 35
	   && scePowerGetBatteryLifePercent () <= 65)
    {
      PutGFX (0, 0, 23, 11, Battery_half, 385, 1);
    }

  else if (scePowerGetBatteryLifePercent () <= 35)
    {
      PutGFX (0, 0, 23, 11, Battery_low, 385, 1);
    }

  else if (scePowerIsPowerOnline ())
    {
      PutGFX (0, 0, 23, 11, Battery_charging, 385, 1);
    }

  else if (scePowerIsLowBattery ())
    {
      PutGFX (0, 0, 23, 11, Battery_empty, 385, 1);
    }

  if (cursorPosition.x > 385 && cursorPosition.x < 408 && cursorPosition.y > 1
      && cursorPosition.y < 12)
    {
      long BatteryVolt = scePowerGetBatteryVolt ();	// Voltage: 5000 = 5.000 Volts    
      long BatteryCharging = scePowerIsBatteryCharging ();	//                 
      int BatteryLifePercent = scePowerGetBatteryLifePercent ();	//   
      int BatteryLifeTime = scePowerGetBatteryLifeTime ();	// Estimated number of minutes the battery will last        

      char message[256];
      char BatteryVolt_ret_text[16];
      char BatteryCharge_percent[16];

      if (BatteryLifePercent < 100)
	{
	  sprintf (BatteryCharge_percent, "%d%%", BatteryLifePercent);
	}
      else
	{
	  strcpy (BatteryCharge_percent, "100%");
	}


      // Running on AC power...       
      if (BatteryLifePercent > 100)
	{
	  sprintf (message, UsingACT);
	}

      // Battery is being used...     
      else if (BatteryCharging == 0)
	{
	  if (BatteryLifeTime > 0 && BatteryLifeTime < 330 /* 5:30 */ )
	    {
	      sprintf (message, "%s %01d:%02d", BatteryCharge_percent,
		       BatteryLifeTime / 60, BatteryLifeTime % 60);
	    }
	  else
	    {
	      sprintf (message, "%s", BatteryCharge_percent);
	    }
	}

      // Battery is being charged...  
      else
	{
	  long BatteryTemp = scePowerGetBatteryTemp ();
	  // If the battery temp. is > 38C (100F), display the temp.      
	  if ((BatteryTemp > 38) && (BatteryTemp < 100))
	    {
	      sprintf (message, "AC: %s - %d° F", BatteryCharge_percent,
		       (int) ((9.0f / 5.0f) * (float) BatteryTemp) + 32);
	    }
	  else
	    {
	      sprintf (message, "AC: %s", BatteryCharge_percent);
	    }
	}
      PutTextFont (380, 260, message, BatteryC);	//Battery stuff       
    }
}

void
DrawStartMenu ()
{

  if (cursorPosition.x > 0 && cursorPosition.x < 60 && cursorPosition.y > 257
      && cursorPosition.y < 272)
    {
      PutGFX (0, 0, 70, 15, Start_menu_Over, 0, 257);	//Start Menu
    }
  else
    {
      PutGFX (0, 0, 70, 15, Start_menu, 0, 257);	//Start Menu
    }
}

//Thanks to Sonic1 for help with the clock :)
#define PSP_SYSTEMPARAM_ID_INT_TIMEZONE         6
void
drawtime ()
{
  char buff[150];
  struct tm *tsys;
  time_t cur_time;
  sceKernelLibcTime (&cur_time);
  tsys = localtime (&cur_time);
  sprintf (buff, "%02d%c%02d",
	   (tsys->tm_hour > 12 ? tsys->tm_hour - 12 : tsys->tm_hour),
	   (tsys->tm_sec & 1 ? ':' : ' '), tsys->tm_min);
  PutTextFont (440, 4, buff, TimeC);	//current Time

}

void
initTimezone ()
{
  int tzOffset = 0;
  sceUtilityGetSystemParamInt (PSP_SYSTEMPARAM_ID_INT_TIMEZONE, &tzOffset);
  int tzOffsetAbs = tzOffset < 0 ? -tzOffset : tzOffset;
  int hours = tzOffsetAbs / 60;
  int minutes = tzOffsetAbs - hours * 60;
  static char tz[10];
  sprintf (tz, "GMT%s%02i:%02i", tzOffset < 0 ? "+" : "-", hours, minutes);
  setenv ("TZ", tz, 1);
  tzset ();
}

void
DrawMediaStatus ()
{
  if (MediaStatus != "stop")
    {
     MP3_EndOfStream();

      PutGFX (0, 0, 135, 15, Audio_Player, 240, 0);	//257

      //Music is PLAYing
      if (MediaStatus == "play")
	{
	  if (cursorPosition.x > 315 && cursorPosition.x < (315 + 15)
	      && cursorPosition.y > 0 && cursorPosition.y < 15)
	    {
	      PutGFX (0, 0, 15, 15, Music_pause2, 315, 0);
	      if (DesktopActive == 1)
		{
		  PutTextFont (380, 260, PauseT, PauseC);	//Audio
		}
	    }
	  else
	    {
	      PutGFX (0, 0, 15, 15, Music_pause1, 315, 0);
	    }
	}

      //Music is PAUSED
      if (MediaStatus == "pause")
	{
	  if (cursorPosition.x > 315 && cursorPosition.x < (315 + 15)
	      && cursorPosition.y > 0 && cursorPosition.y < 15)
	    {
	      PutGFX (0, 0, 15, 15, Music_play2, 315, 0);
	      if (DesktopActive == 1)
		{
		  PutTextFont (380, 260, PlayT, PlayC);
		}
	    }
	  else
	    {
	      PutGFX (0, 0, 15, 15, Music_play1, 315, 0);
	    }
	}

      if (cursorPosition.x > 345 && cursorPosition.x < (345 + 15)
	  && cursorPosition.y > 0 && cursorPosition.y < 15)
	{
	  PutGFX (0, 0, 15, 15, Music_stop2, 345, 0);
	  if (DesktopActive == 1)
	    {
	      PutTextFont (380, 260, StopT, StopC);
	    }
	}
      else
	{
	  PutGFX (0, 0, 15, 15, Music_stop1, 345, 0);
	}

      if (pad.Buttons & PSP_CTRL_CONFIRM && cursorPosition.x > 315
	  && cursorPosition.x < (315 + 15) && cursorPosition.y > 0
	  && cursorPosition.y < 15)
	{
	  Audio_Pause ();
	  PauseVbl (1 * 60);
	}

      if (pad.Buttons & PSP_CTRL_CONFIRM && cursorPosition.x > 345
	  && cursorPosition.x < (345 + 15) && cursorPosition.y > 0
	  && cursorPosition.y < 15)
	{
	  Audio_Stop ();
	  PauseVbl (1 * 60);
	}
    }
}

void
DoDesktopIcons ()
{
  int IconPositionX = 1;
  int IconPositionY = 1;
  int i = 0;

  if (frtd == 1)
    {
      DesktopDirectory = sceIoDopen ("ms0:/PSP-OSS/DESKTOP/");

      //Remove the . and .. folders
      sceIoDread (DesktopDirectory, &dir);
      sceIoDread (DesktopDirectory, &dir);

      while (sceIoDread (DesktopDirectory, &dir) > 0)
	{
	  desktopiconname[i] = strdup (dir.d_name);

	  if (dir.d_stat.st_attr & FIO_SO_IFDIR)
	    {
	      desktopisdir[i] = 1;
	    }
	  else
	    {
	      desktopisdir[i] = 0;	      
			 suffix = strrchr (desktopiconname[i], '.');
		   if (suffix)		   
		    {
		      if (stricmp (suffix, ".qli") == 0)
					{
					  i--;
					}
				}
	    }
	    
	  i++;
	}

      //Close Dir Command
      frtd = 0;
      sceIoDclose (DesktopDirectory);
      numberoffilesondesktop = i;
    }

  else
    {
      while (numberoffilesondesktop > i)
	{

	  //Get file extension          
	  char deskitem[i][32];
	  char deskitemrs[i][32];
	  suffix = strrchr (desktopiconname[i], '.');
	  
	  if (desktopisdir[i] != 1 && suffix)
	    {
	      int size;
	      int size2;
	      size = strlen (desktopiconname[i]);
	      size2 = strlen (suffix);
	      strncpy (deskitemrs[i], desktopiconname[i], (size - size2));
	      deskitemrs[i][(size - size2)] = '\0';

	      if (size <= 10)
		{
		  strncpy (deskitem[i], deskitemrs[i], (size - size2));
		  deskitem[i][(size - size2)] = '\0';
		}
	      else
		{
		  strncpy (deskitem[i], deskitemrs[i], 6);
		  deskitem[i][6] = '\0';
		}
	    }
	  else
	    {
	      strncpy (deskitem[i], desktopiconname[i], 6);
	      deskitem[i][6] = '\0';
	    }
	  PutText ((60 * IconPositionX - 46), (60 * IconPositionY + 7),
		   deskitem[i], DesktopTextC);


	  if (desktopisdir[i] == 1)
	    {
	      if (iconSelected.row == IconPositionX
		  && iconSelected.col == IconPositionY)
		{
		  PutGFX (0, 0, 48, 48, Icon_Folder_Over,
			  (60 * IconPositionX - 48),
			  (60 * IconPositionY - 48 + 5));
		  PutTextFont (380, 260, DirectoryT, DirectoryC);
		  if (DesktopIconsActive == 1)
		    {
		      PutTextFont ((cursorPosition.x + 15), cursorPosition.y,
				   desktopiconname[i], DesktopTextOverC);
		    }
		}
	      else
		{
		  PutGFX (0, 0, 48, 48, Icon_Folder,
			  (60 * IconPositionX - 48),
			  (60 * IconPositionY - 48 + 5));
		}
	    }
	    
	  //No file extension so Unknown files
	  else if (!suffix)
	    {
	      if (iconSelected.row == IconPositionX
		  && iconSelected.col == IconPositionY)
		{
		  PutGFX (0, 0, 48, 48, Icon_Unknown_Over,
			  (60 * IconPositionX - 48),
			  (60 * IconPositionY - 48 + 5));
		  PutTextFont (380, 260, UnknownT, UnknownC);
		  if (DesktopIconsActive == 1)
		    {
		      PutTextFont ((cursorPosition.x + 15), cursorPosition.y,
				   desktopiconname[i], DesktopTextOverC);
		    }
		}
	      else
		{
		  PutGFX (0, 0, 48, 48, Icon_Unknown,
			  (60 * IconPositionX - 48),
			  (60 * IconPositionY - 48 + 5));
		}
	    }	    

	  //Images
	  else if (stricmp (suffix, ".png") == 0
		   || stricmp (suffix, ".jpg") == 0
		   || stricmp (suffix, ".jpeg") == 0
		   || stricmp (suffix, ".thm") == 0)
	    {
	      if (iconSelected.row == IconPositionX
		  && iconSelected.col == IconPositionY)
		{
		  PutGFX (0, 0, 48, 48, Icon_GFX_Over,
			  (60 * IconPositionX - 48),
			  (60 * IconPositionY - 48 + 5));
		  PutTextFont (380, 260, GraphicT, GraphicC);
		  if (DesktopIconsActive == 1)
		    {
		      PutTextFont ((cursorPosition.x + 15), cursorPosition.y,
				   desktopiconname[i], DesktopTextOverC);
		    }
		}
	      else
		{
		  PutGFX (0, 0, 48, 48, Icon_GFX, (60 * IconPositionX - 48),
			  (60 * IconPositionY - 48 + 5));
		}
	    }

	  //Audio
	  else if (stricmp (suffix, ".mp3") == 0
		   || stricmp (suffix, ".ogg") == 0)
	    {
	      if (iconSelected.row == IconPositionX
		  && iconSelected.col == IconPositionY)
		{
		  PutGFX (0, 0, 48, 48, Icon_Audio_Over,
			  (60 * IconPositionX - 48),
			  (60 * IconPositionY - 48 + 5));
		  PutTextFont (380, 260, MusicT, MusicC);
		  if (DesktopIconsActive == 1)
		    {
		      PutTextFont ((cursorPosition.x + 15), cursorPosition.y,
				   desktopiconname[i], DesktopTextOverC);
		    }
		}
	      else
		{
		  PutGFX (0, 0, 48, 48, Icon_Audio, (60 * IconPositionX - 48),
			  (60 * IconPositionY - 48 + 5));
		}
	    }

	  //Video      
	  else if (stricmp (suffix, ".pmp") == 0
		   || stricmp (suffix, ".pos") == 0)
	    {
	      if (iconSelected.row == IconPositionX
		  && iconSelected.col == IconPositionY)
		{
		  PutGFX (0, 0, 48, 48, Icon_Video_Over,
			  (60 * IconPositionX - 48),
			  (60 * IconPositionY - 48 + 5));
		  PutTextFont (380, 260, MusicT, MusicC);
		  if (DesktopIconsActive == 1)
		    {
		      PutTextFont ((cursorPosition.x + 15), cursorPosition.y,
				   desktopiconname[i], DesktopTextOverC);
		    }
		}
	      else
		{
		  PutGFX (0, 0, 48, 48, Icon_Video, (60 * IconPositionX - 48),
			  (60 * IconPositionY - 48 + 5));
		}
	    }

	  //Application/game
	  else if (stricmp (suffix, ".pbp") == 0
		   || stricmp (suffix, ".elf") == 0)
	    {
	      if (iconSelected.row == IconPositionX
		  && iconSelected.col == IconPositionY)
		{
		  PutGFX (0, 0, 48, 48, Icon_Eboot_Over,
			  (60 * IconPositionX - 48),
			  (60 * IconPositionY - 48 + 5));
		  PutTextFont (380, 260, ExecutableT, ExecutableC);
		  if (DesktopIconsActive == 1)
		    {
		      PutTextFont ((cursorPosition.x + 15), cursorPosition.y,
				   desktopiconname[i], DesktopTextOverC);
		    }
		}
	      else
		{
		  PutGFX (0, 0, 48, 48, Icon_Eboot, (60 * IconPositionX - 48),
			  (60 * IconPositionY - 48 + 5));
		}
	    }

	  //Lua Apps
	  else if (stricmp (suffix, ".lua") == 0)
	    {
	      if (iconSelected.row == IconPositionX
		  && iconSelected.col == IconPositionY)
		{
		  PutGFX (0, 0, 48, 48, Icon_Lua_Over,
			  (60 * IconPositionX - 48),
			  (60 * IconPositionY - 48 + 5));
		  PutTextFont (380, 260, ExecutableT, ExecutableC);
		  if (DesktopIconsActive == 1)
		    {
		      PutTextFont ((cursorPosition.x + 15), cursorPosition.y,
				   desktopiconname[i], DesktopTextOverC);
		    }
		}
	      else
		{
		  PutGFX (0, 0, 48, 48, Icon_Lua, (60 * IconPositionX - 48),
			  (60 * IconPositionY - 48 + 5));
		}
	    }

	  //QuickLink
	  else if (stricmp (suffix, ".ql") == 0
		   || stricmp (suffix, ".pol") == 0)
	    {
	      if (iconSelected.row == IconPositionX
		  && iconSelected.col == IconPositionY)
		{
		  if (qlcheck[i] == 1)
		    {
		      PutGFX (0, 0, 48, 48, ShortcutIcon[i],
			      (60 * IconPositionX - 48),
			      (60 * IconPositionY - 48 + 5));
		    }
		  else
		    {
		      PutGFX (0, 0, 48, 48, Icon_QuickLink_Over,
			      (60 * IconPositionX - 48),
			      (60 * IconPositionY - 48 + 5));
		    }
		  PutTextFont (380, 260, QuickLinkT, QuickLinkC);
		  if (DesktopIconsActive == 1)
		    {
		      PutTextFont ((cursorPosition.x + 15), cursorPosition.y,
				   desktopiconname[i], DesktopTextOverC);
		    }
		}
	      else
		{
		  if (qlcheck[i] == 0)
		    {
		      char qlpath[500];
		      FILE *File = NULL;
		      sprintf (qlpath, "ms0:/PSP-OSS/DESKTOP/%s.qli",
			       deskitemrs[i]);
		      File = fopen (qlpath, "r");	// Check To See If The File Exists         
		      fclose (File);

		      if (File)	// Does The File Exist?
			{
			  ShortcutIcon[i] = LoadGFX (qlpath);
			  qlcheck[i] = 1;
			}
		    }

		  if (qlcheck[i] == 1)
		    {
		      PutGFX (0, 0, 48, 48, ShortcutIcon[i],
			      (60 * IconPositionX - 48),
			      (60 * IconPositionY - 48 + 5));
		    }
		  else
		    {
		      PutGFX (0, 0, 48, 48, Icon_QuickLink,
			      (60 * IconPositionX - 48),
			      (60 * IconPositionY - 48 + 5));
		    }
		}
	    }

	  //Unknown files
	  else
	    {
	      if (iconSelected.row == IconPositionX
		  && iconSelected.col == IconPositionY)
		{
		  PutGFX (0, 0, 48, 48, Icon_Unknown_Over,
			  (60 * IconPositionX - 48),
			  (60 * IconPositionY - 48 + 5));
		  PutTextFont (380, 260, UnknownT, UnknownC);
		  if (DesktopIconsActive == 1)
		    {
		      PutTextFont ((cursorPosition.x + 15), cursorPosition.y,
				   desktopiconname[i], DesktopTextOverC);
		    }
		}
	      else
		{
		  PutGFX (0, 0, 48, 48, Icon_Unknown,
			  (60 * IconPositionX - 48),
			  (60 * IconPositionY - 48 + 5));
		}
	    }


	  if (DesktopIconsActive == 1)
	    {
	      if (pad.Buttons & PSP_CTRL_CONFIRM
		  && iconSelected.row == IconPositionX
		  && iconSelected.col == IconPositionY)
		{
		  char buffer[200];

		  if (desktopisdir[i] == 1)
		    {
		      sprintf (buffer, "ms0:/PSP-OSS/DESKTOP/%s/",
			       desktopiconname[i]);
		      BrowseDirectory (buffer);
		      break;
		    }

		  else
		    {
		      sprintf (buffer, "ms0:/PSP-OSS/DESKTOP/%s",
			       desktopiconname[i]);
		      OpenFile (buffer);
		    }
		}

	      if (pad.Buttons & PSP_CTRL_BACK
		  && iconSelected.row == IconPositionX
		  && iconSelected.col == IconPositionY)
		{
		  if (desktopisdir[i] != 1)
		    {
		      RightClick_Icon_Desktop (cursorPosition.x,
					       cursorPosition.y,
					       "ms0:/PSP-OSS/DESKTOP/",
					       desktopiconname[i]);
		    }
		}
	    }
	  else
	    {
	    }
	  //+ everything that needs to be +'ed =D
	  if (IconPositionY > 3)
	    {
	      IconPositionX += 1;
	      IconPositionY = 1;
	    }
	  else
	    {
	      IconPositionY += 1;
	    }

	  i++;
	}
    }

}
void
drawIcons ()
{

  //Exit Desktop Icon
  if (iconSelected.row == 8 && iconSelected.col == 4)
    {				//Cursor is over the exit icon
      PutTextFont (380, 260, ExitOSST, ExitOSSC);
      PutGFX (0, 0, 48, 48, Icon_Quit_Over, (IconXSize * 8 - 48),
	      (IconYSize * 4 - 48));
    }
  else
    {
      PutGFX (0, 0, 48, 48, Icon_Quit, (IconXSize * 8 - 48),
	      (IconYSize * 4 - 48));
    }

  //UMD Icon
  int UMD = sceUmdCheckMedium (0);
  if (!UMD == 0)
    {
      if (iconSelected.row == 8 && iconSelected.col == 3)
	{			//Cursor is over the UMD icon
	  PutTextFont (380, 260, StartUMDT, StartUMDC);
	  PutGFX (0, 0, 48, 48, Icon_UMD_Over, (IconXSize * 8 - 48),
		  (IconYSize * 3 - 48));
	}
      else
	{
	  PutGFX (0, 0, 48, 48, Icon_UMD, (IconXSize * 8 - 48),
		  (IconYSize * 3 - 48));
	}
    }

  //No UMD Icon
  if (UMD == 0)
    {
      if (iconSelected.row == 8 && iconSelected.col == 3)
	{			//Cursor is over the No UMD icon
	  PutTextFont (380, 260, NoUMDT, NoUMDC);
	  PutGFX (0, 0, 48, 48, Icon_No_UMD_Over, (IconXSize * 8 - 48),
		  (IconYSize * 3 - 48));
	}
      else
	{
	  PutGFX (0, 0, 48, 48, Icon_No_UMD, (IconXSize * 8 - 48),
		  (IconYSize * 3 - 48));
	}
    }

  //Settings Icon
  if (iconSelected.row == 8 && iconSelected.col == 2)
    {
      PutTextFont (380, 260, SettingsT, SettingsC);
      PutGFX (0, 0, 48, 48, Icon_Settings_Over, (IconXSize * 8 - 48),
	      (IconYSize * 2 - 48));
    }
  else
    {
      PutGFX (0, 0, 48, 48, Icon_Settings, (IconXSize * 8 - 48),
	      (IconYSize * 2 - 48));
    }
}
