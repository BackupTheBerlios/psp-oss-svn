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
#include "settings.h"
int windowx = 100;
int windowy = 50;
int itemx = 120;
int optionx = 140;

void
SettingsScreen ()
{
  //We got a window open, so desktop shouldn't be active.
  DesktopActive = 0;

  checkkey = 1;

  while (1)
    {
      GetUserInput ();
      DrawSettingsScreenGUI ();

      //Change langage
      if (pad.Buttons & PSP_CTRL_CONFIRM && cursorPosition.x > optionx + 150
	  && cursorPosition.x < optionx + 250
	  && cursorPosition.y > windowy + 15
	  && cursorPosition.y < windowy + 30)
	{
		//SettingsScreen_Language ();
	  Toggle_Lang ("NEXT");
	  textlang ();
 		checkkey = 1;
	  
	}

      //Change CPU Speed
      if (pad.Buttons & PSP_CTRL_CONFIRM && cursorPosition.x > optionx + 150
	  && cursorPosition.x < optionx + 250
	  && cursorPosition.y > windowy + 30
	  && cursorPosition.y < windowy + 45)
	{
	  //Get current CPU speed
	  sprintf (CPU_Speed, "%d", scePowerGetCpuClockFrequency ());

	  SceUID file;
	  file =
	    sceIoOpen ("ms0:/PSP-OSS/SYSTEM/CONFIG/CPU.cfg",
		       PSP_O_WRONLY | PSP_O_CREAT | PSP_O_TRUNC, 0777);

	  //If its at 333mHz, set it to 222mHz.
	  if (strcmp (CPU_Speed, "333") == 0)
	    {
	      sceIoWrite (file, "222", 3);

	      scePowerSetClockFrequency (222, 222, 111);
	    }

	  //If its at 222mHz, set it to 266mHz.
	  else if (strcmp (CPU_Speed, "222") == 0)
	    {
	      sceIoWrite (file, "266", 3);

	      scePowerSetClockFrequency (266, 266, 133);
	    }
	  //If its at 266mHz, set it to 333mHz.
	  else if (strcmp (CPU_Speed, "265") == 0
		   || strcmp (CPU_Speed, "266") == 0)
	    {
	      sceIoWrite (file, "333", 3);

	      scePowerSetClockFrequency (333, 333, 166);
	    }


	  PauseVbl (30);
	  sceIoClose (file);
	  checkkey = 1;
	}

      //Change confirm key
      if (pad.Buttons & PSP_CTRL_CONFIRM && cursorPosition.x > optionx + 150
	  && cursorPosition.x < optionx + 250
	  && cursorPosition.y > windowy + 45
	  && cursorPosition.y < windowy + 60)
	{

	  if (currentkey == "Cross")
	    {
	      Write_config ("ms0:/PSP-OSS/SYSTEM/CONFIG/KEYS.cfg", "JP");

	      PSP_CTRL_CONFIRM = 0x002000;	//CIRCLE
	      PSP_CTRL_BACK = 0x004000;	//CROSS

	      currentkey = "Circle";
	    }
	  else if (currentkey == "Circle")
	    {
	      Write_config ("ms0:/PSP-OSS/SYSTEM/CONFIG/KEYS.cfg", "EN");

	      PSP_CTRL_CONFIRM = 0x004000;	//CROSS
	      PSP_CTRL_BACK = 0x002000;	//CIRCLE

	      currentkey = "Cross";
	    }
	  PauseVbl (30);
	}

      //Toggle wallpapers
      if (pad.Buttons & PSP_CTRL_CONFIRM && cursorPosition.x > optionx + 150
	  && cursorPosition.x < optionx + 250
	  && cursorPosition.y > windowy + 75
	  && cursorPosition.y < windowy + 90)
	{
	  if (toggle_wallpapers == "LRT")
	    {
	      //Make it select
	      Write_config
		("ms0:/PSP-OSS/SYSTEM/CONFIG/TOGGLE_WALLPAPERS.cfg", "SEL");
	      toggle_wallpapers = "SEL";
	    }

	  else if (toggle_wallpapers == "SEL")
	    {
	      //turn off
	      Write_config
		("ms0:/PSP-OSS/SYSTEM/CONFIG/TOGGLE_WALLPAPERS.cfg", "OFF");
	      toggle_wallpapers = "OFF";
	    }

	  else if (toggle_wallpapers == "OFF")
	    {
	      //Make it LR-Trigger
	      Write_config
		("ms0:/PSP-OSS/SYSTEM/CONFIG/TOGGLE_WALLPAPERS.cfg", "LRT");
	      toggle_wallpapers = "LRT";
	    }

	  checkkey = 1;
	}
      //Toggle MP3
      if (pad.Buttons & PSP_CTRL_CONFIRM && cursorPosition.x > optionx + 150
	  && cursorPosition.x < optionx + 250
	  && cursorPosition.y > windowy + 60
	  && cursorPosition.y < windowy + 75)
	{
 if (toggle_MP3 == "LRT")
	    {
	      //Make it select
	      Write_config ("ms0:/PSP-OSS/SYSTEM/CONFIG/TOGGLE_MP3.cfg", "STA");
	      toggle_MP3 = "STA";
	    }

	  else if (toggle_MP3 == "STA")
	    {
	      //turn off
	      Write_config("ms0:/PSP-OSS/SYSTEM/CONFIG/TOGGLE_MP3.cfg", "OFF");
	      toggle_MP3 = "OFF";
	    }

	  else if (toggle_MP3 == "OFF")
	    {
	      //Make it LR-Trigger
	      Write_config("ms0:/PSP-OSS/SYSTEM/CONFIG/TOGGLE_MP3.cfg", "LRT");
	      toggle_MP3 = "LRT";
	    }

	  checkkey = 1;
	}

      //Desktop effect
      if (pad.Buttons & PSP_CTRL_CONFIRM && cursorPosition.x > optionx + 150
	  && cursorPosition.x < optionx + 250
	  && cursorPosition.y > windowy + 90
	  && cursorPosition.y < windowy + 105)
	{
	  if (DesktopEffect == "None")
	    {
	      //Lines
	      Write_config ("ms0:/PSP-OSS/SYSTEM/CONFIG/EFFECT.CFG", "Lines");

	      DesktopEffect = "Lines";
	    }
	  else if (DesktopEffect == "Lines")
	    {
	      //Nothing
	      Write_config ("ms0:/PSP-OSS/SYSTEM/CONFIG/EFFECT.CFG", "None");

	      DesktopEffect = "None";
	    }

	  checkkey = 1;
	  PauseVbl (30);

	}

      //Wallpaper
      if (pad.Buttons & PSP_CTRL_CONFIRM && cursorPosition.x > optionx + 150
	  && cursorPosition.x < optionx + 170
	  && cursorPosition.y > windowy + 120
	  && cursorPosition.y < windowy + 135)
	{
	  //SettingsScreen_MouseSpeed ();
	}
      /* //Theme
         if (pad.Buttons & PSP_CTRL_CONFIRM && cursorPosition.x > optionx + 150
         && cursorPosition.x < optionx + 250
         && cursorPosition.y > windowy + 135
         && cursorPosition.y < windowy + 150)
         {
         BrowseSkins ();
         } */

      //Move cursor over close button
      if (pad.Buttons & PSP_CTRL_UP)
	{
	  cursorPosition.x = windowx + 290;
	  cursorPosition.y = windowy + 5;
	}

      //Close settings screen
      if (pad.Buttons & PSP_CTRL_CONFIRM && cursorPosition.x > windowx + 285
	  && cursorPosition.x < windowx + 295
	  && cursorPosition.y > windowy + 3
	  && cursorPosition.y < windowy + 13)
	{
	  DesktopActive = 1;
	  break;
	}

      PutGFX (0, 0, 32, 32, cursor, cursorPosition.x, cursorPosition.y);
      PrintScreen ();
    }
}

