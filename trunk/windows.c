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

-PlayStation Portable Open-Source Shell Shource

You'll need the latest PSP SDK, as well as zlib, libpng and libmad to compile.

WwW.PsP-OsS.CoM

*/

#include "main.h"
#include "windows.h"

void
MessageWindow (int MessageWindowHeader, int MessageWindowMessage)
{
  MessageWindowX = 100;
  MessageWindowY = 100;

  while (1)
    {
      //The following code displays all pngs on the sceen when a window is open
      DoActiveDesktop ();

      GetUserInput ();


      PutGFX (0, 0, 300, 15, Message_Window_Top1, MessageWindowX,
	      MessageWindowY);
      PutGFX (0, 0, 300, 75, Message_Window_Body, MessageWindowX,
	      (MessageWindowY + 15));

      if (cursorPosition.x > MessageWindowX
	  && cursorPosition.x < (MessageWindowX + 300)
	  && cursorPosition.y > MessageWindowY
	  && cursorPosition.y < (MessageWindowY + 15))
	{
	  PutGFX (0, 0, 300, 15, Message_Window_Top2, MessageWindowX,
		  MessageWindowY);
	}

      //OK button
      if (cursorPosition.x > (MessageWindowX + 125)
	  && cursorPosition.x < (MessageWindowX + 200)
	  && cursorPosition.y > (MessageWindowY + 65)
	  && cursorPosition.y < (MessageWindowY + 85))
	{
	  PutGFX (0, 0, 75, 20, Button2, (MessageWindowX + 113),
		  (MessageWindowY + 63));
	}
      else
	{
	  PutGFX (0, 0, 75, 20, Button1, (MessageWindowX + 113),
		  (MessageWindowY + 63));
	}

      PutTextFont ((MessageWindowX + 143), (MessageWindowY + 70), "OK",
		   0x00000000);

      //Move window
      if (pad.Buttons & PSP_CTRL_CONFIRM && cursorPosition.x > MessageWindowX
	  && cursorPosition.x < (MessageWindowX + 300)
	  && cursorPosition.y > MessageWindowY
	  && cursorPosition.y < (MessageWindowY + 15))
	{
	  if (pad.Lx == 255 || pad.Lx == 0 || pad.Ly == 255 || pad.Ly == 0)
	    {
	      MessageWindowX = (cursorPosition.x - 150);
	      MessageWindowY = (cursorPosition.y - 6);
	    }
	}

      if (cursorPosition.x > (MessageWindowX + 285)
	  && cursorPosition.x < (MessageWindowX + 295)
	  && cursorPosition.y > (MessageWindowY + 3)
	  && cursorPosition.y < (MessageWindowY + 13))
	{
	  PutGFX (0, 0, 10, 10, Window_Exit2, (MessageWindowX + 285),
		  (MessageWindowY + 3));
	}
      else
	{
	  PutGFX (0, 0, 10, 10, Window_Exit1, (MessageWindowX + 285),
		  (MessageWindowY + 3));
	}

      PutTextFont ((MessageWindowX + 5), (MessageWindowY + 5),
		   MessageWindowHeader, 0xFFFFFFFF);
      PutTextFont ((MessageWindowX + 5), (MessageWindowY + 20),
		   MessageWindowMessage, 0x00000000);

      //Close window
      if (pad.Buttons & PSP_CTRL_CONFIRM
	  && cursorPosition.x > (MessageWindowX + 125)
	  && cursorPosition.x < (MessageWindowX + 200)
	  && cursorPosition.y > (MessageWindowY + 65)
	  && cursorPosition.y < (MessageWindowY + 85))
	{
	  break;
	}
      if (pad.Buttons & PSP_CTRL_CONFIRM
	  && cursorPosition.x > (MessageWindowX + 285)
	  && cursorPosition.x < (MessageWindowX + 295)
	  && cursorPosition.y > (MessageWindowY + 3)
	  && cursorPosition.y < (MessageWindowY + 13))
	{
	  break;
	}

      PutGFX (0, 0, 32, 32, cursor, cursorPosition.x, cursorPosition.y);
      PrintScreen ();
    }

}

