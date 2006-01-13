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
PSP-OSS Cursor
Cursor Movement coded by Daurnimator
*/
#include "main.h"
#include "filebrowser.h"
#include "cursor.h"

//Cursor Movement Coded my Daurnimator
float distancemousemoves;
int rispressed = 0;
void
cursorHandler (int analogX, int analogY)
{
  if (pad.Buttons & PSP_CTRL_RTRIGGER)
    {
      //Number of Times pressing R speeds moving the up by    
      distancemousemoves = 3 + mousespeed;
      rispressed = 1;
    }
  else
    {
      distancemousemoves =  mousespeed;
      rispressed = 0;
    }
  //Left
  if ((cursorPosition.x > 0) && (analogX <= 100))
    {
      cursorPosition.x -= distancemousemoves;
      if ((cursorPosition.x > 0) && (analogX <= 55))
	{
	  cursorPosition.x -= distancemousemoves;
	  if ((cursorPosition.x > 0) && (analogX <= 20))
	    {
	      cursorPosition.x -= distancemousemoves;
	      if ((cursorPosition.x > 0) && (analogX <= 2))
		{
		  cursorPosition.x -= distancemousemoves;
		}
	    }
	}
    }
  //Right
  if ((cursorPosition.x < 479) && (analogX >= 154))
    {
      cursorPosition.x += distancemousemoves;
      if ((cursorPosition.x < 479) && (analogX >= 199))
	{
	  cursorPosition.x += distancemousemoves;
	  if ((cursorPosition.x < 479) && (analogX >= 234))
	    {
	      cursorPosition.x += distancemousemoves;
	      if ((cursorPosition.x < 479) && (analogX >= 252))
		{
		  cursorPosition.x += distancemousemoves;
		}
	    }
	}
    }
  //Up
  if ((cursorPosition.y > 0) && (analogY <= 100))
    {
      cursorPosition.y -= distancemousemoves;
      if ((cursorPosition.y > 0) && (analogY <= 55))
	{
	  cursorPosition.y -= distancemousemoves;
	  if ((cursorPosition.y > 0) && (analogY <= 20))
	    {
	      cursorPosition.y -= distancemousemoves;
	      if ((cursorPosition.y > 0) && (analogY <= 2))
		{
		  cursorPosition.y -= distancemousemoves;
		}
	    }
	}
    }
  //Down
  if ((cursorPosition.y < 271) && (analogY >= 154))
    {
      cursorPosition.y += distancemousemoves;
      if ((cursorPosition.y < 271) && (analogY >= 199))
	{
	  cursorPosition.y += distancemousemoves;
	  if ((cursorPosition.y < 271) && (analogY >= 234))
	    {
	      cursorPosition.y += distancemousemoves;
	      if ((cursorPosition.y < 271) && (analogY >= 252))
		{
		  cursorPosition.y += distancemousemoves;
		}
	    }
	}
    }

  //Makes it so if the mouse tries to go offscreen, it returns it to on screen
  if (rispressed == 0)
    {
      //Left
      if (cursorPosition.x <= 0)
	{
	  cursorPosition.x = 0;
	}
      //Right
      if (cursorPosition.x >= 479)
	{
	  cursorPosition.x = 479;
	}
      //Up
      if (cursorPosition.y <= 0)
	{
	  cursorPosition.y = 0;
	}
      //Down
      if (cursorPosition.y >= 271)
	{
	  cursorPosition.y = 271;
	}
    }
  else if (rispressed == 1)
    {
      //Left
      if (cursorPosition.x <= 0)
	{
	  cursorPosition.x = 479;
	}
      //Right
      else if (cursorPosition.x >= 479)
	{
	  cursorPosition.x = 0;
	}
      //Up
      else if (cursorPosition.y <= 0)
	{
	  cursorPosition.y = 271;
	}
      //Down
      else if (cursorPosition.y >= 271)
	{
	  cursorPosition.y = 0;
	}
    }
}