void
DrawSettingsScreenGUI ()
{
  DoActiveDesktop ();

  if (checkkey == 1)
    {
      //Get keys
      SceUID file;
      file =
	sceIoOpen ("ms0:/PSP-OSS/SYSTEM/CONFIG/KEYS.cfg", PSP_O_RDONLY, 0);
      char keys[2];
      sceIoRead (file, keys, 2);
      sceIoClose (file);
      keys[2] = 0x00;

      if (strcmp (keys, "EN") == 0)
	{
	  currentkey = "Cross";
	}
      else if (strcmp (keys, "JP") == 0)
	{
	  currentkey = "Circle";
	}

      //Toggle wallpapers
      if (toggle_wallpapers == "LRT")
	{
	  sprintf (toggle_wallpapers_text, "with L and R");
	}
      else if (toggle_wallpapers == "SEL")
	{
	  sprintf (toggle_wallpapers_text, "with select");
	}
      else if (toggle_wallpapers == "OFF")
	{
	  sprintf (toggle_wallpapers_text, "Off");
	}

      //Toggle wallpapers
      if (toggle_MP3 == "LRT")
	{
	  sprintf (toggle_MP3_text, "with L and R");
	}
      else if (toggle_MP3 == "STA")
	{
	  sprintf (toggle_MP3_text, "with start");
	}
      else if (toggle_MP3 == "OFF")
	{
	  sprintf (toggle_MP3_text, "Off");
	}	

      //Mouse Speed
      if (mousespeed == 2)
	{
	  sprintf (mouse_speed_text, "1");
	}
      else if (mousespeed == 3)
	{
	  sprintf (mouse_speed_text, "2");
	}
      else if (mousespeed == 4)
	{
	  sprintf (mouse_speed_text, "3");
	}
      else if (mousespeed == 5)
	{
	  sprintf (mouse_speed_text, "4");
	}
      else if (mousespeed == 6)
	{
	  sprintf (mouse_speed_text, "5");
	}
      else if (mousespeed == 7)
	{
	  sprintf (mouse_speed_text, "6");
	}

      //CPU speed
      sprintf (CPU_Speed, "%d mHz", scePowerGetCpuClockFrequency ());

      checkkey = 0;
    }


  PutGFX (0, 0, 300, 15, Message_Window_Top1, windowx, windowy);
  PutGFX (0, 0, 300, 15, Settings_Window, windowx, windowy + 15);
  PutGFX (0, 0, 300, 15, Settings_Window, windowx, windowy + 30);
  PutGFX (0, 0, 300, 15, Settings_Window, windowx, windowy + 45);
  PutGFX (0, 0, 300, 15, Settings_Window, windowx, windowy + 60);
  PutGFX (0, 0, 300, 15, Settings_Window, windowx, windowy + 75);
  PutGFX (0, 0, 300, 15, Settings_Window, windowx, windowy + 90);
  PutGFX (0, 0, 300, 15, Settings_Window, windowx, windowy + 105);
  PutGFX (0, 0, 300, 15, Settings_Window, windowx, windowy + 120);
  PutGFX (0, 0, 300, 15, Settings_Window, windowx, windowy + 135);
  PutGFX (0, 0, 300, 15, Settings_Window_Bottom, windowx, windowy + 150);

  PutTextFont (itemx + 5, windowy + 17, LanguageT, LanguageC);
  PutTextFont (optionx + 150, windowy + 17, LangT, SettingsC);

  PutTextFont (itemx + 5, windowy + 32, CPUT, CPUC);
  PutTextFont (optionx + 150, windowy + 32, CPU_Speed, SettingsC);

  PutTextFont (itemx + 5, windowy + 47, ConfirmT, ConfirmC);
  PutTextFont (optionx + 150, windowy + 47, currentkey, SettingsC);
  
  PutTextFont (itemx + 5, windowy + 62, "Toggle MP3 Mode", ToggleWallpaperC);
  PutTextFont (optionx + 150, windowy + 62, toggle_MP3_text,
	       SettingsC);  

  PutTextFont (itemx + 5, windowy + 77, ToggleWallpaperT, ToggleWallpaperC);
  PutTextFont (optionx + 150, windowy + 77, toggle_wallpapers_text,
	       SettingsC);

  PutTextFont (itemx + 5, windowy + 92, DeasktopEffectT, DeasktopEffectC);
  PutTextFont (optionx + 150, windowy + 92, DesktopEffect, SettingsC);

  PutTextFont (itemx + 5, windowy + 122, MouseSpeedT, MouseSpeedC);
  PutTextFont (optionx + 160, windowy + 122, mouse_speed_text, SettingsC);

  /*PutTextFont (itemx + 5, windowy + 137, "Theme:", BLACK);
     PutTextFont (optionx + 150, windowy + 137, "Change", RED);
   */

  /*
     Mouseovers
   */

  //Language
  if (cursorPosition.x > optionx + 150 && cursorPosition.x < optionx + 250
      && cursorPosition.y > windowy + 15 && cursorPosition.y < windowy + 30)
    {
      PutTextFont (optionx + 150, windowy + 17, LangT, Settings2C);
    }
  if (cursorPosition.x > optionx + 150 && cursorPosition.x < optionx + 250
      && cursorPosition.y > windowy + 30 && cursorPosition.y < windowy + 45)
    {
      PutTextFont (optionx + 150, windowy + 32, CPU_Speed, Settings2C);
    }
  if (cursorPosition.x > optionx + 150 && cursorPosition.x < optionx + 250
      && cursorPosition.y > windowy + 45 && cursorPosition.y < windowy + 60)
    {
      PutTextFont (optionx + 150, windowy + 47, currentkey, Settings2C);
    }
  if (cursorPosition.x > optionx + 150 && cursorPosition.x < optionx + 250
      && cursorPosition.y > windowy + 60 && cursorPosition.y < windowy + 75)
    {
      PutTextFont (optionx + 150, windowy + 62, toggle_MP3_text,
		   Settings2C);
    }    
  if (cursorPosition.x > optionx + 150 && cursorPosition.x < optionx + 250
      && cursorPosition.y > windowy + 75 && cursorPosition.y < windowy + 90)
    {
      PutTextFont (optionx + 150, windowy + 77, toggle_wallpapers_text,
		   Settings2C);
    }
  if (cursorPosition.x > optionx + 150 && cursorPosition.x < optionx + 250
      && cursorPosition.y > windowy + 90 && cursorPosition.y < windowy + 105)
    {
      PutTextFont (optionx + 150, windowy + 92, DesktopEffect, Settings2C);
    }
  if (cursorPosition.x > optionx + 150 && cursorPosition.x < optionx + 250
      && cursorPosition.y > windowy + 120 && cursorPosition.y < windowy + 135)
    {
      PutTextFont (optionx + 160, windowy + 122, mouse_speed_text,
		   Settings2C);
    }
/*    
  if (cursorPosition.x > optionx + 150 && cursorPosition.x < optionx + 250
      && cursorPosition.y > windowy + 135 && cursorPosition.y < windowy + 150)
    {
      PutTextFont (optionx + 150, windowy + 137, "Change", DARK_RED);
    }
*/

  if (cursorPosition.x > windowx + 285 && cursorPosition.x < windowx + 295
      && cursorPosition.y > windowy + 3 && cursorPosition.y < windowy + 13)
    {
      PutGFX (0, 0, 10, 10, Window_Exit2, windowx + 285, windowy + 3);
    }
  else
    {
      PutGFX (0, 0, 10, 10, Window_Exit1, windowx + 285, windowy + 3);
    }
}

