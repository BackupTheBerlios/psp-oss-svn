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
	  PauseVbl (30);
	  SettingsScreen_Language ();
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
	  else if (strcmp (CPU_Speed, "265") == 0)
	    {
	      sceIoWrite (file, "333", 3);

	      scePowerSetClockFrequency (333, 333, 166);
	    }
	  //If its at 266mHz, set it to 333mHz.
	  else if (strcmp (CPU_Speed, "266") == 0)
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
	  PauseVbl (30);
	}

      //Desktop effect
      if (pad.Buttons & PSP_CTRL_CONFIRM && cursorPosition.x > optionx + 150
	  && cursorPosition.x < optionx + 250
	  && cursorPosition.y > windowy + 90
	  && cursorPosition.y < windowy + 105)
	{
	  /*
	     if(DesktopEffect=="None"){
	     //make it snow
	     Write_config("ms0:/PSP-OSS/SYSTEM/CONFIG/EFFECT.CFG","Snow");

	     Effect_GFX1 = LoadGFX("ms0:/PSP-OSS/SYSTEM/IMAGES/snow.png");
	     DesktopEffect="Snow";
	     Effect_Snow_PositionX=0;
	     Effect_Snow_PositionY=0;
	     }
	     else if(DesktopEffect=="Snow"){
	     //make it nothing
	     Write_config("ms0:/PSP-OSS/SYSTEM/CONFIG/EFFECT.CFG","None");

	     DesktopEffect="None";
	     }

	     checkkey=1;
	     PauseVbl(30);
	   */
	}

      //Wallpaper
      if (pad.Buttons & PSP_CTRL_CONFIRM && cursorPosition.x > optionx + 150
	  && cursorPosition.x < optionx + 170
	  && cursorPosition.y > windowy + 120
	  && cursorPosition.y < windowy + 135)
	{
	  SettingsScreen_MouseSpeed ();
	}
 /* //Theme
      if (pad.Buttons & PSP_CTRL_CONFIRM && cursorPosition.x > optionx + 150
	  && cursorPosition.x < optionx + 250
	  && cursorPosition.y > windowy + 135
	  && cursorPosition.y < windowy + 150)
	{
	  BrowseSkins ();
	}*/

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
	
	    //Mouse Speed
  if (mousespeed == 1)
    {
      sprintf (mouse_speed_text, "1");
    }
  else if (mousespeed == 2)
    {
      sprintf (mouse_speed_text, "2");
    }
  else if (mousespeed == 3)
    {
      sprintf (mouse_speed_text, "3");
    }
  else if (mousespeed == 4)
    {
      sprintf (mouse_speed_text, "4");
    }
  else if (mousespeed == 5)
    {
      sprintf (mouse_speed_text, "5");
    }
  else if (mousespeed == 6)
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

  PutTextFont (itemx + 5, windowy + 17, "Language:", BLACK);
  PutTextFont (optionx + 150, windowy + 17, "English", RED);

  PutTextFont (itemx + 5, windowy + 32, "CPU Speed:", BLACK);
  PutTextFont (optionx + 150, windowy + 32, CPU_Speed, RED);

  PutTextFont (itemx + 5, windowy + 47, "Confirm key:", BLACK);
  PutTextFont (optionx + 150, windowy + 47, currentkey, RED);

  //

  PutTextFont (itemx + 5, windowy + 77, "Mouse Speed:", BLACK);
  PutTextFont (optionx + 150, windowy + 77, toggle_wallpapers_text, RED);

  PutTextFont (itemx + 5, windowy + 92, "Desktop effect:", BLACK);
  PutTextFont (optionx + 150, windowy + 92, DesktopEffect, RED);

  //

  PutTextFont (itemx + 5, windowy + 122, "Mouse Speed:", BLACK);
  PutTextFont (optionx + 160, windowy + 122, mouse_speed_text, RED);

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
      PutTextFont (optionx + 150, windowy + 17, "English", DARK_RED);
    }
  if (cursorPosition.x > optionx + 150 && cursorPosition.x < optionx + 250
      && cursorPosition.y > windowy + 30 && cursorPosition.y < windowy + 45)
    {
      PutTextFont (optionx + 150, windowy + 32, CPU_Speed, DARK_RED);
    }
  if (cursorPosition.x > optionx + 150 && cursorPosition.x < optionx + 250
      && cursorPosition.y > windowy + 45 && cursorPosition.y < windowy + 60)
    {
      PutTextFont (optionx + 150, windowy + 47, currentkey, DARK_RED);
    }
  if (cursorPosition.x > optionx + 150 && cursorPosition.x < optionx + 250
      && cursorPosition.y > windowy + 75 && cursorPosition.y < windowy + 90)
    {
      PutTextFont (optionx + 150, windowy + 77, toggle_wallpapers_text,
		   DARK_RED);
    }
  if (cursorPosition.x > optionx + 150 && cursorPosition.x < optionx + 250
      && cursorPosition.y > windowy + 90 && cursorPosition.y < windowy + 105)
    {
      PutTextFont (optionx + 150, windowy + 92, DesktopEffect, DARK_RED);
    }
  if (cursorPosition.x > optionx + 150 && cursorPosition.x < optionx + 250
      && cursorPosition.y > windowy + 120 && cursorPosition.y < windowy + 135)
    {
      PutTextFont (optionx + 160, windowy + 122, mouse_speed_text, DARK_RED);
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


void
SettingsScreen_Language ()
{
  while (1)
    {
      GetUserInput ();
      DrawSettingsScreenGUI ();

      PutGFX (0, 0, 70, 10, RightclickMenu_Top, optionx + 150, windowy + 15);
      PutGFX (0, 0, 70, 10, RightclickMenu_Body, optionx + 150, windowy + 25);
      PutGFX (0, 0, 70, 10, RightclickMenu_Bottom, optionx + 150,
	      windowy + 35);

      //Mouseover
      if (cursorPosition.x > optionx + 150 && cursorPosition.x < optionx + 220
	  && cursorPosition.y > windowy + 25
	  && cursorPosition.y < windowy + 35)
	{
	  PutGFX (0, 0, 70, 10, RightclickMenu_Body_Over, optionx + 150,
		  windowy + 25);
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

      PutTextFont (optionx + 155, windowy + 25, "English", RED);

      PutGFX (0, 0, 32, 32, cursor, cursorPosition.x, cursorPosition.y);
      PrintScreen ();
    }
}


void SettingsScreen_MouseSpeed ()
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
      PutGFX (0, 0, 70, 10, RightclickMenu_Body, optionx + 170, windowy + 105);
      PutGFX (0, 0, 70, 10, RightclickMenu_Body, optionx + 170, windowy + 115);
      PutGFX (0, 0, 70, 10, RightclickMenu_Body, optionx + 170, windowy + 125);
      PutGFX (0, 0, 70, 10, RightclickMenu_Bottom, optionx + 170, windowy + 135);
      
      //Mouseover
  if (cursorPosition.x > optionx + 170 && cursorPosition.x < optionx + 240 && cursorPosition.y > windowy + 75 && cursorPosition.y < windowy + 85)
	{
	  PutGFX (0, 0, 70, 10, RightclickMenu_Body_Over, optionx + 170,  windowy + 75);
	}
  else if (cursorPosition.x > optionx + 170 && cursorPosition.x < optionx + 240 && cursorPosition.y > windowy + 85 && cursorPosition.y < windowy + 95)
	{
	  PutGFX (0, 0, 70, 10, RightclickMenu_Body_Over, optionx + 170,  windowy + 85);
	}	
  else if (cursorPosition.x > optionx + 170 && cursorPosition.x < optionx + 240 && cursorPosition.y > windowy + 95 && cursorPosition.y < windowy + 105)
	{
	  PutGFX (0, 0, 70, 10, RightclickMenu_Body_Over, optionx + 170,  windowy + 95);
	}	
  else if (cursorPosition.x > optionx + 170 && cursorPosition.x < optionx + 240 && cursorPosition.y > windowy + 105 && cursorPosition.y < windowy + 115)
	{
	  PutGFX (0, 0, 70, 10, RightclickMenu_Body_Over, optionx + 170,  windowy + 105);
	}	
  else if (cursorPosition.x > optionx + 170 && cursorPosition.x < optionx + 240 && cursorPosition.y > windowy + 115 && cursorPosition.y < windowy + 125)
	{
	  PutGFX (0, 0, 70, 10, RightclickMenu_Body_Over, optionx + 170,  windowy + 115);
	}	
  else if (cursorPosition.x > optionx + 170 && cursorPosition.x < optionx + 240 && cursorPosition.y > windowy + 125 && cursorPosition.y < windowy + 135)
	{
	  PutGFX (0, 0, 70, 10, RightclickMenu_Body_Over, optionx + 170,  windowy + 125);
	}	


      //Confirm
  if (pad.Buttons & PSP_CTRL_CONFIRM)
	{
		  if (cursorPosition.x > optionx + 170 && cursorPosition.x < optionx + 240 && cursorPosition.y > windowy + 75 && cursorPosition.y < windowy + 85)
			{
				mousespeed = 1;
			  Write_config ("ms0:/PSP-OSS/SYSTEM/CONFIG/MOUSE_SPEED.cfg", "1");
			  DrawSettingsScreenGUI ();
			  break;
			}
		  else if (cursorPosition.x > optionx + 170 && cursorPosition.x < optionx + 240 && cursorPosition.y > windowy + 85 && cursorPosition.y < windowy + 95)
			{
				mousespeed = 2;
			  Write_config ("ms0:/PSP-OSS/SYSTEM/CONFIG/MOUSE_SPEED.cfg", "2");
			  DrawSettingsScreenGUI ();
			  break;
			}	
		  else if (cursorPosition.x > optionx + 170 && cursorPosition.x < optionx + 240 && cursorPosition.y > windowy + 95 && cursorPosition.y < windowy + 105)
			{
				mousespeed = 3;
			  Write_config ("ms0:/PSP-OSS/SYSTEM/CONFIG/MOUSE_SPEED.cfg", "3");
			  DrawSettingsScreenGUI ();
			  break;
			}	
		  else if (cursorPosition.x > optionx + 170 && cursorPosition.x < optionx + 240 && cursorPosition.y > windowy + 105 && cursorPosition.y < windowy + 115)
			{
				mousespeed = 4;
			  Write_config ("ms0:/PSP-OSS/SYSTEM/CONFIG/MOUSE_SPEED.cfg", "4");
			  DrawSettingsScreenGUI ();
			  break;
			}	
		  else if (cursorPosition.x > optionx + 170 && cursorPosition.x < optionx + 240 && cursorPosition.y > windowy + 115 && cursorPosition.y < windowy + 125)
			{
				mousespeed = 5;
			  Write_config ("ms0:/PSP-OSS/SYSTEM/CONFIG/MOUSE_SPEED.cfg", "5");
			  DrawSettingsScreenGUI ();
			  break;
			}	
		  else if (cursorPosition.x > optionx + 170 && cursorPosition.x < optionx + 240 && cursorPosition.y > windowy + 125 && cursorPosition.y < windowy + 135)
			{
				mousespeed = 6;
			  Write_config ("ms0:/PSP-OSS/SYSTEM/CONFIG/MOUSE_SPEED.cfg", "6");
			  DrawSettingsScreenGUI ();			  
			  break;
			}	

	  PauseVbl (30);
	  GetUserInput ();
	}

      PutTextFont (optionx + 200, windowy + 75, "1", RED);
      PutTextFont (optionx + 200, windowy + 85, "2", RED);
      PutTextFont (optionx + 200, windowy + 95, "3", RED);
      PutTextFont (optionx + 200, windowy + 105, "4", RED);
      PutTextFont (optionx + 200, windowy + 115, "5", RED);
      PutTextFont (optionx + 200, windowy + 125, "6", RED);

      PutGFX (0, 0, 32, 32, cursor, cursorPosition.x, cursorPosition.y);
      PrintScreen ();
    }
}