//Mechanism that finds which icon your'e over
void
findIcon ()
{	
  if (!(cursorPosition.y <= 15 || cursorPosition.y >= 272 - 15))
    {
      //Row
      if (cursorPosition.x > (IconXSize * 0)
	  && cursorPosition.x < (IconXSize * 1))
	{
	  iconSelected.row = 1;
	}

      else if (cursorPosition.x > (IconXSize * 1)
	       && cursorPosition.x < (IconXSize * 2))
	{
	  iconSelected.row = 2;
	}

      else if (cursorPosition.x > (IconXSize * 2)
	       && cursorPosition.x < (IconXSize * 3))
	{
	  iconSelected.row = 3;
	}

      else if (cursorPosition.x > (IconXSize * 3)
	       && cursorPosition.x < (IconXSize * 4))
	{
	  iconSelected.row = 4;
	}

      else if (cursorPosition.x > (IconXSize * 4)
	       && cursorPosition.x < (IconXSize * 5))
	{
	  iconSelected.row = 5;
	}

      else if (cursorPosition.x > (IconXSize * 5)
	       && cursorPosition.x < (IconXSize * 6))
	{
	  iconSelected.row = 6;
	}

      else if (cursorPosition.x > (IconXSize * 6)
	       && cursorPosition.x < (IconXSize * 7))
	{
	  iconSelected.row = 7;
	}

      else if (cursorPosition.x > (IconXSize * 7)
	       && cursorPosition.x < (IconXSize * 8))
	{
	  iconSelected.row = 8;
	}

      //Col
      if ((cursorPosition.y - 15) > (IconYSize * 0)
	  && (cursorPosition.y - 15) < (IconYSize * 1))
	{
	  iconSelected.col = 1;
	}

      else if ((cursorPosition.y - 15) > (IconYSize * 1)
	       && (cursorPosition.y - 15) < (IconYSize * 2))
	{
	  iconSelected.col = 2;
	}

      else if ((cursorPosition.y - 15) > (IconYSize * 2)
	       && (cursorPosition.y - 15) < (IconYSize * 3))
	{
	  iconSelected.col = 3;
	}

      else if ((cursorPosition.y - 15) > (IconYSize * 3)
	       && (cursorPosition.y - 15) < (IconYSize * 4))
	{
	  iconSelected.col = 4;
	}
    }
  else
    {
      iconSelected.col = 0;
      iconSelected.row = 0;
    }
}