int i = 0;
void
SettingsScreen_Language ()
{
  if (language_ran == 0)
    {
      int dfd;
      dfd = sceIoDopen ("ms0:/PSP-OSS/SYSTEM/LANG/");
      sceIoDread (dfd, &dir);
      sceIoDread (dfd, &dir);

      while (sceIoDread (dfd, &dir) > 0)
	{
	      LR_language[i] = strdup (dir.d_name); 
	      i++;
	}

      //Close Dir Command
      frtd = 0;
      sceIoDclose (dfd);
      LR_language_amount = i;
      language_ran =1;
      PauseVbl (20);
    }
   
    
  while (1)
    {
      GetUserInput ();
      DrawSettingsScreenGUI ();
    
      PutGFX (0, 0, 70, 10, RightclickMenu_Top, optionx + 150, windowy + 15);
      for (i = 1; i <= LR_language_amount; i++ ) 
      {
      	PutGFX (0, 0, 70, 10, RightclickMenu_Body, optionx + 150, windowy + 15 + (i*10));  		            	
      	char Langfiles[i][10];      	
			  int size;
	      size = strlen (LR_language[i]);
	     // strncpy (Langfiles[i], LR_language[i],(7));
	      //Langfiles[i][7] = '\0';
	      //PutText (optionx + 155, windowy + 25+(i*10), Langfiles[i], SettingsC);   	      
	       
	    }
    	PutGFX (0, 0, 70, 10, RightclickMenu_Bottom, optionx + 150,windowy + 25+(LR_language_amount*10));

      //Mouseover
      if (cursorPosition.x > optionx + 150 && cursorPosition.x < optionx + 220
	  && cursorPosition.y > windowy + 15+ (i*10)
	  && cursorPosition.y < windowy + 25+ (i*10))
	{
	  PutGFX (0, 0, 70, 10, RightclickMenu_Body_Over, optionx + 150,
		  windowy + 15 + (i*10));
	}	      


      //Confirm
      if (pad.Buttons & PSP_CTRL_CONFIRM)
	{
	  if (cursorPosition.x > optionx + 150
	      && cursorPosition.x < optionx + 220
	      && cursorPosition.y > windowy + 25
	      && cursorPosition.y < windowy + 35)
	    {
	      //Set language to ENGLISH
	    }

	  PauseVbl (30);
	  GetUserInput ();
	  break;
	}


      PutGFX (0, 0, 32, 32, cursor, cursorPosition.x, cursorPosition.y);
      PrintScreen ();
    }
  
}


