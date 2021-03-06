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
#include "filebrowser.h"

void
BrowseWallpapers ()		// Browse Wallpapers :)
{
  int IconPositionX = 1;
  int IconPositionY = 1;
  int i = 0;
  int FBpage;
  int FBmore;
  FBpage = 1;
  FBmore = 0;

  if (BrowseWallpapersCache != 1)
    {
      int dfd;
      dfd = sceIoDopen ("ms0:/PSP-OSS/WALLPAPERS/");
      sceIoDread (dfd, &dir);
      sceIoDread (dfd, &dir);

      while (sceIoDread (dfd, &dir) > 0)
	{
		free(wallpapericonname[i]);
	  wallpapericonname[i] = NULL;
	  wallpapericonname[i] = strdup (dir.d_name);
	  if (dir.d_stat.st_attr & FIO_SO_IFDIR)
	    {
	      i--;
	    }
	  i++;
	}

      //Close Dir Command
      frtd = 0;
      sceIoDclose (dfd);
      numberoffilesinwallpapers = i;
      BrowseWallpapersCache = 1;
      PauseVbl (20);
      BrowseWallpapers ();
    }

  else
    {
      while (1)
	{

	  DrawFullscreenWindow (FSWallpaperT);
	  findIcon ();
	  GetUserInput ();

	  while (numberoffilesinwallpapers > i)
	    {
	      if (i >= (32 * (FBpage - 1)) && i < (32 * FBpage))
		{
		  //Get file extension
		  char *suffix = strrchr (wallpapericonname[i], '.');
		  //added 24th of dec           
		  char wallitem[i][13];
		  strncpy (wallitem[i], wallpapericonname[i], 6);
		  wallitem[i][6] = '\0';
		  //added 24th of dec     

		  //Images
		  if (stricmp (suffix, ".png") == 0)
		    {
		      if (iconSelected.row == IconPositionX
			  && iconSelected.col == IconPositionY)
			{
			  PutGFX (0, 0, 48, 48, Icon_GFX_Over,
				  (60 * IconPositionX - 48),
				  (60 * IconPositionY - 48 + 5));
			  PutTextFont (5, 260, wallpapericonname[i],
				       WallpaperTextTBC);
			  PutText ((60 * IconPositionX - 46), (60 * IconPositionY + 7), wallitem[i], WallpaperTextHLC);	//added 24th of dec
			  PutTextFont ((cursorPosition.x + 15),
				       cursorPosition.y, wallpapericonname[i],
				       WallpaperTextOverC);
			}
		      else
			{
			  PutText ((60 * IconPositionX - 46), (60 * IconPositionY + 7), wallitem[i], WallpaperTextC);	//added 24th of dec
			  PutGFX (0, 0, 48, 48, Icon_GFX,
				  (60 * IconPositionX - 48),
				  (60 * IconPositionY - 48 + 5));
			}
		    }

		  if (pad.Buttons & PSP_CTRL_CONFIRM
		      && iconSelected.row == IconPositionX
		      && iconSelected.col == IconPositionY)
		    {
		      char buffer[200];
		      sprintf (buffer, "ms0:/PSP-OSS/WALLPAPERS/%s",
			       wallpapericonname[i]);
		      SetWallpaper (buffer);
		      PauseVbl (10);
		      break;

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
		}
	      i++;
	    }

	  if (FBpage > 1)
	    {
	      //Previous mouseover
	      if (cursorPosition.x > 190 && cursorPosition.x < 230
		  && cursorPosition.y > 250 && cursorPosition.y < 272)
		{
		  PutGFX (0, 0, 40, 25, FBLeft, 190, 247);
		  PutText (5, 260, PreviousPageT, PreviousPageC);	//Displays the name of the item in the Start Menu                               
		}
	      else
		{
		  PutGFX (0, 0, 40, 25, FBLeft, 190, 247);
		}

	      //Previous

	      if (pad.Buttons & PSP_CTRL_CONFIRM && cursorPosition.x > 190
		  && cursorPosition.x < 230 && cursorPosition.y > 250
		  && cursorPosition.y < 272 || pad.Buttons & PSP_CTRL_LEFT)
		{
		  FBpage -= 1;
		  PauseVbl (15);
		}
	    }

	  if (numberoffilesinwallpapers > 32 * FBpage)
	    {
	      //Next mouseover
	      if (cursorPosition.x > 250 && cursorPosition.x < 490
		  && cursorPosition.y > 250 && cursorPosition.y < 272)
		{
		  PutGFX (0, 0, 40, 25, FBRight, 250, 247);
		  PutText (5, 260, NextPageT, NextPageC);	//Displays the name of the item in the Start Menu
		}
	      else
		{
		  PutGFX (0, 0, 40, 25, FBRight, 250, 247);
		}

	      //Next

	      if (pad.Buttons & PSP_CTRL_CONFIRM && cursorPosition.x > 250
		  && cursorPosition.x < 490 && cursorPosition.y > 250
		  && cursorPosition.y < 272 || pad.Buttons & PSP_CTRL_RIGHT)
		{
		  FBpage += 1;
		  PauseVbl (15);
		}
	    }

	  if (pad.Buttons & PSP_CTRL_CONFIRM && cursorPosition.x > 465
	      && cursorPosition.x < 475 && cursorPosition.y > 3
	      && cursorPosition.y < 13)
	    {
	      break;
	    }
	  //if(pad.Buttons & PSP_CTRL_TRIANGLE){
	  //    break;
	  //}

	  PutGFX (0, 0, 32, 32, cursor, cursorPosition.x, cursorPosition.y);
	  PrintScreen ();

	  IconPositionX = 1;
	  IconPositionY = 1;
	  i = 0;
	}

    }
}


void
BrowseSkins ()
{
  int IconPositionX = 1;
  int IconPositionY = 1;
  int i = 0;
  int FBpage;
  int FBmore;
  FBpage = 1;
  FBmore = 0;

  if (BrowseSkinsCache != 1)
    {
      int dfd;
      dfd = sceIoDopen ("ms0:/PSP-OSS/SKINS/");
      sceIoDread (dfd, &dir);
      sceIoDread (dfd, &dir);

      while (sceIoDread (dfd, &dir) > 0)
	{
		free(skinsiconname[i]);
	  skinsiconname[i] = NULL;
	  skinsiconname[i] = strdup (dir.d_name);
	  if (dir.d_stat.st_attr & FIO_SO_IFDIR)
	    {
	      i--;
	    }
	  i++;
	}

      //Close Dir Command
      frtd = 0;
      sceIoDclose (dfd);
      numberoffilesinskins = i;
      BrowseSkinsCache = 1;
      PauseVbl (20);
      BrowseSkins ();
    }

  else
    {
      while (1)
	{

	  DrawFullscreenWindow (FSThemeT);
	  findIcon ();
	  GetUserInput ();

	  while (numberoffilesinskins > i)
	    {
	      if (i >= (32 * (FBpage - 1)) && i < (32 * FBpage))
		{
	      char *suffix = strrchr (skinsiconname[i], '.');
	      char skinitem[i][6];
	      char skinitemtxt[i][52];
	      int size;
	      int size2;
	      size = strlen (skinsiconname[i]);
	      size2 = strlen (suffix);

		  if (size <= 12)
		    {
		    	strncpy (skinitem[i], skinsiconname[i], (size - size2));
		      skinitem[i][(size - size2)] = '\0';
		    }
		    else
		    {	      	
	      	strncpy (skinitem[i], skinitem[i], 6);
	      	skinitem[i][6] = '\0';
	      }    
		    	strncpy (skinitemtxt[i], skinsiconname[i], (size - size2));
		      skinitemtxt[i][(size - size2)] = '\0';	      

		  if (iconSelected.row == IconPositionX
		      && iconSelected.col == IconPositionY)
		    {
		      PutGFX (0, 0, 48, 48, Icon_Themes_Over,
			      (60 * IconPositionX - 48),
			      (60 * IconPositionY - 48 + 5));
		      PutTextFont (5, 260, skinitemtxt[i], SkinTextTBC);
		      PutText ((60 * IconPositionX - 46), (60 * IconPositionY + 7), skinitem[i], SkinTextHLC);	//added 24th of dec
		      PutTextFont ((cursorPosition.x + 15), cursorPosition.y,
				   skinitemtxt[i], SkinTextOverC);
		    }
		  else
		    {
		      PutGFX (0, 0, 48, 48, Icon_Themes,
			      (60 * IconPositionX - 48),
			      (60 * IconPositionY - 48 + 5));
		      PutText ((60 * IconPositionX - 46), (60 * IconPositionY + 7), skinitem[i], SkinTextC);	//added 24th of dec
		    }

		  if (pad.Buttons & PSP_CTRL_CONFIRM
		      && iconSelected.row == IconPositionX
		      && iconSelected.col == IconPositionY)
		    {
		      SetSkin (skinsiconname[i]);
		      break;	//Just incase

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
		}
	      i++;
	    }

	  if (FBpage > 1)
	    {
	      //Previous mouseover
	      if (cursorPosition.x > 190 && cursorPosition.x < 230
		  && cursorPosition.y > 250 && cursorPosition.y < 272)
		{
		  PutGFX (0, 0, 40, 25, FBLeft, 190, 247);
		  PutText (5, 260, PreviousPageT, PreviousPageC);	//Displays the name of the item in the Start Menu
		}
	      else
		{
		  PutGFX (0, 0, 40, 25, FBLeft, 190, 247);
		}

	      //Previous

	      if (pad.Buttons & PSP_CTRL_CONFIRM && cursorPosition.x > 190
		  && cursorPosition.x < 230 && cursorPosition.y > 250
		  && cursorPosition.y < 272 || pad.Buttons & PSP_CTRL_LEFT)
		{
		  FBpage -= 1;
		  PauseVbl (15);
		}
	    }

	  if (numberoffilesinskins > 32 * FBpage)
	    {
	      //Next mouseover
	      if (cursorPosition.x > 250 && cursorPosition.x < 490
		  && cursorPosition.y > 250 && cursorPosition.y < 272)
		{
		  PutGFX (0, 0, 40, 25, FBRight, 250, 247);
		  PutText (5, 260, NextPageT, NextPageC);	//Displays the name of the item in the Start Menu
		}
	      else
		{
		  PutGFX (0, 0, 40, 25, FBRight, 250, 247);
		}

	      //Next

	      if (pad.Buttons & PSP_CTRL_CONFIRM && cursorPosition.x > 250
		  && cursorPosition.x < 490 && cursorPosition.y > 250
		  && cursorPosition.y < 272 || pad.Buttons & PSP_CTRL_RIGHT)
		{
		  FBpage += 1;
		  PauseVbl (15);
		}
	    }

	  if (pad.Buttons & PSP_CTRL_CONFIRM && cursorPosition.x > 465
	      && cursorPosition.x < 475 && cursorPosition.y > 3
	      && cursorPosition.y < 13)
	    {
	      break;
	    }
	  //if(pad.Buttons & PSP_CTRL_TRIANGLE){
	  //    break;
	  //}

	  PutGFX (0, 0, 32, 32, cursor, cursorPosition.x, cursorPosition.y);
	  PrintScreen ();

	  IconPositionX = 1;
	  IconPositionY = 1;
	  i = 0;
	}

    }
}
void
BrowseDirectory (const char *Directory)
{
  //Icon positions. This is the start position of where to place icons.
  int IconPositionX = 1;
  int IconPositionY = 1;
  char Dic[500];
  strcpy (Dic, Directory);
  int i = 0;
  int FBpage;
  int FBmore;
  FBpage = 1;
  FBmore = 0;
  //The intrenger we use to open the directory.
  int dfd;
loo:
  //Open the directory

  dfd = sceIoDopen (Dic);

  //SceIoDread 2 times, to skip the "." and ".." dir. We dont want to display those.
  sceIoDread (dfd, &dir);
  //sceIoDread(dfd, &dir);
  if (strcmp (Dic, "ms0:/") != 0)
    {
      sceIoDread (dfd, &dir);
    }

  //List files in folder.
  //While there are more files left...     
  while (sceIoDread (dfd, &dir) > 0)
    {
			free(iconname[i]);
	  	iconname[i] = NULL;    	
      iconname[i] = strdup (dir.d_name);

      //If it's a dir. Set isdir to 1.
      if (dir.d_stat.st_attr & FIO_SO_IFDIR)
	{
	  isdir[i] = 1;
	}

      //If its not a dir (it's a file), set isdir to 0.
      else
	{
	  isdir[i] = 0;
	}

      //1++ for the next file
      i++;
    }

  //Close Dir Command
  sceIoDclose (dfd);
  numberoffiles = i;

  //Pause for 0,2 seconds. (200 milliseconds)
  PauseVbl (20);

  //Filebrowser mainloop
  while (1)
    {

      DrawFullscreenWindow (Dic);
      findIcon ();
      GetUserInput ();

      if (numberoffiles > 32 * FBpage)
	{
	  FBmore = 1;
	}

      while (numberoffiles > i)
	{
	  if (i >= (32 * (FBpage - 1)) && i < (32 * FBpage))
	    {

	      //Get file extension
	      char *suffix = strrchr (iconname[i], '.');
	      //added 24th of dec           
	      char iconitem[i][13];
	      strncpy (iconitem[i], iconname[i], 6);
	      iconitem[i][6] = '\0';
	      PutText ((60 * IconPositionX - 46), (60 * IconPositionY + 6),
		       iconitem[i], FileBrowserTextC);
	      //added 24th of dec      

	      if (isdir[i] == 1)
		{
		  if (iconSelected.row == IconPositionX
		      && iconSelected.col == IconPositionY)
		    {
		      PutGFX (0, 0, 48, 48, Icon_Folder_Over,
			      (60 * IconPositionX - 48),
			      (60 * IconPositionY - 48 + 5));
		      PutTextFont (5, 260, DirectoryT, DirectoryC);
		      PutTextFont ((cursorPosition.x + 15), cursorPosition.y,
				   iconname[i], FileBrowserTextOverC);
		    }
		  else
		    {
		      PutGFX (0, 0, 48, 48, Icon_Folder,
			      (60 * IconPositionX - 48),
			      (60 * IconPositionY - 48 + 5));
		    }
		}
	      //No Suffix so Unknown
	      else if (!suffix)
		{
		  if (iconSelected.row == IconPositionX
		      && iconSelected.col == IconPositionY)
		    {
		      PutGFX (0, 0, 48, 48, Icon_Unknown_Over,
			      (60 * IconPositionX - 48),
			      (60 * IconPositionY - 48 + 5));
		      PutTextFont (5, 260, UnknownT, UnknownC);
		      PutTextFont ((cursorPosition.x + 15), cursorPosition.y,
				   iconname[i], FileBrowserTextOverC);
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
		      PutTextFont (5, 260, GraphicT, GraphicC);
		      PutTextFont ((cursorPosition.x + 15), cursorPosition.y,
				   iconname[i], FileBrowserTextOverC);
		    }
		  else
		    {
		      PutGFX (0, 0, 48, 48, Icon_GFX,
			      (60 * IconPositionX - 48),
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
		      PutTextFont (5, 260, MusicT, MusicC);
		      PutTextFont ((cursorPosition.x + 15), cursorPosition.y,
				   iconname[i], FileBrowserTextOverC);
		    }
		  else
		    {
		      PutGFX (0, 0, 48, 48, Icon_Audio,
			      (60 * IconPositionX - 48),
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
		      PutTextFont ((cursorPosition.x + 15), cursorPosition.y,
				   iconname[i], DesktopTextOverC);
		    }
		  else
		    {
		      PutGFX (0, 0, 48, 48, Icon_Video,
			      (60 * IconPositionX - 48),
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
		      PutTextFont (5, 260, ExecutableT, ExecutableC);
		      PutTextFont ((cursorPosition.x + 15), cursorPosition.y,
				   iconname[i], FileBrowserTextOverC);
		    }
		  else
		    {
		      PutGFX (0, 0, 48, 48, Icon_Eboot,
			      (60 * IconPositionX - 48),
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
		      PutTextFont ((cursorPosition.x + 15), cursorPosition.y,
				   iconname[i], DesktopTextOverC);
		    }
		  else
		    {
		      PutGFX (0, 0, 48, 48, Icon_Lua,
			      (60 * IconPositionX - 48),
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
		      PutGFX (0, 0, 48, 48, Icon_QuickLink_Over,
			      (60 * IconPositionX - 48),
			      (60 * IconPositionY - 48 + 5));
		      PutTextFont (5, 260, QuickLinkT, QuickLinkC);
		      PutTextFont ((cursorPosition.x + 15), cursorPosition.y,
				   iconname[i], FileBrowserTextOverC);
		    }
		  else
		    {
		      PutGFX (0, 0, 48, 48, Icon_QuickLink,
			      (60 * IconPositionX - 48),
			      (60 * IconPositionY - 48 + 5));
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
		      PutTextFont (5, 260, UnknownT, UnknownC);
		      PutTextFont ((cursorPosition.x + 15), cursorPosition.y,
				   iconname[i], FileBrowserTextOverC);
		    }
		  else
		    {
		      PutGFX (0, 0, 48, 48, Icon_Unknown,
			      (60 * IconPositionX - 48),
			      (60 * IconPositionY - 48 + 5));
		    }
		}


	      //If we're not displaying a rightclick menu...
	      if (FilebrowserRightclickActive != 1)
		{
		  if (pad.Buttons & PSP_CTRL_CONFIRM
		      && iconSelected.row == IconPositionX
		      && iconSelected.col == IconPositionY)
		    {
		      char buffer[200];

		      if (isdir[i] == 1)
			{
			  sprintf (Dic, "%s%s/", Dic, iconname[i]);
			  i = 0;
			  goto loo;
			  break;
			}
		      else
			{
			  sprintf (buffer, "%s%s", Dic, iconname[i]);
			  fbimager = 1;
			  strcpy (imageDic, Dic);
			  OpenFile (buffer);
			}
		    }

		  if (pad.Buttons & PSP_CTRL_BACK
		      && iconSelected.row == IconPositionX
		      && iconSelected.col == IconPositionY)
		    {
		      Init_RightClick_Icon_Filebrowser (cursorPosition.x,
							cursorPosition.y,
							Dic, iconname[i],
							isdir[i]);
		    }
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
	    }
	  i++;
	}


      //Exit
      if (pad.Buttons & PSP_CTRL_CONFIRM && cursorPosition.x > 465
	  && cursorPosition.x < 475 && cursorPosition.y > 3
	  && cursorPosition.y < 13)
	{
	  break;
	}
      //if(pad.Buttons & PSP_CTRL_TRIANGLE){
      //    break;
      //}

      //Back mouseover
      if (cursorPosition.x > 455 && cursorPosition.x < 480
	  && cursorPosition.y > 247 && cursorPosition.y < 272)
	{
	  PutGFX (0, 0, 25, 25, Back_Over, 455, 247);
	}
      else
	{
	  PutGFX (0, 0, 25, 25, Back, 455, 247);
	}

      //Back
      if (pad.Buttons & PSP_CTRL_CONFIRM && cursorPosition.x > 455
	  && cursorPosition.x < 480 && cursorPosition.y > 247
	  && cursorPosition.y < 272)
	{
	  FBpage = 1;
	  int a = 0;
	  int b = 0;
	  int c = 0;
	  char tmp[500];
	  if (strlen (Dic) > strlen ("ms0:/"))
	    {
	      for (a = strlen (Dic); a >= 0; a--)
		{
		  if (Dic[a] == '/')
		    {
		      b++;
		    }

		  if (b == 2)
		    {
		      break;
		    }

		  Dic[a] = NULL;
		}
	      i = 0;
	      goto loo;
	    }
	}
      //Back

      if (FBpage > 1)
	{
	  //Previous mouseover
	  if (cursorPosition.x > 190 && cursorPosition.x < 230
	      && cursorPosition.y > 250 && cursorPosition.y < 272)
	    {
	      PutGFX (0, 0, 40, 25, FBLeft, 190, 247);
	      PutText (5, 260, PreviousPageT, PreviousPageC);	//Displays the name of the item in the Start Menu
	    }
	  else
	    {
	      PutGFX (0, 0, 40, 25, FBLeft, 190, 247);
	    }

	  //Previous

	  if (pad.Buttons & PSP_CTRL_CONFIRM && cursorPosition.x > 190
	      && cursorPosition.x < 230 && cursorPosition.y > 250
	      && cursorPosition.y < 272 || pad.Buttons & PSP_CTRL_LEFT)
	    {
	      FBpage -= 1;
	      PauseVbl (15);
	    }
	}

      if (numberoffiles > 32 * FBpage)
	{
	  //Next mouseover
	  if (cursorPosition.x > 250 && cursorPosition.x < 490
	      && cursorPosition.y > 250 && cursorPosition.y < 272)
	    {
	      PutGFX (0, 0, 40, 25, FBRight, 250, 247);
	      PutText (5, 260, NextPageT, NextPageC);	//Displays the name of the item in the Start Menu                       
	    }
	  else
	    {
	      PutGFX (0, 0, 40, 25, FBRight, 250, 247);
	    }

	  //Next

	  if (pad.Buttons & PSP_CTRL_CONFIRM && cursorPosition.x > 250
	      && cursorPosition.x < 490 && cursorPosition.y > 250
	      && cursorPosition.y < 272 || pad.Buttons & PSP_CTRL_RIGHT)
	    {
	      FBpage += 1;
	      PauseVbl (15);
	    }
	}

      if (pad.Buttons & PSP_CTRL_SQUARE)
	{
	  FBpage = 1;
	  int a = 0;
	  int b = 0;
	  int c = 0;
	  char tmp[500];
	  if (strlen (Dic) > strlen ("ms0:/"))
	    {
	      for (a = strlen (Dic); a >= 0; a--)
		{
		  if (Dic[a] == '/')
		    {
		      b++;
		    }

		  if (b == 2)
		    {
		      break;
		    }

		  Dic[a] = NULL;
		}
	      i = 0;
	      goto loo;
	    }
	}

      //If a rightclickmenu is enables, display it.
      if (FilebrowserRightclickActive == 1)
	{
	  RightClick_Icon_Filebrowser ();
	}

      //Draw the cursor
      PutGFX (0, 0, 32, 32, cursor, cursorPosition.x, cursorPosition.y);
      PrintScreen ();

      IconPositionX = 1;
      IconPositionY = 1;
      i = 0;
    }

}

void
Toggle_Wallpapers (int mode)
{
  if (LR_Wallpapers_ran == 0)
    {
      int i = 0;
      int dfd;
      dfd = sceIoDopen ("ms0:/PSP-OSS/WALLPAPERS/");
      sceIoDread (dfd, &dir);
      sceIoDread (dfd, &dir);

      while (sceIoDread (dfd, &dir) > 0)
	{
	  //Make sure its a PNG
	  char *suffix = strrchr (strdup (dir.d_name), '.');
	  if (stricmp (suffix, ".png") == 0)
	    {
	    	free(LR_Wallpapers[i]);
	    	LR_Wallpapers[i] = NULL;
	      LR_Wallpapers[i] = strdup (dir.d_name);
	      i++;
	    }
	}

			
      //Close Dir Command
      frtd = 0;
      sceIoDclose (dfd);
      LR_Wallpapers_amount = i;
      PauseVbl (20);
    }

  //Next wallpaper
  if (mode == "R")
    {
      LR_Wallpapers_current += 1;

      if (LR_Wallpapers_amount == LR_Wallpapers_current)
	{
	  LR_Wallpapers_current = 0;
	}

      char buffer[200];
      sprintf (buffer, "ms0:/PSP-OSS/WALLPAPERS/%s",
	       LR_Wallpapers[LR_Wallpapers_current]);
	       
      SetWallpaper (buffer);
    }

  if (mode == "L")
    {
      LR_Wallpapers_current -= 1;

      if (LR_Wallpapers_current < 0)
	{
	  LR_Wallpapers_current = (LR_Wallpapers_amount - 1);
	}

      char buffer[200];
      sprintf (buffer, "ms0:/PSP-OSS/WALLPAPERS/%s",LR_Wallpapers[LR_Wallpapers_current]);
      SetWallpaper (buffer);
    }
}

void
Toggle_MP3 (int mode)
{
  if (LR_MUSIC_ran == 0)
    {
      int i = 0;
      int dfd;
      dfd = sceIoDopen (Audiofolder);
      sceIoDread (dfd, &dir);
      sceIoDread (dfd, &dir);

      while (sceIoDread (dfd, &dir) > 0)
	{
		  if (dir.d_stat.st_attr & FIO_SO_IFDIR)
			{
				free(isdir[i]);
	    	isdir[i] = NULL;
			  isdir[i] = 1;
			}

	  //Make sure its a mp3 or ogg
	  if (isdir[i] != 1)
		{			
	  	char *suffix = strrchr (strdup (dir.d_name), '.');
	  	if (stricmp (suffix, ".mp3") == 0 || stricmp (suffix, ".ogg") == 0)
	    	{
	    		free(LR_MUSIC[i]);
	    		LR_MUSIC[i] = NULL;
	     		LR_MUSIC[i] = strdup (dir.d_name);	      	
	     		i++;
				}
	  }	 
	}

      //Close Dir Command
      frtd = 0;
      sceIoDclose (dfd);
      LR_MUSIC_amount = i;
      PauseVbl (20);
    }

  //Next SONG
  if (mode == "R")
    {    	
      LR_MUSIC_current += 1;

      if (LR_MUSIC_amount == LR_MUSIC_current)
	{
	  LR_MUSIC_current = 0;
	}

      char buffer[200];
      sprintf (buffer, "%s%s",Audiofolder,LR_MUSIC[LR_MUSIC_current]);
      Audio_Stop();
      	  Audio_Play (buffer);
				  PauseVbl (1 * 60);
	       
    }

  if (mode == "L")
    {
      LR_MUSIC_current -= 1;

      if (LR_MUSIC_current < 0)
	{
	  LR_MUSIC_current = (LR_MUSIC_amount - 1);
	}

      char buffer[200];
      sprintf (buffer, "%s%s",Audiofolder,LR_MUSIC[LR_MUSIC_current]);
      Audio_Stop();
      	  Audio_Play (buffer);
				  PauseVbl (1 * 60);
    }
 
  if (mode == "SHUFFLE")
    {
	 // Thanks to Raphael for posting this information http://forums.ps2dev.org/viewtopic.php?t=4836
			SceKernelUtilsMt19937Context ctx;			
			sceKernelUtilsMt19937Init(&ctx, time(NULL));			

			u32 rand_val = sceKernelUtilsMt19937UInt(&ctx); 

			rand_val = 1 + rand_val % LR_MUSIC_amount; 

   		LR_MUSIC_current = rand_val;

      char buffer[200];
      sprintf (buffer, "%s%s",Audiofolder,LR_MUSIC[LR_MUSIC_current]);
      Audio_Stop();
      	  Audio_Play (buffer);
				  PauseVbl (1 * 60);
    }    
}

