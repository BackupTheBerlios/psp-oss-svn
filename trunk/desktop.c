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
typedef struct
{
  signed int x;
  signed int y;
  signed int v;
  signed int vx;
} fstruct;
fstruct fountain[5000];
int finited = 0;
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
  PutTextFont (5, 5, OSSVersion, DARK_RED);	//Version

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
  
  if (pad.Buttons & PSP_CTRL_START && pad.Buttons & PSP_CTRL_LTRIGGER)
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
initf ()
{
  int a = 0;
  for (a = 0; a <= 5000; a++)
    {
      fountain[a].x = 340 - (Random (0, 200));
      fountain[a].y = 272;
      fountain[a].v = Random (0, 80) + 150;
      fountain[a].vx = 20 - Random (0, 40);
    }
  finited = 1;
}

void
DoDesktopEffects ()
{
  if (DesktopEffect == "Snow")
    {

      int TempY;
      int TempX;

      TempX = -40;
      while (480 > TempX)
	{
	  TempY = 0;
	  while (272 > TempY)
	    {
	      PutGFX (0, 0, 15, 15, Effect_GFX1,
		      (Effect_Snow_PositionX + TempX),
		      (Effect_Snow_PositionY + TempY));
	      TempY += 40;
	    }
	  TempX += 40;
	}

      if (Effect_Snow_PositionX > 40)
	{
	  Effect_Snow_PositionX = 0;
	}
      else if (Effect_Snow_PositionX < -40)
	{
	  Effect_Snow_PositionX = 0;
	}
      else
	{
	  //Effect_Snow_PositionX+=1;
	  Effect_Snow_PositionX += Random (0, 3);
	  Effect_Snow_PositionX -= 1;
	}

      if (Effect_Snow_PositionY == 40)
	{
	  Effect_Snow_PositionY = 0;
	}
      else
	{
	  Effect_Snow_PositionY += 1;
	}

    }
  else if (DesktopEffect == "Fountain")
    {
      if (finited == 0)
	{
	  initf ();
	}
      //Move particles//
      int a = 0;
      for (a = 0; a <= 5000; a++)
	{
	  fountain[a].y -= fountain[a].v;
	  fountain[a].v -= 9.81;
	  fountain[a].x += fountain[a].vx;
	  if (fountain[a].y > 480)
	    {
	      fountain[a].x = 380 - Random (0, 200);
	      fountain[a].y = 272;
	      fountain[a].v = Random (0, 80) + 150;
	      fountain[a].vx = 20 - Random (0, 40);
	    }
	  //Draw Particles//
	  for (a = 0; a <= 5000; a++)
	    {
	      //PutPixel(fountain[a].x,fountain[a].y,RGB(200+Random(0,30),200+Random(0,30),255));
	      PutPixel (1, 2,
			RGB (200 + Random (0, 30), 200 + Random (0, 30),
			     255));
	    }
	  //End of Draw Particles//
	}
    }
  else if (DesktopEffect == "Starfield")
    {
      char *startX[100];
      char *startY[100];

      //allocate 30 x positions
      int a = 0;
      while (a != 100)
	{
	  startX[a] = Random (0, 480);
	  a++;
	}

      //allocate 30 y positions             
      int b = 0;
      while (b != 100)
	{
	  startY[b] = Random (0, 272);
	  b++;
	}

      //place 10 WHITE stars
      int c = 1;
      while (c != 100)
	{
	  PutPixel (startX[c], startY[c], WHITE);
	  c++;
	}
      c = 1;
      while (c <= 10)
	{
	  PutPixel (startX[c], startY[c], BLUE);
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
      PutTextFont (380, 260, "USB", BLACK);
    }
}

//Battery status
void
DrawBattery ()
{

  if (scePowerGetBatteryLifePercent () > 65)
    {
      PutGFX (0, 0, 23, 11, Battery_full, 385, 1);
    }

  else if (scePowerGetBatteryLifePercent () > 35)
    {
      PutGFX (0, 0, 23, 11, Battery_half, 385, 1);
    }

  else if (scePowerGetBatteryLifePercent () < 35)
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
      int powlev = scePowerGetBatteryLifePercent ();
      //PutTextFont(380,260,powlev,BLACK);
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
  PutTextFont (440, 4, buff, DARK_RED);

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
		  PutTextFont (380, 260, "Pause", 0x00000000);
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
		  PutTextFont (380, 260, "Play", 0x00000000);
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
	      PutTextFont (380, 260, "Stop", 0x00000000);
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

	  char *suffix1 = strrchr (desktopiconname[i], '.qli');

	  if (suffix1)
	    {
	      i--;
	    }	  
	    
	  char *suffix2 = strrchr (desktopiconname[i], '.QLI');

	  if (suffix2)
	    {
	      i--;
	    }	  	    
		
	  if (dir.d_stat.st_attr & FIO_SO_IFDIR)
	    {
	      desktopisdir[i] = 1;
	    }
	  else
	    {
	      desktopisdir[i] = 0;
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
           //Get file extension
           int size;
           int size2;
           char* suffix = strrchr(desktopiconname[i], '.');   
           char deskitem[i][10];
           char deskitemrs[i][30];
           size = strlen (desktopiconname[i]);
           size2 = strlen (suffix);           
           strncpy (deskitemrs[i],desktopiconname[i],(size-size2));
           deskitemrs[i][(size-size2)]='\0';
           
           if (size <=10)
           {
           	strncpy (deskitem[i],deskitemrs[i],(size-size2));
           	deskitem[i][(size-size2)]='\0';
           }
           else
           {
            strncpy (deskitem[i],deskitemrs[i],6);
            deskitem[i][6]='\0';
           }           
           PutText((60*IconPositionX-46),(60*IconPositionY+7),deskitem[i],BLACK); 


	  if (desktopisdir[i] == 1)
	    {
	      if (iconSelected.row == IconPositionX
		  && iconSelected.col == IconPositionY)
		{
		  PutGFX (0, 0, 48, 48, Icon_Folder_Over,
			  (60 * IconPositionX - 48),
			  (60 * IconPositionY - 48 + 5));
		  PutTextFont (380, 260, "Directory", BLACK);
				if (DesktopIconsActive==1)
					{
		  		 PutTextFont ((cursorPosition.x + 15), cursorPosition.y,
			       desktopiconname[i], BLUE);
					}
		}
	      else
		{
		  PutGFX (0, 0, 48, 48, Icon_Folder,
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
		  PutTextFont (380, 260, "Graphics", BLACK);
				if (DesktopIconsActive==1)
					{		  
		  			PutTextFont ((cursorPosition.x + 15), cursorPosition.y,
			       desktopiconname[i], BLUE);
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
		  PutTextFont (380, 260, "Music", BLACK);
				if (DesktopIconsActive==1)
					{		  
		  			PutTextFont ((cursorPosition.x + 15), cursorPosition.y,
			       desktopiconname[i], BLUE);
			     }
		}
	      else
		{
		  PutGFX (0, 0, 48, 48, Icon_Audio, (60 * IconPositionX - 48),
			  (60 * IconPositionY - 48 + 5));
		}
	    }

	  //Application/game
	  else if (stricmp (suffix, ".pbp") == 0
		   || stricmp (suffix, ".elf") == 0
		   || stricmp (suffix, ".lua") == 0)
	    {
	      if (iconSelected.row == IconPositionX
		  && iconSelected.col == IconPositionY)
		{
		  PutGFX (0, 0, 48, 48, Icon_Eboot_Over,
			  (60 * IconPositionX - 48),
			  (60 * IconPositionY - 48 + 5));
		  PutTextFont (380, 260, "Executable", BLACK);
				if (DesktopIconsActive==1)
					{		  
		  			PutTextFont ((cursorPosition.x + 15), cursorPosition.y,
			       desktopiconname[i], BLUE);
			     }
		}
	      else
		{
		  PutGFX (0, 0, 48, 48, Icon_Eboot, (60 * IconPositionX - 48),
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
		  	PutTextFont (380, 260, "QuickLink", BLACK);
				if (DesktopIconsActive==1)
					{		  	
		  			PutTextFont ((cursorPosition.x + 15), cursorPosition.y,
			       desktopiconname[i], BLUE);
			    }
		}
	      else
		{		  
				if (qlcheck[i] == 0)
				{
					 char qlpath[500];
					 FILE *File=NULL;
					 sprintf (qlpath, "ms0:/PSP-OSS/DESKTOP/%s.qli", deskitemrs[i]);
			  	 File=fopen(qlpath,"r");                     // Check To See If The File Exists		
					 fclose(File); 			  	 		
			   
			   if (File)                                 // Does The File Exist?
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
		  PutTextFont (380, 260, "Unknown", BLACK);
				if (DesktopIconsActive==1)
					{		  
		  			PutTextFont ((cursorPosition.x + 15), cursorPosition.y,
			       desktopiconname[i], BLUE);
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
				if (DesktopIconsActive==1)
					{		  		    	
		      sprintf (buffer, "ms0:/PSP-OSS/DESKTOP/%s/",
			       desktopiconname[i]);
		      BrowseDirectory (buffer);
		      break;
		      }
		    }

		  else
		    {
				if (DesktopIconsActive==1)
					{		  		    	
		      sprintf (buffer, "ms0:/PSP-OSS/DESKTOP/%s",
			       desktopiconname[i]);
		      OpenFile (buffer);
		      }
		    }
		}

	      if (pad.Buttons & PSP_CTRL_BACK
		  && iconSelected.row == IconPositionX
		  && iconSelected.col == IconPositionY)
		{
		  if (desktopisdir[i] != 1)
		    {
				if (DesktopIconsActive==1)
					{		  		    	
		      RightClick_Icon_Desktop (cursorPosition.x,
					       cursorPosition.y,
					       "ms0:/PSP-OSS/DESKTOP/",
					       desktopiconname[i]);
					}
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
      PutTextFont (380, 260, "Exit OSS", 0x00000000);
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
	  PutTextFont (380, 260, "Start UMD", 0x00000000);
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
	  PutTextFont (380, 260, "No UMD", 0x00000000);
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
      PutTextFont (380, 260, "Settings", 0x00000000);
      PutGFX (0, 0, 48, 48, Icon_Settings_Over, (IconXSize * 8 - 48),
	      (IconYSize * 2 - 48));
    }
  else
    {
      PutGFX (0, 0, 48, 48, Icon_Settings, (IconXSize * 8 - 48),
	      (IconYSize * 2 - 48));
    }
}