void
ShutDown_Prompt (int PowerWindowHeader)
{
  MessageWindowX = 100;
  MessageWindowY = 100;

  while (1)
    {

      GetUserInput ();

      PutGFX (0, 0, 480, 270, wallpaper, 0, 0);	//Wallpaper
      PutGFX (0, 0, 480, 15, taskbar, 0, 257);	//Taskbar
      PutGFX (0, 0, 480, 15, TopBar, 0, 0);	//Top Bar

      //The following code displays all pngs on the sceen when a window is open
      DoActiveDesktop ();

      PutGFX (0, 0, 300, 15, Message_Window_Top1, MessageWindowX,
	      MessageWindowY);
      PutGFX (0, 0, 300, 75, Message_Window_Body, MessageWindowX,
	      (MessageWindowY + 15));

      if (pad.Buttons & PSP_CTRL_LEFT)
	{
	  cursorPosition.x = (MessageWindowX + 70);
	  cursorPosition.y = (MessageWindowY + 70);
	}
      if (pad.Buttons & PSP_CTRL_RIGHT)
	{
	  cursorPosition.x = (MessageWindowX + 170);
	  cursorPosition.y = (MessageWindowY + 70);
	}
      if (pad.Buttons & PSP_CTRL_UP)
	{
	  cursorPosition.x = (MessageWindowX + 290);
	  cursorPosition.y = (MessageWindowY + 5);
	}

      //Shutdown button
      if (cursorPosition.x > (MessageWindowX + 65)
	  && cursorPosition.x < (MessageWindowX + 140)
	  && cursorPosition.y > (MessageWindowY + 65)
	  && cursorPosition.y < (MessageWindowY + 85))
	{
	  PutGFX (0, 0, 75, 20, Button2, (MessageWindowX + 65),
		  (MessageWindowY + 65));
	}
      else
	{
	  PutGFX (0, 0, 75, 20, Button1, (MessageWindowX + 65),
		  (MessageWindowY + 65));
	}

      PutTextFont ((MessageWindowX + 70), (MessageWindowY + 70), "Shutdown",
		   BLACK);

      //Reboot button
      if (cursorPosition.x > (MessageWindowX + 160)
	  && cursorPosition.x < (MessageWindowX + 235)
	  && cursorPosition.y > (MessageWindowY + 65)
	  && cursorPosition.y < (MessageWindowY + 85))
	{
	  PutGFX (0, 0, 75, 20, Button2, (MessageWindowX + 160),
		  (MessageWindowY + 65));
	}
      else
	{
	  PutGFX (0, 0, 75, 20, Button1, (MessageWindowX + 160),
		  (MessageWindowY + 65));
	}

      PutTextFont ((MessageWindowX + 165), (MessageWindowY + 70), " Reboot",
		   BLACK);

      if (cursorPosition.x > (MessageWindowX + 285)
	  && cursorPosition.x < (MessageWindowX + 295)
	  && cursorPosition.y > (MessageWindowY + 3)
	  && cursorPosition.y < (MessageWindowY + 13))
	{
	  PutGFX (0, 0, 10, 10, Window_Exit2, (MessageWindowX + 285),
		  (MessageWindowY + 3));
	}
      else
	{
	  PutGFX (0, 0, 10, 10, Window_Exit1, (MessageWindowX + 285),
		  (MessageWindowY + 3));
	}

      PutTextFont ((MessageWindowX + 5), (MessageWindowY + 5), "Shutdown",
		   WHITE);
      PutTextFont ((MessageWindowX + 20), (MessageWindowY + 20),
		   "What do you want to do?", BLACK);

      //Close window                        
      if (pad.Buttons & PSP_CTRL_CONFIRM
	  && cursorPosition.x > (MessageWindowX + 285)
	  && cursorPosition.x < (MessageWindowX + 295)
	  && cursorPosition.y > (MessageWindowY + 3)
	  && cursorPosition.y < (MessageWindowY + 13))
	{
	  break;
	}

      if (pad.Buttons & PSP_CTRL_CONFIRM
	  && cursorPosition.x > (MessageWindowX + 65)
	  && cursorPosition.x < (MessageWindowX + 140)
	  && cursorPosition.y > (MessageWindowY + 65)
	  && cursorPosition.y < (MessageWindowY + 85))
	{
	  ShutDown ();
	}

      if (pad.Buttons & PSP_CTRL_CONFIRM
	  && cursorPosition.x > (MessageWindowX + 160)
	  && cursorPosition.x < (MessageWindowX + 235)
	  && cursorPosition.y > (MessageWindowY + 65)
	  && cursorPosition.y < (MessageWindowY + 85))
	{
	  Reboot ();
	}

      PutGFX (0, 0, 32, 32, cursor, cursorPosition.x, cursorPosition.y);
      PrintScreen ();
    }
}
void
FadeScreenMessage (int FadeMessageWindowHeader,
		   int FadeMessageWindowMessageLine1,
		   int FadeMessageWindowMessageLine2,
		   int FadeMessageWindowMessageLine3)
{
  PutGFX (0, 0, 480, 270, wallpaper, 0, 0);	//Wallpaper
  PutGFX (0, 0, 480, 15, taskbar, 0, 257);	//Taskbar
  PutGFX (0, 0, 480, 15, TopBar, 0, 0);	//Top Bar

  PutGFX (0, 0, 480, 272, Fade, 0, 0);

  PutGFX (0, 0, 300, 15, Message_Window_Top1, 100, 100);
  PutGFX (0, 0, 300, 75, Message_Window_Body, 100, (100 + 15));
  PutTextFont ((100 + 5), (100 + 5), FadeMessageWindowHeader, 0xFFFFFFFF);

  PutTextFont ((100 + 5), (100 + 20), FadeMessageWindowMessageLine1,
	       0x00000000);
  PutTextFont ((100 + 5), (100 + 30), FadeMessageWindowMessageLine2,
	       0x00000000);
  PutTextFont ((100 + 5), (100 + 40), FadeMessageWindowMessageLine3,
	       0x00000000);
}