void
SettingsScreen_MouseSpeed ()
{
  while (1)
    {
      GetUserInput ();
      DrawSettingsScreenGUI ();
      checkkey = 1;

      PutGFX (0, 0, 70, 10, RightclickMenu_Top, optionx + 170, windowy + 65);
      PutGFX (0, 0, 70, 10, RightclickMenu_Body, optionx + 170, windowy + 75);
      PutGFX (0, 0, 70, 10, RightclickMenu_Body, optionx + 170, windowy + 85);
      PutGFX (0, 0, 70, 10, RightclickMenu_Body, optionx + 170, windowy + 95);
      PutGFX (0, 0, 70, 10, RightclickMenu_Body, optionx + 170,
	      windowy + 105);
      PutGFX (0, 0, 70, 10, RightclickMenu_Body, optionx + 170,
	      windowy + 115);
      PutGFX (0, 0, 70, 10, RightclickMenu_Body, optionx + 170,
	      windowy + 125);
      PutGFX (0, 0, 70, 10, RightclickMenu_Bottom, optionx + 170,
	      windowy + 135);

      //Mouseover
      if (cursorPosition.x > optionx + 170 && cursorPosition.x < optionx + 240
	  && cursorPosition.y > windowy + 75
	  && cursorPosition.y < windowy + 85)
	{
	  PutGFX (0, 0, 70, 10, RightclickMenu_Body_Over, optionx + 170,
		  windowy + 75);
	}
      else if (cursorPosition.x > optionx + 170
	       && cursorPosition.x < optionx + 240
	       && cursorPosition.y > windowy + 85
	       && cursorPosition.y < windowy + 95)
	{
	  PutGFX (0, 0, 70, 10, RightclickMenu_Body_Over, optionx + 170,
		  windowy + 85);
	}
      else if (cursorPosition.x > optionx + 170
	       && cursorPosition.x < optionx + 240
	       && cursorPosition.y > windowy + 95
	       && cursorPosition.y < windowy + 105)
	{
	  PutGFX (0, 0, 70, 10, RightclickMenu_Body_Over, optionx + 170,
		  windowy + 95);
	}
      else if (cursorPosition.x > optionx + 170
	       && cursorPosition.x < optionx + 240
	       && cursorPosition.y > windowy + 105
	       && cursorPosition.y < windowy + 115)
	{
	  PutGFX (0, 0, 70, 10, RightclickMenu_Body_Over, optionx + 170,
		  windowy + 105);
	}
      else if (cursorPosition.x > optionx + 170
	       && cursorPosition.x < optionx + 240
	       && cursorPosition.y > windowy + 115
	       && cursorPosition.y < windowy + 125)
	{
	  PutGFX (0, 0, 70, 10, RightclickMenu_Body_Over, optionx + 170,
		  windowy + 115);
	}
      else if (cursorPosition.x > optionx + 170
	       && cursorPosition.x < optionx + 240
	       && cursorPosition.y > windowy + 125
	       && cursorPosition.y < windowy + 135)
	{
	  PutGFX (0, 0, 70, 10, RightclickMenu_Body_Over, optionx + 170,
		  windowy + 125);
	}


      //Confirm
      if (pad.Buttons & PSP_CTRL_CONFIRM)
	{
	  if (cursorPosition.x > optionx + 170
	      && cursorPosition.x < optionx + 240
	      && cursorPosition.y > windowy + 75
	      && cursorPosition.y < windowy + 85)
	    {
	      mousespeed = 2;
	      Write_config ("ms0:/PSP-OSS/SYSTEM/CONFIG/MOUSE_SPEED.cfg",
			    "1");
	      DrawSettingsScreenGUI ();
	      break;
	    }
	  else if (cursorPosition.x > optionx + 170
		   && cursorPosition.x < optionx + 240
		   && cursorPosition.y > windowy + 85
		   && cursorPosition.y < windowy + 95)
	    {
	      mousespeed = 3;
	      Write_config ("ms0:/PSP-OSS/SYSTEM/CONFIG/MOUSE_SPEED.cfg",
			    "2");
	      DrawSettingsScreenGUI ();
	      break;
	    }
	  else if (cursorPosition.x > optionx + 170
		   && cursorPosition.x < optionx + 240
		   && cursorPosition.y > windowy + 95
		   && cursorPosition.y < windowy + 105)
	    {
	      mousespeed = 4;
	      Write_config ("ms0:/PSP-OSS/SYSTEM/CONFIG/MOUSE_SPEED.cfg",
			    "3");
	      DrawSettingsScreenGUI ();
	      break;
	    }
	  else if (cursorPosition.x > optionx + 170
		   && cursorPosition.x < optionx + 240
		   && cursorPosition.y > windowy + 105
		   && cursorPosition.y < windowy + 115)
	    {
	      mousespeed = 5;
	      Write_config ("ms0:/PSP-OSS/SYSTEM/CONFIG/MOUSE_SPEED.cfg",
			    "4");
	      DrawSettingsScreenGUI ();
	      break;
	    }
	  else if (cursorPosition.x > optionx + 170
		   && cursorPosition.x < optionx + 240
		   && cursorPosition.y > windowy + 115
		   && cursorPosition.y < windowy + 125)
	    {
	      mousespeed = 6;
	      Write_config ("ms0:/PSP-OSS/SYSTEM/CONFIG/MOUSE_SPEED.cfg",
			    "5");
	      DrawSettingsScreenGUI ();
	      break;
	    }
	  else if (cursorPosition.x > optionx + 170
		   && cursorPosition.x < optionx + 240
		   && cursorPosition.y > windowy + 125
		   && cursorPosition.y < windowy + 135)
	    {
	      mousespeed = 7;
	      Write_config ("ms0:/PSP-OSS/SYSTEM/CONFIG/MOUSE_SPEED.cfg",
			    "6");
	      DrawSettingsScreenGUI ();
	      break;
	    }

	  GetUserInput ();
	}

      PutTextFont (optionx + 200, windowy + 75, "1", SettingsC);
      PutTextFont (optionx + 200, windowy + 85, "2", SettingsC);
      PutTextFont (optionx + 200, windowy + 95, "3", SettingsC);
      PutTextFont (optionx + 200, windowy + 105, "4", SettingsC);
      PutTextFont (optionx + 200, windowy + 115, "5", SettingsC);
      PutTextFont (optionx + 200, windowy + 125, "6", SettingsC);

      PutGFX (0, 0, 32, 32, cursor, cursorPosition.x, cursorPosition.y);
      PrintScreen ();
    }
}

void
Toggle_Lang (int mode)
{
  if (language_ran == 0)
    {
      int dfd;
      dfd = sceIoDopen ("ms0:/PSP-OSS/SYSTEM/LANG/");
      sceIoDread (dfd, &dir);
      sceIoDread (dfd, &dir);

      while (sceIoDread (dfd, &dir) > 0)
	{
	      LR_language[i] = strdup (dir.d_name); 
	      i++;
	}

      //Close Dir Command
      frtd = 0;
      sceIoDclose (dfd);
      LR_language_amount = i;
      language_ran =1;
      PauseVbl (20);
    }   

  //Next ConfigFile
  if (mode == "NEXT")
    {    	
      LR_language_current += 1;

      if (LR_language_amount == LR_language_current)
					{
					  LR_language_current = 0;
					}
		  Write_config ("ms0:/PSP-OSS/SYSTEM/CONFIG/LANG.cfg", LR_language[LR_language_current]);
		  textlang ();     
    }
  }
  