void
RightClick_Icon_Desktop (int PositionX, int PositionY, const char *filepath,
			 const char *filename)
{
  DesktopIconsActive = 0;
  char buffer[500];

  while (1)
    {

      GetUserInput ();

      PutGFX (0, 0, 480, 270, wallpaper, 0, 0);	//Wallpaper
      PutGFX (0, 0, 480, 15, taskbar, 0, 257);	//Taskbar
      PutGFX (0, 0, 480, 15, TopBar, 0, 0);	//Top Bar

      //The following code displays all pngs on the sceen when a window is open
      DoActiveDesktop ();

      PutGFX (0, 0, 70, 10, RightclickMenu_Top, PositionX, PositionY);
      PutGFX (0, 0, 70, 10, RightclickMenu_Body, PositionX, (PositionY + 10));
      PutGFX (0, 0, 70, 10, RightclickMenu_Body, PositionX, (PositionY + 20));
      PutGFX (0, 0, 70, 10, RightclickMenu_Body, PositionX, (PositionY + 30));
      PutGFX (0, 0, 70, 10, RightclickMenu_Body, PositionX, (PositionY + 40));

      PutTextFont ((PositionX + 5), (PositionY + 10), "Open", BLACK);
      PutTextFont ((PositionX + 5), (PositionY + 20), "Copy", BLACK);

      if (Pastefile == 1)
	{
	  PutGFX (0, 0, 70, 10, RightclickMenu_Body, PositionX,
		  (PositionY + 50));
	  PutGFX (0, 0, 70, 10, RightclickMenu_Bottom, PositionX,
		  (PositionY + 60));
	  PutTextFont ((PositionX + 5), (PositionY + 30), "Paste", BLACK);
	  PutTextFont ((PositionX + 5), (PositionY + 40), "Rename", BLACK);
	  PutTextFont ((PositionX + 5), (PositionY + 50), "Delete", BLACK);
	}
      else
	{
	  PutGFX (0, 0, 70, 10, RightclickMenu_Bottom, PositionX,
		  (PositionY + 50));
	  PutTextFont ((PositionX + 5), (PositionY + 30), "Rename", BLACK);
	  PutTextFont ((PositionX + 5), (PositionY + 40), "Delete", BLACK);
	}

      if (cursorPosition.x > PositionX && cursorPosition.x < (PositionX + 70)
	  && cursorPosition.y > (PositionY + 10)
	  && cursorPosition.y < (PositionY + 20))
	{
	  PutGFX (0, 0, 70, 10, RightclickMenu_Body_Over, PositionX,
		  (PositionY + 10));
	}
      else if (cursorPosition.x > PositionX
	       && cursorPosition.x < (PositionX + 70)
	       && cursorPosition.y > (PositionY + 20)
	       && cursorPosition.y < (PositionY + 30))
	{
	  PutGFX (0, 0, 70, 10, RightclickMenu_Body_Over, PositionX,
		  (PositionY + 20));
	}
      else if (cursorPosition.x > PositionX
	       && cursorPosition.x < (PositionX + 70)
	       && cursorPosition.y > (PositionY + 30)
	       && cursorPosition.y < (PositionY + 40))
	{
	  PutGFX (0, 0, 70, 10, RightclickMenu_Body_Over, PositionX,
		  (PositionY + 30));
	}
      else if (cursorPosition.x > PositionX
	       && cursorPosition.x < (PositionX + 70)
	       && cursorPosition.y > (PositionY + 40)
	       && cursorPosition.y < (PositionY + 50))
	{
	  PutGFX (0, 0, 70, 10, RightclickMenu_Body_Over, PositionX,
		  (PositionY + 40));
	}
      else if (Pastefile == 1 && cursorPosition.x > PositionX
	       && cursorPosition.x < (PositionX + 70)
	       && cursorPosition.y > (PositionY + 50)
	       && cursorPosition.y < (PositionY + 60))
	{
	  PutGFX (0, 0, 70, 10, RightclickMenu_Body_Over, PositionX,
		  (PositionY + 50));
	}

      PutGFX (0, 0, 32, 32, cursor, cursorPosition.x, cursorPosition.y);
      PrintScreen ();

      if (pad.Buttons & PSP_CTRL_CONFIRM)
	{

	  if (cursorPosition.x > PositionX
	      && cursorPosition.x < (PositionX + 70)
	      && cursorPosition.y > (PositionY + 10)
	      && cursorPosition.y < (PositionY + 20))
	    {
	      sprintf (buffer, "%s%s", filepath, filename);
	      OpenFile (buffer);
	    }

	  //Copy
	  else if (cursorPosition.x > PositionX
		   && cursorPosition.x < (PositionX + 70)
		   && cursorPosition.y > (PositionY + 20)
		   && cursorPosition.y < (PositionY + 30))
	    {
	      sceIoRemove ("ms0:/PSP-OSS/SYSTEM/tempfile");

	      sprintf (buffer, "%s%s", filepath, filename);
	      CopyExecute (buffer, "ms0:/PSP-OSS/SYSTEM/tempfile");

	      SceUID file;
	      file =
		sceIoOpen ("ms0:/PSP-OSS/SYSTEM/tempfile_name",
			   PSP_O_WRONLY | PSP_O_CREAT | PSP_O_TRUNC, 0777);
	      sceIoWrite (file, filename, strlen (filename));
	      sceIoClose (file);

	      Pastefile = 1;
	    }

	  //Rename
	  else if (Pastefile == 0 && cursorPosition.x > PositionX
		   && cursorPosition.x < (PositionX + 70)
		   && cursorPosition.y > (PositionY + 30)
		   && cursorPosition.y < (PositionY + 40))
	    {
	      sprintf (buffer, "%s%s", filepath, filename);

	      char *new_filename;
	      new_filename = Keyboard (filename);

	      sceIoRename (buffer, new_filename);
	    }

	  //Delete
	  else if (Pastefile == 0 && cursorPosition.x > PositionX
		   && cursorPosition.x < (PositionX + 70)
		   && cursorPosition.y > (PositionY + 40)
		   && cursorPosition.y < (PositionY + 50))
	    {
	      sprintf (buffer, "%s%s", filepath, filename);
	      sceIoRemove (buffer);
	    }
	  //Paste
	  else if (Pastefile == 1 && cursorPosition.x > PositionX
		   && cursorPosition.x < (PositionX + 70)
		   && cursorPosition.y > (PositionY + 30)
		   && cursorPosition.y < (PositionY + 40))
	    {
	      SceUID file;
	      file =
		sceIoOpen ("ms0:/PSP-OSS/SYSTEM/tempfile_name", PSP_O_RDONLY,
			   0);
	      char Temp_Filename[255];
	      sceIoRead (file, Temp_Filename, 255);
	      int filesize = sceIoLseek (file, 0, SEEK_END);
	      sceIoClose (file);
	      Temp_Filename[filesize] = 0x00;

	      sprintf (buffer, "%sCopy %s", filepath, Temp_Filename);
	      CopyExecute ("ms0:/PSP-OSS/SYSTEM/tempfile", buffer);
	      sceIoRemove ("ms0:/PSP-OSS/SYSTEM/tempfile");

	      Pastefile = 0;
	    }
	  //Rename
	  else if (Pastefile == 1 && cursorPosition.x > PositionX
		   && cursorPosition.x < (PositionX + 70)
		   && cursorPosition.y > (PositionY + 40)
		   && cursorPosition.y < (PositionY + 50))
	    {
	      sprintf (buffer, "%s%s", filepath, filename);

	      char *new_filename;
	      new_filename = Keyboard (filename);

	      sceIoRename (buffer, new_filename);
	    }
	  //Delete
	  else if (Pastefile == 1 && cursorPosition.x > PositionX
		   && cursorPosition.x < (PositionX + 70)
		   && cursorPosition.y > (PositionY + 50)
		   && cursorPosition.y < (PositionY + 60))
	    {
	      sprintf (buffer, "%s%s", filepath, filename);
	      sceIoRemove (buffer);
	    }

	  frtd = 1;
	  DesktopIconsActive = 1;
	  PauseVbl (30);	//Pause for half a second
	  break;
	}
    }

}