//Configuration
void
Configuration ()
{
  DesktopActive = 0;
  while (1)
    {
      GetUserInput ();
      findIcon ();
      DrawFullscreenWindow ("Configuration");

      if (pad.Buttons & PSP_CTRL_CONFIRM && cursorPosition.x > 465
	  && cursorPosition.x < 475 && cursorPosition.y > 3
	  && cursorPosition.y < 13)
	{
	  DesktopActive = 1;
	  break;
	}
      //Change wallpaper           
      if (iconSelected.row == 1 && iconSelected.col == 1)
	{
	  PutTextFont (5, 260, "Change wallpaper", WHITE);
	  PutGFX (0, 0, 48, 48, Icon_Wallpapers_Over, (IconXSize * 1 - 48),
		  (IconYSize * 1 - 48 + 5));
	}

      else
	{
	  PutGFX (0, 0, 48, 48, Icon_Wallpapers, (IconXSize * 1 - 48),
		  (IconYSize * 1 - 48 + 5));
	}

      //Change theme
      if (iconSelected.row == 2 && iconSelected.col == 1)
	{
	  PutTextFont (5, 260, "Change theme", WHITE);
	  PutGFX (0, 0, 48, 48, Icon_Themes_Over, (IconXSize * 2 - 48),
		  (IconYSize * 1 - 48 + 5));
	}

      else
	{
	  PutGFX (0, 0, 48, 48, Icon_Themes, (IconXSize * 2 - 48),
		  (IconYSize * 1 - 48 + 5));
	}

      if (pad.Buttons & PSP_CTRL_CONFIRM && iconSelected.row == 1
	  && iconSelected.col == 1)
	{
	  PauseVbl (30);
	  BrowseWallpapers ();
	}

      if (pad.Buttons & PSP_CTRL_CONFIRM && iconSelected.row == 2
	  && iconSelected.col == 1)
	{
	  PauseVbl (30);
	  BrowseSkins ();
	}

      PutGFX (0, 0, 32, 32, cursor, cursorPosition.x, cursorPosition.y);
      PrintScreen ();
    }
}

void
DrawFullscreenWindow (int FullscreenWindowHeader)
{
  PutGFX (0, 0, 480, 270, wallpaper, 0, 0);	//Wallpaper
  PutGFX (0, 0, 480, 15, Fullscreen_Window_Top1, 0, 0);
  PutGFX (0, 0, 480, 257, Fullscreen_Window_Body, 0, 15);

  if (cursorPosition.x > 0 && cursorPosition.x < 480 && cursorPosition.y > 0
      && cursorPosition.y < 15)
    {
      PutGFX (0, 0, 480, 15, Fullscreen_Window_Top2, 0, 0);
    }


  if (cursorPosition.x > 465 && cursorPosition.x < 475 && cursorPosition.y > 3
      && cursorPosition.y < 13)
    {
      PutGFX (0, 0, 10, 10, Window_Exit2, 465, 3);
    }
  else
    {
      PutGFX (0, 0, 10, 10, Window_Exit1, 465, 3);
    }

  //Move cursor over exit icon
  if (pad.Buttons & PSP_CTRL_UP)
    {
      cursorPosition.x = 470;
      cursorPosition.y = 10;
    }

  PutTextFont (5, 5, FullscreenWindowHeader, DARK_RED);

}