void
RightClick_Desktop (int PositionX, int PositionY)
{
  DesktopIconsActive = 0;
  char buffer[500];

  while (1)
    {

      GetUserInput ();

      PutGFX (0, 0, 480, 270, wallpaper, 0, 0);	//Wallpaper
      PutGFX (0, 0, 480, 15, taskbar, 0, 257);	//Taskbar
      PutGFX (0, 0, 480, 15, TopBar, 0, 0);	//Top Bar

      //The following code displays all pngs on the sceen when a window is open
      DoActiveDesktop ();

      PutGFX (0, 0, 70, 10, RightclickMenu_Top, PositionX, PositionY);
      PutGFX (0, 0, 70, 10, RightclickMenu_Body, PositionX, (PositionY + 10));
      PutGFX (0, 0, 70, 10, RightclickMenu_Body, PositionX, (PositionY + 20));


      PutTextFont ((PositionX + 5), (PositionY + 10), "Backgr.", BLACK);
      PutTextFont ((PositionX + 5), (PositionY + 20), "Theme", BLACK);

      if (Pastefile == 1)
	{
	  PutGFX (0, 0, 70, 10, RightclickMenu_Body, PositionX,
		  (PositionY + 30));
	  PutGFX (0, 0, 70, 10, RightclickMenu_Bottom, PositionX,
		  (PositionY + 40));
	  PutTextFont ((PositionX + 5), (PositionY + 30), "Paste", BLACK);
	}
      else
	{
	  PutGFX (0, 0, 70, 10, RightclickMenu_Bottom, PositionX,
		  (PositionY + 30));
	}

      if (cursorPosition.x > PositionX && cursorPosition.x < (PositionX + 70)
	  && cursorPosition.y > (PositionY + 10)
	  && cursorPosition.y < (PositionY + 20))
	{
	  PutGFX (0, 0, 70, 10, RightclickMenu_Body_Over, PositionX,
		  (PositionY + 10));
	}
      else if (cursorPosition.x > PositionX
	       && cursorPosition.x < (PositionX + 70)
	       && cursorPosition.y > (PositionY + 20)
	       && cursorPosition.y < (PositionY + 30))
	{
	  PutGFX (0, 0, 70, 10, RightclickMenu_Body_Over, PositionX,
		  (PositionY + 20));
	}
      if (Pastefile == 1 && cursorPosition.x > PositionX
	  && cursorPosition.x < (PositionX + 70)
	  && cursorPosition.y > (PositionY + 30)
	  && cursorPosition.y < (PositionY + 40))
	{
	  PutGFX (0, 0, 70, 10, RightclickMenu_Body_Over, PositionX,
		  (PositionY + 30));
	}

      PutGFX (0, 0, 32, 32, cursor, cursorPosition.x, cursorPosition.y);
      PrintScreen ();

      if (pad.Buttons & PSP_CTRL_CONFIRM)
	{
	  if (cursorPosition.x > PositionX
	      && cursorPosition.x < (PositionX + 70)
	      && cursorPosition.y > (PositionY + 10)
	      && cursorPosition.y < (PositionY + 20))
	    {
	      BrowseWallpapers ();
	    }

	  else if (cursorPosition.x > PositionX
		   && cursorPosition.x < (PositionX + 70)
		   && cursorPosition.y > (PositionY + 20)
		   && cursorPosition.y < (PositionY + 30))
	    {
	      BrowseSkins ();
	    }

	  else if (Pastefile == 1 && cursorPosition.x > PositionX
		   && cursorPosition.x < (PositionX + 70)
		   && cursorPosition.y > (PositionY + 30)
		   && cursorPosition.y < (PositionY + 40))
	    {
	      SceUID file;
	      file =
		sceIoOpen ("ms0:/PSP-OSS/SYSTEM/tempfile_name", PSP_O_RDONLY,
			   0);
	      char Temp_Filename[255];
	      sceIoRead (file, Temp_Filename, 255);
	      int filesize = sceIoLseek (file, 0, SEEK_END);
	      sceIoClose (file);
	      Temp_Filename[filesize] = 0x00;

	      sprintf (buffer, "%sCopy %s", "ms0:/PSP-OSS/DESKTOP/",
		       Temp_Filename);
	      CopyExecute ("ms0:/PSP-OSS/SYSTEM/tempfile", buffer);
	      sceIoRemove ("ms0:/PSP-OSS/SYSTEM/tempfile");

	      Pastefile = 0;
	    }

	  frtd = 1;
	  DesktopIconsActive = 1;
	  PauseVbl (30);	//Pause for half a second
	  break;
	}
    }

}

void
Init_RightClick_Icon_Filebrowser (int PositionX, int PositionY,
				  const char *filepath, const char *filename, int RCMdir)
{
  FilebrowserRightclickActive = 1;

  FilebrowserRightclickPosX = PositionX;
  FilebrowserRightclickPosY = PositionY;
  RCMisdir = RCMdir;
  
  FilebrowserRightclickFilepath = filepath;
  FilebrowserRightclickFilename = filename;

  PauseVbl (30);		//Pause for half a second
}

void
RightClick_Icon_Filebrowser ()
{

  char buffer[500];

  PutGFX (0, 0, 70, 10, RightclickMenu_Top, FilebrowserRightclickPosX,
	  FilebrowserRightclickPosY);
  PutGFX (0, 0, 70, 10, RightclickMenu_Body, FilebrowserRightclickPosX,
	  (FilebrowserRightclickPosY + 10));
  PutGFX (0, 0, 70, 10, RightclickMenu_Body, FilebrowserRightclickPosX,
	  (FilebrowserRightclickPosY + 20));
  PutGFX (0, 0, 70, 10, RightclickMenu_Body, FilebrowserRightclickPosX,
	  (FilebrowserRightclickPosY + 30));

  PutTextFont ((FilebrowserRightclickPosX + 5),
	       (FilebrowserRightclickPosY + 10), "Open", BLACK);
  PutTextFont ((FilebrowserRightclickPosX + 5),
	       (FilebrowserRightclickPosY + 20), "Copy", BLACK);

  if (Pastefile == 1)
    {
      PutGFX (0, 0, 70, 10, RightclickMenu_Body, FilebrowserRightclickPosX,
	      (FilebrowserRightclickPosY + 40));
      PutGFX (0, 0, 70, 10, RightclickMenu_Body, FilebrowserRightclickPosX,
	      (FilebrowserRightclickPosY + 50));
      PutGFX (0, 0, 70, 10, RightclickMenu_Body, FilebrowserRightclickPosX,
	      (FilebrowserRightclickPosY + 60));
      PutGFX (0, 0, 70, 10, RightclickMenu_Bottom, FilebrowserRightclickPosX,
	      (FilebrowserRightclickPosY + 70));
      PutTextFont ((FilebrowserRightclickPosX + 5),
		   (FilebrowserRightclickPosY + 30), "Paste", BLACK);
      PutTextFont ((FilebrowserRightclickPosX + 5),
		   (FilebrowserRightclickPosY + 40), "Rename", BLACK);
      PutTextFont ((FilebrowserRightclickPosX + 5),
		   (FilebrowserRightclickPosY + 50), "Delete", BLACK);
      PutTextFont ((FilebrowserRightclickPosX + 5),
		   (FilebrowserRightclickPosY + 60), "Make QL", BLACK);
    }
  else
    {
      PutGFX (0, 0, 70, 10, RightclickMenu_Body, FilebrowserRightclickPosX,
	      (FilebrowserRightclickPosY + 40));
      PutGFX (0, 0, 70, 10, RightclickMenu_Body, FilebrowserRightclickPosX,
	      (FilebrowserRightclickPosY + 50));
      PutGFX (0, 0, 70, 10, RightclickMenu_Bottom, FilebrowserRightclickPosX,
	      (FilebrowserRightclickPosY + 60));
      PutTextFont ((FilebrowserRightclickPosX + 5),
		   (FilebrowserRightclickPosY + 30), "Rename", BLACK);
      PutTextFont ((FilebrowserRightclickPosX + 5),
		   (FilebrowserRightclickPosY + 40), "Delete", BLACK);
      PutTextFont ((FilebrowserRightclickPosX + 5),
		   (FilebrowserRightclickPosY + 50), "Make QL", BLACK);
    }

  if (cursorPosition.x > FilebrowserRightclickPosX
      && cursorPosition.x < (FilebrowserRightclickPosX + 70)
      && cursorPosition.y > (FilebrowserRightclickPosY + 10)
      && cursorPosition.y < (FilebrowserRightclickPosY + 20))
    {
      PutGFX (0, 0, 70, 10, RightclickMenu_Body_Over,
	      FilebrowserRightclickPosX, (FilebrowserRightclickPosY + 10));
    }
  else if (cursorPosition.x > FilebrowserRightclickPosX
	   && cursorPosition.x < (FilebrowserRightclickPosX + 70)
	   && cursorPosition.y > (FilebrowserRightclickPosY + 20)
	   && cursorPosition.y < (FilebrowserRightclickPosY + 30))
    {
      PutGFX (0, 0, 70, 10, RightclickMenu_Body_Over,
	      FilebrowserRightclickPosX, (FilebrowserRightclickPosY + 20));
    }
  else if (cursorPosition.x > FilebrowserRightclickPosX
	   && cursorPosition.x < (FilebrowserRightclickPosX + 70)
	   && cursorPosition.y > (FilebrowserRightclickPosY + 30)
	   && cursorPosition.y < (FilebrowserRightclickPosY + 40))
    {
      PutGFX (0, 0, 70, 10, RightclickMenu_Body_Over,
	      FilebrowserRightclickPosX, (FilebrowserRightclickPosY + 30));
    }
  else if (cursorPosition.x > FilebrowserRightclickPosX
	   && cursorPosition.x < (FilebrowserRightclickPosX + 70)
	   && cursorPosition.y > (FilebrowserRightclickPosY + 40)
	   && cursorPosition.y < (FilebrowserRightclickPosY + 50))
    {
      PutGFX (0, 0, 70, 10, RightclickMenu_Body_Over,
	      FilebrowserRightclickPosX, (FilebrowserRightclickPosY + 40));
    }
  else if (cursorPosition.x > FilebrowserRightclickPosX
	   && cursorPosition.x < (FilebrowserRightclickPosX + 70)
	   && cursorPosition.y > (FilebrowserRightclickPosY + 50)
	   && cursorPosition.y < (FilebrowserRightclickPosY + 60))
    {
      PutGFX (0, 0, 70, 10, RightclickMenu_Body_Over,
	      FilebrowserRightclickPosX, (FilebrowserRightclickPosY + 50));
    }
  else if (Pastefile == 1 && cursorPosition.x > FilebrowserRightclickPosX
	   && cursorPosition.x < (FilebrowserRightclickPosX + 70)
	   && cursorPosition.y > (FilebrowserRightclickPosY + 60)
	   && cursorPosition.y < (FilebrowserRightclickPosY + 70))
    {
      PutGFX (0, 0, 70, 10, RightclickMenu_Body_Over,
	      FilebrowserRightclickPosX, (FilebrowserRightclickPosY + 60));
    }    

  PutGFX (0, 0, 32, 32, cursor, cursorPosition.x, cursorPosition.y);
  PrintScreen ();

  if (pad.Buttons & PSP_CTRL_CONFIRM)
    {

      //Open
      if (cursorPosition.x > FilebrowserRightclickPosX
	  && cursorPosition.x < (FilebrowserRightclickPosX + 70)
	  && cursorPosition.y > (FilebrowserRightclickPosY + 10)
	  && cursorPosition.y < (FilebrowserRightclickPosY + 20))
	{
		if (RCMisdir == 1)
		{
		 // sprintf (buffer, "%s%s/", FilebrowserRightclickFilepath, FilebrowserRightclickFilename);
		 // FilebrowserRightclickActive = 0;
		 //BrowseDirectory (buffer);	
		}
		else
		{
	  	sprintf (buffer, "%s%s", FilebrowserRightclickFilepath,
		  FilebrowserRightclickFilename);
	  	OpenFile (buffer);
	  }
	}
      //Copy
      else if (RCMisdir != 1 && cursorPosition.x > FilebrowserRightclickPosX
	       && cursorPosition.x < (FilebrowserRightclickPosX + 70)
	       && cursorPosition.y > (FilebrowserRightclickPosY + 20)
	       && cursorPosition.y < (FilebrowserRightclickPosY + 30))
	{
	  sceIoRemove ("ms0:/PSP-OSS/SYSTEM/tempfile");

	  sprintf (buffer, "%s%s", FilebrowserRightclickFilepath,
		   FilebrowserRightclickFilename);
	  CopyExecute (buffer, "ms0:/PSP-OSS/SYSTEM/tempfile");

	  SceUID file;
	  file =
	    sceIoOpen ("ms0:/PSP-OSS/SYSTEM/tempfile_name",
		       PSP_O_WRONLY | PSP_O_CREAT | PSP_O_TRUNC, 0777);
	  sceIoWrite (file, FilebrowserRightclickFilename,
		      strlen (FilebrowserRightclickFilename));
	  sceIoClose (file);

	  Pastefile = 1;
	}
      //Rename
      else if (Pastefile == 0 && cursorPosition.x > FilebrowserRightclickPosX
	       && cursorPosition.x < (FilebrowserRightclickPosX + 70)
	       && cursorPosition.y > (FilebrowserRightclickPosY + 30)
	       && cursorPosition.y < (FilebrowserRightclickPosY + 40))
	{
	  sprintf (buffer, "%s%s", FilebrowserRightclickFilepath,
		   FilebrowserRightclickFilename);

	  char *new_filename;
	  new_filename = Keyboard (FilebrowserRightclickFilename);

	  sceIoRename (buffer, new_filename);
	}
      //Delete
      else if (RCMisdir != 1 && Pastefile == 0 && cursorPosition.x > FilebrowserRightclickPosX
	       && cursorPosition.x < (FilebrowserRightclickPosX + 70)
	       && cursorPosition.y > (FilebrowserRightclickPosY + 40)
	       && cursorPosition.y < (FilebrowserRightclickPosY + 50))
	{
	  	sprintf (buffer, "%s%s", FilebrowserRightclickFilepath,
		   FilebrowserRightclickFilename);
	  	sceIoRemove (buffer);	 
	}
      //Make Link
      else if (RCMisdir != 1 && Pastefile == 0 && cursorPosition.x > FilebrowserRightclickPosX
	       && cursorPosition.x < (FilebrowserRightclickPosX + 70)
	       && cursorPosition.y > (FilebrowserRightclickPosY + 50)
	       && cursorPosition.y < (FilebrowserRightclickPosY + 60))
	{
	  char buffer2[255];
    char buffer3[255]; 
    int size;
    int size2;
    char* suffix = strrchr(FilebrowserRightclickFilename, '.');   
    char Createlink[255];
    size = strlen (FilebrowserRightclickFilename);
    size2 = strlen (suffix);           
    strncpy (Createlink,FilebrowserRightclickFilename,(size-size2));
    Createlink[(size-size2)]='\0'; 
	  sprintf (buffer2, "%s%s", FilebrowserRightclickFilepath,Createlink);
	  char *new_filename;
	  new_filename = Keyboard (Createlink);
    sprintf (buffer3, "ms0:/PSP-OSS/DESKTOP/%s.pol", new_filename);
    Write_config (buffer3,buffer2);
    frtd = 1;
    DoDesktopIcons ();
            
	}
      //Paste
      else if (Pastefile == 1 && cursorPosition.x > FilebrowserRightclickPosX
	       && cursorPosition.x < (FilebrowserRightclickPosX + 70)
	       && cursorPosition.y > (FilebrowserRightclickPosY + 30)
	       && cursorPosition.y < (FilebrowserRightclickPosY + 40))
	{
	  SceUID file;
	  file =
	    sceIoOpen ("ms0:/PSP-OSS/SYSTEM/tempfile_name", PSP_O_RDONLY, 0);
	  char Temp_Filename[255];
	  sceIoRead (file, Temp_Filename, 255);
	  int filesize = sceIoLseek (file, 0, SEEK_END);
	  sceIoClose (file);
	  Temp_Filename[filesize] = 0x00;

	  sprintf (buffer, "%sCopy %s", FilebrowserRightclickFilepath,
		   Temp_Filename);
	  CopyExecute ("ms0:/PSP-OSS/SYSTEM/tempfile", buffer);
	  sceIoRemove ("ms0:/PSP-OSS/SYSTEM/tempfile");

	  Pastefile = 0;
	}
      //Rename
      else if (Pastefile == 1 && cursorPosition.x > FilebrowserRightclickPosX
	       && cursorPosition.x < (FilebrowserRightclickPosX + 70)
	       && cursorPosition.y > (FilebrowserRightclickPosY + 40)
	       && cursorPosition.y < (FilebrowserRightclickPosY + 50))
	{
	  sprintf (buffer, "%s%s", FilebrowserRightclickFilepath,
		   FilebrowserRightclickFilename);

	  char *new_filename;
	  new_filename = Keyboard (FilebrowserRightclickFilename);

	  sceIoRename (buffer, new_filename);
	}
      //Delete
      else if (Pastefile == 1 && cursorPosition.x > FilebrowserRightclickPosX
	       && cursorPosition.x < (FilebrowserRightclickPosX + 70)
	       && cursorPosition.y > (FilebrowserRightclickPosY + 50)
	       && cursorPosition.y < (FilebrowserRightclickPosY + 60))
	{
	  sprintf (buffer, "%s%s", FilebrowserRightclickFilepath,
		   FilebrowserRightclickFilename);
	  sceIoRemove (buffer);
	}
      //Make Link
      else if (RCMisdir != 1 && Pastefile == 1 && cursorPosition.x > FilebrowserRightclickPosX
	       && cursorPosition.x < (FilebrowserRightclickPosX + 70)
	       && cursorPosition.y > (FilebrowserRightclickPosY + 60)
	       && cursorPosition.y < (FilebrowserRightclickPosY + 70))
	{
	  char buffer2[255];
    char buffer3[255]; 
    int size;
    int size2;
    char* suffix = strrchr(FilebrowserRightclickFilename, '.');   
    char Createlink[255];
    size = strlen (FilebrowserRightclickFilename);
    size2 = strlen (suffix);           
    strncpy (Createlink,FilebrowserRightclickFilename,(size-size2));
    Createlink[(size-size2)]='\0'; 
	  sprintf (buffer2, "%s%s", FilebrowserRightclickFilepath,Createlink);
	  char *new_filename;
	  new_filename = Keyboard (Createlink);
    sprintf (buffer3, "ms0:/PSP-OSS/DESKTOP/%s.pol", new_filename);
    Write_config (buffer3,buffer2);
    frtd = 1;
    DoDesktopIcons ();
	}


      PauseVbl (30);		//Pause for half a second
      FilebrowserRightclickActive = 0;
      BrowseDirectory (FilebrowserRightclickFilepath);
    }

  PrintScreen ();
}
