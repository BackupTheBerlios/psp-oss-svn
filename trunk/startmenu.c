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
#include "startmenu.h"
int MenuPositionX = 1;		//Used to defind the columns that will be used for the start menu item
int MenuPositionY;		//Used to set the Start Menu to star in the second row
int stopmenu = 0;		//used to kill the start menu
int stopmenu2;
int fourcolumns;		//This will be used to move the start menu over to the left if there are 4 columns
int empty;			//This will be used to display information if a folder is empty
int settings;			//system menu
int substart = 0;
int substartdpad = 0;
int DPad_PositionY;
int DPad_PositionX;
int DPad_Position;
int startcounter;
int subdpad = 0;
int right = 0;
int smpage;
int more;
int musicmenu;

//Select menu is very important.  It is used to define which folder the start menu reads from. e.g selectmenu = "ms0:/PSP-OSS/APPS/"; 
char *selectmenu;

void
StartMenu ()
{

  DesktopIconsActive = 0;
  PauseVbl (10);
  stopmenu = 0;
  substart = 0;
  while (1)
    {

      GetUserInput ();

      DoActiveDesktop ();
      PutGFX (0, 0, 70, 15, Start_menu_Over, 0, 257);
      PutGFX (0, 0, 70, 15, Start_menu_Open, 0, 257);
      PutGFX (0, 0, 70, 10, Start_Menu_Top, 0, 177);
      PutGFX (0, 0, 70, 10, Start_Menu_Body, 0, 187);
      PutGFX (0, 0, 70, 10, Start_Menu_Body, 0, 197);
      PutGFX (0, 0, 70, 10, Start_Menu_Body, 0, 207);
      PutGFX (0, 0, 70, 10, Start_Menu_Body, 0, 217);
      PutGFX (0, 0, 70, 10, Start_Menu_Body, 0, 227);
      PutGFX (0, 0, 70, 10, Start_Menu_Body, 0, 237);
      PutGFX (0, 0, 70, 10, Start_Menu_Body, 0, 247);

      Startmenulistover ();
      Startmenulist ();

      if (smpage > 1 || musicmenu == 1)
	{
	  StartListMenu ();
	}


      PutGFX (0, 0, 32, 32, cursor, cursorPosition.x, cursorPosition.y);
      PrintScreen ();

      //Allows a user to slect an icon using the dpad.
      if (pad.Buttons & PSP_CTRL_DOWN)
	{
	  cursorPosition.x = 35;
	  DPad_Position++;
	  if (DPad_Position > 7)
	    {
	      DPad_Position = 7;
	    }
	  if (DPad_Position == 1)
	    {
	      cursorPosition.y = 190;
	    }
	  else if (DPad_Position == 2)
	    {
	      cursorPosition.y = 200;
	    }	    
	  else if (DPad_Position == 3)
	    {
	      cursorPosition.y = 210;
	    }
	  else if (DPad_Position == 4)
	    {
	      cursorPosition.y = 220;
	    }
	  else if (DPad_Position == 5)
	    {
	      cursorPosition.y = 230;
	    }
	  else if (DPad_Position == 6)
	    {
	      cursorPosition.y = 240;
	    }
	  else if (DPad_Position == 7)
	    {
	      cursorPosition.y = 250;
	    }

	  PauseVbl (10);
	}

      if (pad.Buttons & PSP_CTRL_UP)
	{
	  cursorPosition.x = 35;
	  DPad_Position--;
	  if (DPad_Position < 1)
	    {
	      DPad_Position = 1;
	    }
	  if (DPad_Position == 1)
	    {
	      cursorPosition.y = 190;
	    }
	  else if (DPad_Position == 2)
	    {
	      cursorPosition.y = 200;
	    }
	  else if (DPad_Position == 3)
	    {
	      cursorPosition.y = 210;
	    }
	  else if (DPad_Position == 4)
	    {
	      cursorPosition.y = 220;
	    }
	  else if (DPad_Position == 5)
	    {
	      cursorPosition.y = 230;
	    }
	  else if (DPad_Position == 6)
	    {
	      cursorPosition.y = 240;
	    }
	  else if (DPad_Position == 7)
	    {
	      cursorPosition.y = 250;
	    }
	  PauseVbl (10);
	}

      if (stopmenu2 == 1)
	{
	  stopmenu = 1;
	  stopmenu2 = 0;
	  break;
	}
      if (pad.Buttons & PSP_CTRL_START)
	{
	  DesktopIconsActive = 1;
	  break;
	}
      if (cursorPosition.x > 71 || cursorPosition.y < 187)
	{
	  if (pad.Buttons & PSP_CTRL_CONFIRM || pad.Buttons & PSP_CTRL_BACK)
	    {
	      DesktopIconsActive = 1;
	      break;
	    }
	}

    }


}

//Mechanism that finds which Start Menu item the cursor is over.
void
findStartMenu ()
{
  DesktopIconsActive = 0;

  //Defines the Rows
  //fourcolums will adjust the colums appropriately when there are 4 colums on the sceen.
  //the -20 is there since everything in the start menu has been moved to the left by 20 pixels  
  if (cursorPosition.x > (menuXSize * 0) - fourcolumns - 20
      && cursorPosition.x < (menuXSize * 1) - fourcolumns - 20)
    {
      MenuSelected.row1 = 0;
    }

  else if (cursorPosition.x > (menuXSize * 1) - fourcolumns - 20
	   && cursorPosition.x < (menuXSize * 2) - fourcolumns - 20)
    {
      MenuSelected.row1 = 1;
    }

  else if (cursorPosition.x > (menuXSize * 2) - fourcolumns - 20
	   && cursorPosition.x < (menuXSize * 3) - fourcolumns - 20)
    {
      MenuSelected.row1 = 2;
    }

  else if (cursorPosition.x > (menuXSize * 3) - fourcolumns - 20
	   && cursorPosition.x < (menuXSize * 4) - fourcolumns - 20)
    {
      MenuSelected.row1 = 3;
    }

  else if (cursorPosition.x > (menuXSize * 4) - fourcolumns - 20
	   && cursorPosition.x < (menuXSize * 5) - fourcolumns - 20)
    {
      MenuSelected.row1 = 4;
    }

  else if (cursorPosition.x > (menuXSize * 5) - fourcolumns - 20
	   && cursorPosition.x < (menuXSize * 6) - fourcolumns - 20)
    {
      MenuSelected.row1 = 5;
    }

  //Defines the Columns
  if ((cursorPosition.y) > (menuYSize * 0)
      && (cursorPosition.y) < (menuYSize * 1))
    {
      MenuSelected.col1 = 0;
    }

  else if ((cursorPosition.y) > (menuYSize * 1)
	   && (cursorPosition.y) < (menuYSize * 2))
    {
      MenuSelected.col1 = 1;
    }

  else if ((cursorPosition.y) > (menuYSize * 2)
	   && (cursorPosition.y) < (menuYSize * 3))
    {
      MenuSelected.col1 = 2;
    }

  else if ((cursorPosition.y) > (menuYSize * 3)
	   && (cursorPosition.y) < (menuYSize * 4))
    {
      MenuSelected.col1 = 3;
    }

  else if ((cursorPosition.y) > (menuYSize * 4)
	   && (cursorPosition.y) < (menuYSize * 5))
    {
      MenuSelected.col1 = 4;
    }

  else if ((cursorPosition.y) > (menuYSize * 5)
	   && (cursorPosition.y) < (menuYSize * 6))
    {
      MenuSelected.col1 = 5;
    }

  else if ((cursorPosition.y) > (menuYSize * 6)
	   && (cursorPosition.y) < (menuYSize * 7))
    {
      MenuSelected.col1 = 6;
    }

  else if ((cursorPosition.y) > (menuYSize * 7)
	   && (cursorPosition.y) < (menuYSize * 8))
    {
      MenuSelected.col1 = 7;
    }

  else if ((cursorPosition.y) > (menuYSize * 8)
	   && (cursorPosition.y) < (menuYSize * 9))
    {
      MenuSelected.col1 = 8;
    }

  else if ((cursorPosition.y) > (menuYSize * 9)
	   && (cursorPosition.y) < (menuYSize * 10))
    {
      MenuSelected.col1 = 9;
    }

  else if ((cursorPosition.y) > (menuYSize * 10)
	   && (cursorPosition.y) < (menuYSize * 11))
    {
      MenuSelected.col1 = 10;
    }

  else if ((cursorPosition.y) > (menuYSize * 11)
	   && (cursorPosition.y) < (menuYSize * 12))
    {
      MenuSelected.col1 = 11;
    }

  else if ((cursorPosition.y) > (menuYSize * 12)
	   && (cursorPosition.y) < (menuYSize * 13))
    {
      MenuSelected.col1 = 12;
    }

  else if ((cursorPosition.y) > (menuYSize * 13)
	   && (cursorPosition.y) < (menuYSize * 14))
    {
      MenuSelected.col1 = 13;
    }

  else if ((cursorPosition.y) > (menuYSize * 14)
	   && (cursorPosition.y) < (menuYSize * 15))
    {
      MenuSelected.col1 = 14;
    }

  else if ((cursorPosition.y) > (menuYSize * 15)
	   && (cursorPosition.y) < (menuYSize * 16))
    {
      MenuSelected.col1 = 15;
    }

  else if ((cursorPosition.y) > (menuYSize * 16)
	   && (cursorPosition.y) < (menuYSize * 17))
    {
      MenuSelected.col1 = 16;
    }

  else if ((cursorPosition.y) > (menuYSize * 17)
	   && (cursorPosition.y) < (menuYSize * 18))
    {
      MenuSelected.col1 = 17;
    }

  else if ((cursorPosition.y) > (menuYSize * 18)
	   && (cursorPosition.y) < (menuYSize * 19))
    {
      MenuSelected.col1 = 18;
    }

  else if ((cursorPosition.y) > (menuYSize * 19)
	   && (cursorPosition.y) < (menuYSize * 20))
    {
      MenuSelected.col1 = 19;
    }

}

//The Following code is used to create the Dynamic Start Menu.  Up too 64 items can be shown on sceen but it is not recommended
//Anything beginning with SubMenu is used in the creation of the dynamic Start menu.

void
StartListMenu ()
{
  int i = 0;
  fourcolumns = 0;		//Useful for when there are 4 colums
  empty = 0;
  startcounter = 1;
  DesktopIconsActive = 0;

  //The following code reads the directory selected earlier by selectmenu.
  int dfd = sceIoDopen (selectmenu);
  sceIoDread (dfd, &dir);
  sceIoDread (dfd, &dir);

  while (sceIoDread (dfd, &dir) > 0)
    {

   		free(startitemname[i]);
   		startitemname[i] = NULL;    	
      startitemname[i] = strdup (dir.d_name);

      //This code identifys if an item is a directory or not.
      if (dir.d_stat.st_attr & FIO_SO_IFDIR)
	{
	  isdir[i] = 1;

	  //If it's a % folder, dont list it
	  char *suffix = strrchr (startitemname[i], '%');

	  if (suffix)
	    {
	      i--;
	    }

	  else if (strcmp (startitemname[i], "PSP-OSS") == 0)
	    {
	      i--;
	    }

	}
      else
	{
	  isdir[i] = 0;
	}

      i++;
    }

  //Close Dir Command
  sceIoDclose (dfd);
  numberoffilesinlist = i;
  PauseVbl (20);

  while (1)
    {

      if (stopmenu == 1)
	{
	  mstart = 0;
	  smpage = 1;
	  fourcolumns = 0;
	  stopmenu = 0;
	  break;
	}

      //This detects if there are going to be more then 4 columns and helps adjust the x position of the start menu
      if (numberoffilesinlist <= 15 * smpage)
	{
	  subdpad = numberoffilesinlist + 1;
	  startcounter = 1;
	  more = 0;
	}
      else if (numberoffilesinlist <= 30 * smpage)
	{
	  startcounter = 2;
	  more = 0;
	}
      else if (numberoffilesinlist <= 45 * smpage)
	{
	  startcounter = 3;
	  more = 0;
	}
      else if (numberoffilesinlist > 45 * smpage)
	{
	  fourcolumns = 31;
	  startcounter = 4;
	  if (numberoffilesinlist > 59 * smpage)
	    {
	      more = 1;
	    }
	}

      if (numberoffilesinlist >= 16)
	{
	  subdpad = 16;
	}

      //The following code displays all pngs required for the start menu on the sceen
      DoActiveDesktop ();
      PutGFX (0, 0, 70, 15, Start_menu_Over, 0, 257);
      PutGFX (0, 0, 70, 15, Start_menu_Open, 0, 257);
      PutGFX (0, 0, 70, 10, Start_Menu_Top, 0, 177);
      PutGFX (0, 0, 70, 10, Start_Menu_Body, 0, 187);
      PutGFX (0, 0, 70, 10, Start_Menu_Body, 0, 197);
      PutGFX (0, 0, 70, 10, Start_Menu_Body, 0, 207);
      PutGFX (0, 0, 70, 10, Start_Menu_Body, 0, 217);
      PutGFX (0, 0, 70, 10, Start_Menu_Body, 0, 227);
      PutGFX (0, 0, 70, 10, Start_Menu_Body, 0, 237);
      PutGFX (0, 0, 70, 10, Start_Menu_Body, 0, 247);
		  PutText (5, 187, BrowseT, BrowseC);
		  PutText (5, 197, GamesT, GamesC);
		  PutText (5, 207, MusicT, MusicC);
		  PutText (5, 217, "Videos", MusicC);
      PutText (5, 227, PicturesT, PicturesC);
      PutText (5, 237, SystemT, SystemC);
      PutText (5, 247, QuitT, QuitC);

      findStartMenu ();
      GetUserInput ();
      DesktopIconsActive = 0;



      //The following code is used to create a start menu.  There are 4 types of start menu's that can be created depending on the size required.
      if (selectmenu == "ms0:/NOTREALFOROURUSEONLY")
	{			//checks if the system folder is being created
	  MenuPositionY = (16 - settings);	//Works out how many spaces will be required to include the two system icons
	  substartdpad = (16 - settings);
	  subdpad = (1 + settings);
	}
      else if (numberoffilesinlist >= 1 && numberoffilesinlist <= 15)
	{
	  MenuPositionY = (16 - numberoffilesinlist);	//Works out how many sapaces will be required if there is only one column
	  substartdpad = (16 - numberoffilesinlist);
	}
      else if (numberoffilesinlist >= 1)	//checks that there are more then 16 files which would create more then one column
	{
	  MenuPositionY = (1);
	  substartdpad = (1);
	}
      else
	{			//Used to create the empty folder display
	  MenuPositionY = 14;
	  empty = 1;
	}


      Startmenulistover ();

      //The following creates the top left corner of the start menu         
      PutGFX (0, 0, 10, 10, SubMenuTopLeft, (100 * MenuPositionX - fourcolumns - 30), (15 * MenuPositionY - 3));	//Sub Menu top left corner placed here because it is always in the same place.
      PutGFX (0, 0, 100, 10, SubMenuTop, (100 * MenuPositionX - fourcolumns - 20), (15 * MenuPositionY - 3));	//Sub Menu top of the first column placed here because it is always in the same place.

      //Checks thats there are more filesnames to be added to the start menu
      while (numberoffilesinlist > i)
	{
	  //The code below ensures that only 4 colums are created as no more will fit on the sceen
	  if (i >= (60 * (smpage - 1)) - 1 && i < (60 * smpage))
	    {

	      //this code checks that we are up to the 16th item and starts the next column.
	      if (MenuPositionY == 16)
		{
		  if (MenuPositionX != 4)	// used to ensure that a 5th column is not created.
		    {
		      MenuPositionX += 1;	//Is used to start items being displayed on the next column
		      MenuPositionY = 1;	//This resets where items start to be displayed on the sceen.
		      PutGFX (0, 0, 100, 10, SubMenuTop, (100 * MenuPositionX - fourcolumns - 20), (15 * MenuPositionY - 3));	//Places the SubMenuTop image above the next column.
		    }
		}

	      PutGFX (0, 0, 100, 15, SubMenuMiddle, (100 * MenuPositionX - fourcolumns - 20), (15 * MenuPositionY + 7));	//SubMenuMiddle is the image that both the icon and the text of an item in the start menu is dispayed on.                                                  

	      //Get file extension and limit the size of the filename in the start menu.
	      char *suffix = strrchr (startitemname[i], '.');
	      char Startitem[i][13];
	      int size;
	      size = strlen (startitemname[i]);

	      if (isdir[i] != 1)
		{
		  if (size <= 12)
		    {
		      strncpy (Startitem[i], startitemname[i], 12);
		      Startitem[i][12] = '\0';
		    }
		  else
		    {
		      strncpy (Startitem[i], startitemname[i], 8);
		      Startitem[i][8] = '\0';
		      strncat (Startitem[i], suffix, 4);
		    }
		}
	      else
		{
		  strncpy (Startitem[i], startitemname[i], 12);
		  Startitem[i][12] = '\0';
		}

	      PutText ((100 * MenuPositionX - fourcolumns - 17), (15 * MenuPositionY + 9), Startitem[i], StartSubMenuC);	//Displays the name of the item in the Start Menu
	      //Used to check is an item is a Directory
	      if (isdir[i] == 1)
		{
		  //I am only going to comment this menu item the rest use the exact same code.
		  //This if Statement is used to check if the mouse cursor is over an item and then highlights the item with an image.
		  if (MenuSelected.row1 == MenuPositionX
		      && MenuSelected.col1 == MenuPositionY)
		    {
		      PutGFX (0, 0, 100, 15, SubMenuSelect, (100 * MenuPositionX - fourcolumns - 19), (15 * MenuPositionY + 7));	//Puts an overlay over the Text if the mouse cursor is over the item.                 
		      PutText ((100 * MenuPositionX - fourcolumns - 17), (15 * MenuPositionY + 9), Startitem[i], StartSubMenuOverC);	//Displays the name of the item in the Start Menu
		      if (selectmenu == "ms0:/PSP/GAME/")
			{
			  PutText (380, 260, ExecutableT, StartSubMenuTypeC);	//Display the type of file type in the Status Bar e.g Executable
			}
		      else
			{
			  PutText (380, 260, DirectoryT, StartSubMenuTypeC);	//Display the type of file type in the Status Bar e.g Executable
			}
		    }

		}
		
	      //No Suffix so Unknown
	      else if (!suffix)
		{
		  if (MenuSelected.row1 == MenuPositionX
		      && MenuSelected.col1 == MenuPositionY)
		    {
		      PutGFX (0, 0, 100, 15, SubMenuSelect,
			      (100 * MenuPositionX - fourcolumns - 19),
			      (15 * MenuPositionY + 7));
		      PutText ((100 * MenuPositionX - fourcolumns - 17),
			       (15 * MenuPositionY + 9), Startitem[i],
			       StartSubMenuOverC);
		      PutText (380, 260, UnknownT, StartSubMenuTypeC);
		    }
		}				

	      //Used to check is an item is an Image
	      else if (stricmp (suffix, ".png") == 0
		       || stricmp (suffix, ".jpg") == 0
		       || stricmp (suffix, ".jpeg") == 0)
		{
		  if (MenuSelected.row1 == MenuPositionX
		      && MenuSelected.col1 == MenuPositionY)
		    {
		      PutGFX (0, 0, 100, 15, SubMenuSelect,
			      (100 * MenuPositionX - fourcolumns - 19),
			      (15 * MenuPositionY + 7));
		      PutText ((100 * MenuPositionX - fourcolumns - 17),
			       (15 * MenuPositionY + 9), Startitem[i],
			       StartSubMenuOverC);
		      PutText (380, 260, GraphicT, StartSubMenuTypeC);
		    }

		}


	      //Used to check is an item is an Audio file
	      else if (stricmp (suffix, ".mp3") == 0
		       || stricmp (suffix, ".ogg") == 0)
		{
		  if (MenuSelected.row1 == MenuPositionX
		      && MenuSelected.col1 == MenuPositionY)
		    {
		      PutGFX (0, 0, 100, 15, SubMenuSelect,
			      (100 * MenuPositionX - fourcolumns - 19),
			      (15 * MenuPositionY + 7));
		      PutText ((100 * MenuPositionX - fourcolumns - 17),
			       (15 * MenuPositionY + 9), Startitem[i],
			       StartSubMenuOverC);
		      PutText (380, 260, MusicT, StartSubMenuTypeC);
		    }

		}
         //Used to check is an item is an Video file
	      else if (stricmp (suffix, ".pmp") == 0
		       || stricmp (suffix, ".pos") == 0)
		{
		  if (MenuSelected.row1 == MenuPositionX
		      && MenuSelected.col1 == MenuPositionY)
		    {
		      PutGFX (0, 0, 100, 15, SubMenuSelect,
			      (100 * MenuPositionX - fourcolumns - 19),
			      (15 * MenuPositionY + 7));
		      PutText ((100 * MenuPositionX - fourcolumns - 17),
			       (15 * MenuPositionY + 9), Startitem[i],
			       StartSubMenuOverC);
		      PutText (380, 260, MusicT, StartSubMenuTypeC);
		    }

		}

	      //Used to check is an item is a Application/game
	      else if (stricmp (suffix, ".PBP") == 0
		       || stricmp (suffix, ".elf") == 0)
		{
		  if (MenuSelected.row1 == MenuPositionX
		      && MenuSelected.col1 == MenuPositionY)
		    {
		      PutGFX (0, 0, 100, 15, SubMenuSelect,
			      (100 * MenuPositionX - fourcolumns - 19),
			      (15 * MenuPositionY + 7));
		      PutText ((100 * MenuPositionX - fourcolumns - 17),
			       (15 * MenuPositionY + 9), Startitem[i],
			       StartSubMenuOverC);
		      PutText (380, 260, ExecutableT, StartSubMenuTypeC);
		    }
		}
	      
	      //Lua Apps
          else if (stricmp (suffix, ".lua") == 0)
		{
		  if (MenuSelected.row1 == MenuPositionX
		      && MenuSelected.col1 == MenuPositionY)
		    {
		      PutGFX (0, 0, 100, 15, SubMenuSelect,
			      (100 * MenuPositionX - fourcolumns - 19),
			      (15 * MenuPositionY + 7));
		      PutText ((100 * MenuPositionX - fourcolumns - 17),
			       (15 * MenuPositionY + 9), Startitem[i],
			       StartSubMenuOverC);
		      PutText (380, 260, ExecutableT, StartSubMenuTypeC);
		    }
		}
	      //Used to check is an item is a Shortcut
	      else if (stricmp (suffix, ".ql") == 0
		       || stricmp (suffix, ".pol") == 0)
		{
		  if (MenuSelected.row1 == MenuPositionX
		      && MenuSelected.col1 == MenuPositionY)
		    {
		      PutGFX (0, 0, 100, 15, SubMenuSelect,
			      (100 * MenuPositionX - fourcolumns - 19),
			      (15 * MenuPositionY + 7));
		      PutText ((100 * MenuPositionX - fourcolumns - 17),
			       (15 * MenuPositionY + 9), Startitem[i],
			       StartSubMenuOverC);
		      PutText (380, 260, QuickLinkT, StartSubMenuTypeC);
		    }

		}

	      //Unknown files
	      else
		{
		  if (MenuSelected.row1 == MenuPositionX
		      && MenuSelected.col1 == MenuPositionY)
		    {
		      PutGFX (0, 0, 100, 15, SubMenuSelect,
			      (100 * MenuPositionX - fourcolumns - 19),
			      (15 * MenuPositionY + 7));
		      PutText ((100 * MenuPositionX - fourcolumns - 17),
			       (15 * MenuPositionY + 9), Startitem[i],
			       StartSubMenuOverC);
		      PutText (380, 260, UnknownT, StartSubMenuTypeC);
		    }
		}


	      if (more == 1)
		{
		  if (pad.Buttons & PSP_CTRL_CONFIRM && MenuSelected.row1 == 4
		      && MenuSelected.col1 == 15)
		    {
		      smpage += 1;
		      StartMenu ();
		    }
		}

	      //If we're not displaying a rightclick menu...                                                                                  
	      if (FilebrowserRightclickActive != 1)
		{
		  if (mstart == 1)	//mstart was added in so menu items could not be cliked if the 
		    {
		      //The Following is used to check if the mouse cursor is over an item and then exectute it.
		      if (pad.Buttons & PSP_CTRL_CONFIRM
			  && MenuSelected.row1 == MenuPositionX
			  && MenuSelected.col1 == MenuPositionY)
			{
			  char buffer[200];
			  //If the Folder is a directory it will open it up in the file browser.
			  if (isdir[i] == 1)
			    {
			      if (selectmenu == "ms0:/PSP/GAME/")
				{
				  stopmenu = 1;
				  musicmenu = 0;
				  sprintf (buffer, "%s%s/EBOOT.PBP", selectmenu, startitemname[i]);	//Uncomment these lines to have EBOOTS lunch from inside folders.  Comment the two lines above
				  ELF_Run (buffer);
				}
			      else if (selectmenu == "ms0:/PSP/MUSIC/" || selectmenu == "ms0:/PSP/VIDEO/" )
			      {
			    stopmenu = 0;
				  sprintf (buffer, "%s%s/", selectmenu, startitemname[i]);	//Uncomment these lines to have EBOOTS lunch from inside folders.  Comment the two lines above
				  selectmenu = buffer;
				  musicmenu = 1;
				  StartMenu ();
			      }
			      else
				{
				  DesktopIconsActive = 1;
				  stopmenu = 1;
				  musicmenu = 0;
				  sprintf (buffer, "%s%s/", selectmenu, startitemname[i]);	//This line works out the directory and folder name e.g ms0:/PSP-OSS/GAMES/
				  BrowseDirectory (buffer);	//This line lunches the file Browser                              
				}
			    }
			  //If the folder is not a directory it will try to open it.
			  else
			    {
			      DesktopIconsActive = 1;
			      musicmenu = 0;
			      sprintf (buffer, "%s%s", selectmenu, startitemname[i]);	//This line works out the directory and item name e.g ms0:/PSP-OSS/WALLPAPER/XWING.PNG
			      OpenFile (buffer);	//Sends the File to be opend by the appropriate app
			      stopmenu = 1;
			    }
			}

		      if (pad.Buttons & PSP_CTRL_BACK
			  && MenuSelected.row1 == MenuPositionX
			  && MenuSelected.col1 == MenuPositionY)
			{
			  if (cursorPosition.y > 200)
			    {
			      Init_RightClick_Icon_Filebrowser
				(cursorPosition.x, cursorPosition.y - 60,
				 selectmenu, startitemname[i]), isdir[i];
			    }
			  else
			    {
			      Init_RightClick_Icon_Filebrowser
				(cursorPosition.x, cursorPosition.y,
				 selectmenu, startitemname[i]);
			    }
			}
		    }
		}


	      //The following checks that the first column is being created and then displays the Left Side of the start menu on the sceen next to each item.
	      if (MenuPositionX == 1)
		{
		  PutGFX (0, 0, 10, 15, SubMenuSideLeft, (100 * MenuPositionX - fourcolumns - 30), (15 * MenuPositionY + 7));	//SubMenuSideLeft is Repeated down the left side of the Start Menu
		}

	      //The Following Code is used to ensure only 15 items are places on the sceen in one column. 
	      if (MenuPositionY >= 15)
		{
		  //The following checks that the first column is being created and then displays the bottom left corner of the start menu on the sceen            
		  if (MenuPositionX == 1)
		    {
		      PutGFX (0, 0, 10, 10, SubMenuBottomLeft, (100 * MenuPositionX - fourcolumns - 30), (15 * MenuPositionY + 22));	//SubMenuBottomleft is only displayed in the bottom left corner of the start menu.
		    }
		  // The following draws the bottom and bottom right parts of the skin in the start menu if a second column is to be created.
		  PutGFX (0, 0, 100, 10, SubMenuBottom, (100 * MenuPositionX - fourcolumns - 20), (15 * MenuPositionY + 22));	//Used to display the image beneith the start menu. Give the user some room to edit it.
		  PutGFX (0, 0, 10, 15, SubMenuSideRight, (100 * MenuPositionX - fourcolumns + 80), (15 * MenuPositionY + 7));	//SubMenuSideRight is Repeated down the right side of the Start Menu
		  MenuPositionY += 1;	//Starts the next column                                                                                                      
		}

	      else
		{
		  if (numberoffilesinlist - i <= 15 || i >= 45)	//Checks to see if the last column is being created and adds the right side of the start menu skin
		    {
		      PutGFX (0, 0, 10, 15, SubMenuSideRight, (100 * MenuPositionX - fourcolumns + 80), (15 * MenuPositionY + 7));	//SubMenuSideRight is Repeated down the right side of the Start Menu
		    }
		  MenuPositionY += 1;	//Adds one to the row for the next item to be placed.
		}
	    }
	  if (i == (60 * smpage))
	    {
	      if (MenuSelected.row1 == 4 && MenuSelected.col1 == 15)
		{		//Cursor is over the exit icon
		  PutGFX (0, 0, 100, 15, SubMenuMiddle, (100 * 4 - fourcolumns - 20), (15 * 15 + 7));	//SubMenuMiddle is the image that both the icon and the text of an item in the start menu is dispayed on.
		  PutGFX (0, 0, 100, 15, SubMenuSelect, (100 * 4 - fourcolumns - 19), (15 * 15 + 7));	//Puts an overlay over the Text if the mouse cursor is over the item.     
		  PutText ((100 * 4 - fourcolumns - 10), (15 * 15 + 9), MoreT, StartSubMenuOverC);	//Displays the name of the item in the Start Menu
		  PutText (380, 260, MoreT, StartSubMenuTypeC);	//Display the type of file in the Status Bar e.g Executable
		}
	      else
		{
		  PutGFX (0, 0, 100, 15, SubMenuMiddle, (100 * 4 - fourcolumns - 20), (15 * 15 + 7));	//SubMenuMiddle is the image that both the icon and the text of an item in the start menu is dispayed on.
		  PutText ((100 * 4 - fourcolumns - 10), (15 * 15 + 9), MoreT, StartSubMenuC);	//Displays the name of the item in the Start Menu              
		}
	    }
	  i++;
	}

      //The code below ensures that only 4 colums are created as no more will fit on the sceen

      //The following is used to fill in the blank positions in the last column.  So the start menu looks even
      while (MenuPositionY < 16)
	{
	  //The following checks that the first column is being created and then displays the Left Side of the start menu on the sceen next to each empty space.
	  if (MenuPositionX == 1)
	    {
	      PutGFX (0, 0, 10, 15, SubMenuSideLeft, (100 * MenuPositionX - fourcolumns - 30), (15 * MenuPositionY + 7));	//SubMenuSideLeft is Repeated down the left side of the Start Menu
	    }
	  if (MenuPositionY > 14)
	    {
	      //The following checks that the first column is being created and then displays the bottom left corner of the start menu on the sceen            
	      if (MenuPositionX == 1)
		{
		  PutGFX (0, 0, 10, 10, SubMenuBottomLeft, (100 * MenuPositionX - fourcolumns - 30), (15 * MenuPositionY + 22));	//SubMenuBottomleft is only displayed in the bottom left corner of the start menu.
		}
	    }

	  //These two lines finish up the the job if more then one column has been created but there are not enough items
	  if (i < 60 * smpage)
	    {
	      PutGFX (0, 0, 100, 15, SubMenuMiddle, (100 * MenuPositionX - fourcolumns - 20), (15 * MenuPositionY + 7));	//SubMenuMiddle is blank for these rows.
	    }
	  PutGFX (0, 0, 10, 15, SubMenuSideRight, (100 * MenuPositionX - fourcolumns + 80), (15 * MenuPositionY + 7));	//SubMenuSideRight is Repeated down the right side of the Start Menu

	  //The following checks if the settings menu is being created.  If it is then extra options are displayed on the start menu.
	  if (selectmenu == "ms0:/NOTREALFOROURUSEONLY")
	    {
	      drawSettings ();
	    }

	  else
	    {
	      MenuPositionY += 1;
	    }
	  i++;
	}

      //Fixed
      //The Following displays the botoms left corner of the start menu if the folder is empty
      if (MenuPositionX == 1)
	{
	  PutGFX (0, 0, 10, 10, SubMenuBottomLeft, (100 * MenuPositionX - fourcolumns - 30), (15 * MenuPositionY + 7));	//Sub Menu Bottom Left should always end up in the same spot.
	}

      //The following places both the bottom image and the bottom right corner at the bottom of the last column
      PutGFX (0, 0, 100, 10, SubMenuBottom,
	      (100 * MenuPositionX - fourcolumns - 20),
	      (15 * MenuPositionY + 7));
      PutGFX (0, 0, 10, 10, SubMenuBottomRight,
	      (100 * MenuPositionX - fourcolumns + 80),
	      (15 * MenuPositionY + 7));

      //This code works out where the top right corner of the start menu is
      //Either its down the sceen in the first column if there are less then 16 items
      if (selectmenu == "ms0:/NOTREALFOROURUSEONLY")	//checks if the system folder is being made
	{
	  MenuPositionY = (16 - settings);	//Works out how many sapaces will be required to include the two other icons
	  PutGFX (0, 0, 10, 10, SubMenuTopRight, (100 * MenuPositionX - fourcolumns + 80), (15 * MenuPositionY - 3));	//Places the top right hand corner in the first column
	}

      else if (empty == 1)	//Places the top right corner of the start menu if the folder is empty
	{
	  MenuPositionY = 14;
	  PutGFX (0, 0, 10, 10, SubMenuTopRight, (100 * MenuPositionX - fourcolumns + 80), (15 * MenuPositionY - 3));	//Places the top right hand corner in the first column
	}

      else if (numberoffilesinlist <= 15)
	{
	  MenuPositionY = (16 - numberoffilesinlist);
	  PutGFX (0, 0, 10, 10, SubMenuTopRight, (100 * MenuPositionX - fourcolumns + 80), (15 * MenuPositionY - 3));	//Places the top right hand corner in the first column
	}

      //The places the Top Right hand corner at the top right of the last column if there is more then one column
      else
	{
	  MenuPositionY = 1;
	  PutGFX (0, 0, 10, 10, SubMenuTopRight, (100 * MenuPositionX - fourcolumns + 80), (15 * MenuPositionY - 3));	//Places the top right hand corner in the last column of the start menu
	}

      //No files in list
      if (empty == 1)
	{
	  PutText ((100 * 1 - fourcolumns - 6), (15 * 14 + 9), EmptyT, StartSubMenuEmptyC);	//Displays the name of the item in the Start Menu       
	  PutText ((100 * 1 - fourcolumns - 6), (15 * 15 + 9), DirectoryT, StartSubMenuEmptyC);	//Displays the name of the item in the Start Menu   
	}

      if (FilebrowserRightclickActive != 1)
	{
	  //Closes the start menu           
	  if (pad.Buttons & PSP_CTRL_CONFIRM || pad.Buttons & PSP_CTRL_BACK)
	    {
	      //uses to close the start menu if the cross is not pressed on an icon
	      if (cursorPosition.x < 80 - fourcolumns
		  && cursorPosition.y < 180)
		{
		  //mstart required to disable the start menu
		  mstart = 0;
		  fourcolumns = 0;
		  DesktopIconsActive = 1;
		  stopmenu = 1;
		  musicmenu = 0;
		  break;
		}
	      else if (cursorPosition.x > (MenuSelected.row1 + startcounter))
		{
		  //mstart required to disable the start menu
		  mstart = 0;
		  fourcolumns = 0;
		  stopmenu = 1;
		  musicmenu = 0;
		  break;
		}
	    }
	  /*used to close the start menu if the triangle button is pressed
	     if(pad.Buttons & PSP_CTRL_TRIANGLE)
	     {
	     mstart = 0;
	     fourcolumns = 0;
	     DesktopIconsActive=1;
	     break;
	     }
	   */

	  //Startmenu Break
	  if (pad.Buttons & PSP_CTRL_START)
	    {
	      mstart = 0;
	      fourcolumns = 0;
	      DesktopIconsActive = 1;
	      musicmenu = 0;
	      break;
	    }
	}

      //If a rightclickmenu is enables, display it.
      if (FilebrowserRightclickActive == 1)
	{
	  RightClick_Icon_Filebrowser ();
	}

      //Allows another start menu item to be selected
      SubmenuDPad ();

      Startmenulist ();

      //Displays the cursor on sceen
      PutGFX (0, 0, 32, 32, cursor, cursorPosition.x, cursorPosition.y);
      PrintScreen ();

      //The following is used to set where the start menu starts on the sceen
      MenuPositionY = 2;
      MenuPositionX = 1;
      i = 0;
    }
}



//The following is used for the system menu in the start menu.  Used to add custom items.
void
drawSettings ()
{
  DesktopIconsActive = 0;
  int Themes = 13;
  int Wallpapers = 14;
  int Setmenu = 15;

  if (MenuSelected.row1 == 1 && MenuSelected.col1 == Wallpapers)
    {				//Cursor is over the exit icon
      PutGFX (0, 0, 100, 15, SubMenuMiddle, (100 * 1 - fourcolumns - 20), (15 * Wallpapers + 7));	//SubMenuMiddle is the image that both the icon and the text of an item in the start menu is dispayed on.
      PutGFX (0, 0, 100, 15, SubMenuSelect, (100 * 1 - fourcolumns - 19), (15 * Wallpapers + 7));	//Puts an overlay over the Text if the mouse cursor is over the item.
      PutText ((100 * 1 - fourcolumns - 10), (15 * Wallpapers + 9), SMWallpapersT, StartSubMenuOverC);	//Displays the name of the item in the Start Menu
      PutText (380, 260, SMWallpapersT, StartSubMenuTypeC);	//Display the type of file in the Status Bar e.g Executable
    }
  else
    {
      PutGFX (0, 0, 100, 15, SubMenuMiddle, (100 * 1 - fourcolumns - 20), (15 * Wallpapers + 7));	//SubMenuMiddle is the image that both the icon and the text of an item in the start menu is dispayed on.
      PutText ((100 * 1 - fourcolumns - 10), (15 * Wallpapers + 9), SMWallpapersT, StartSubMenuC);	//Displays the name of the item in the Start Menu       
    }

  if (MenuSelected.row1 == 1 && MenuSelected.col1 == Themes)
    {				//Cursor is over the exit icon
      PutGFX (0, 0, 100, 15, SubMenuMiddle, (100 * 1 - fourcolumns - 20), (15 * Themes + 7));	//SubMenuMiddle is the image that both the icon and the text of an item in the start menu is dispayed on.
      PutGFX (0, 0, 100, 15, SubMenuSelect, (100 * 1 - fourcolumns - 19), (15 * Themes + 7));	//Puts an overlay over the Text if the mouse cursor is over the item.     
      PutText ((100 * 1 - fourcolumns - 10), (15 * Themes + 9), SMThemesT, StartSubMenuOverC);	//Displays the name of the item in the Start Menu
      PutText (380, 260, SMThemesT, StartSubMenuTypeC);	//Display the type of file in the Status Bar e.g Executable
    }
  else
    {
      PutGFX (0, 0, 100, 15, SubMenuMiddle, (100 * 1 - fourcolumns - 20), (15 * Themes + 7));	//SubMenuMiddle is the image that both the icon and the text of an item in the start menu is dispayed on.
      PutText ((100 * 1 - fourcolumns - 10), (15 * Themes + 9), SMThemesT, StartSubMenuC);	//Displays the name of the item in the Start Menu       
    }

  if (MenuSelected.row1 == 1 && MenuSelected.col1 == Setmenu)
    {				//Cursor is over the exit icon
      PutGFX (0, 0, 100, 15, SubMenuMiddle, (100 * 1 - fourcolumns - 20), (15 * Setmenu + 7));	//SubMenuMiddle is the image that both the icon and the text of an item in the start menu is dispayed on.
      PutGFX (0, 0, 100, 15, SubMenuSelect, (100 * 1 - fourcolumns - 19), (15 * Setmenu + 7));	//Puts an overlay over the Text if the mouse cursor is over the item.     
      PutText ((100 * 1 - fourcolumns - 10), (15 * Setmenu + 9), SMSettingsT, StartSubMenuOverC);	//Displays the name of the item in the Start Menu
      PutText (380, 260, SMSettingsT, StartSubMenuTypeC);	//Display the type of file in the Status Bar e.g Executable
    }
  else
    {
      PutGFX (0, 0, 100, 15, SubMenuMiddle, (100 * 1 - fourcolumns - 20), (15 * Setmenu + 7));	//SubMenuMiddle is the image that both the icon and the text of an item in the start menu is dispayed on.
      PutText ((100 * 1 - fourcolumns - 10), (15 * Setmenu + 9), SMSettingsT, StartSubMenuC);	//Displays the name of the item in the Start Menu       
    }


  //The Following is used to check if the mouse cursor is over an item and then exectute it.
  if (pad.Buttons & PSP_CTRL_CONFIRM && MenuSelected.row1 == 1
      && MenuSelected.col1 == Themes)
    {
      BrowseSkins ();
      stopmenu = 1;
    }

  else if (pad.Buttons & PSP_CTRL_CONFIRM && MenuSelected.row1 == 1
	   && MenuSelected.col1 == Wallpapers)
    {
      BrowseWallpapers ();
      stopmenu = 1;
    }

  else if (pad.Buttons & PSP_CTRL_CONFIRM && MenuSelected.row1 == 1
	   && MenuSelected.col1 == Setmenu)
    {
      SettingsScreen ();
      stopmenu = 1;
    }

  //custom start menu items can be added like below
  /*else if(pad.Buttons & PSP_CTRL_CONFIRM && MenuSelected.row1 == 1 && MenuSelected.col1 == 15){
     ELF_Run("ms0:/PSP/GAME/PSP-OSS/EBOOT.PBP"); 
     stopmenu= 1;
     }
   */

  MenuPositionY += 1;

}

//The following is used to select the submenu
void
Startmenulistover ()
{
  DesktopIconsActive = 0;
  if (cursorPosition.x > 0 && cursorPosition.x < 70 && cursorPosition.y > 187
      && cursorPosition.y < 197)
    {
      PutGFX (0, 0, 70, 10, Start_Menu_Body_Over, 0, 187);
    }
  else if (cursorPosition.x > 0 && cursorPosition.x < 70
	   && cursorPosition.y > 197 && cursorPosition.y < 207)
    {
      PutGFX (0, 0, 70, 10, Start_Menu_Body_Over, 0, 197);
    }
  else if (cursorPosition.x > 0 && cursorPosition.x < 70
	   && cursorPosition.y > 207 && cursorPosition.y < 217)
    {
      PutGFX (0, 0, 70, 10, Start_Menu_Body_Over, 0, 207);
    }
  else if (cursorPosition.x > 0 && cursorPosition.x < 70
	   && cursorPosition.y > 217 && cursorPosition.y < 227)
    {
      PutGFX (0, 0, 70, 10, Start_Menu_Body_Over, 0, 217);
    }
  else if (cursorPosition.x > 0 && cursorPosition.x < 70
	   && cursorPosition.y > 227 && cursorPosition.y < 237)
    {
      PutGFX (0, 0, 70, 10, Start_Menu_Body_Over, 0, 227);
    }
  else if (cursorPosition.x > 0 && cursorPosition.x < 70
	   && cursorPosition.y > 237 && cursorPosition.y < 247)
    {
      PutGFX (0, 0, 70, 10, Start_Menu_Body_Over, 0, 237);
    }
  else if (cursorPosition.x > 0 && cursorPosition.x < 70
	   && cursorPosition.y > 247 && cursorPosition.y < 267)
    {
      PutGFX (0, 0, 70, 10, Start_Menu_Body_Over, 0, 247);
    }
  PutText (5, 187, BrowseT, BrowseC);
  PutText (5, 197, GamesT, GamesC);
  PutText (5, 207, MusicT, MusicC);
  PutText (5, 217, "Videos", MusicC);
  PutText (5, 227, PicturesT, PicturesC);
  PutText (5, 237, SystemT, SystemC);
  PutText (5, 247, QuitT, QuitC);

}

void
Startmenulist ()
{
  DesktopIconsActive = 0;
  right = 0;
  if (pad.Buttons & PSP_CTRL_RIGHT)
    {
      right = 1;
    }
  if (pad.Buttons & PSP_CTRL_CONFIRM || pad.Buttons & PSP_CTRL_RIGHT)
    {
      //Browse
      if (cursorPosition.x > 0 && cursorPosition.x < 70
	  && cursorPosition.y > 187 && cursorPosition.y < 197)
	{
	  mstart = 1;
	  BrowseDirectory ("ms0:/PSP/");
	}
      //Games
      else if (cursorPosition.x > 0 && cursorPosition.x < 70
	       && cursorPosition.y > 197 && cursorPosition.y < 207)
	{
	  mstart = 1;
	  substart = 0;
	  stopmenu = 0;
	  DPad_PositionX = 1;
	  DPad_PositionY = 1;
	  smpage = 1;
	  selectmenu = "ms0:/PSP/GAME/";
	  DesktopIconsActive = 0;
	  StartListMenu ();
	}
      //Music
      else if (cursorPosition.x > 0 && cursorPosition.x < 70
	       && cursorPosition.y > 207 && cursorPosition.y < 217)
	{
	  mstart = 1;
	  substart = 0;
	  stopmenu = 0;
	  DPad_PositionX = 1;
	  DPad_PositionY = 1;
	  smpage = 1;
	  selectmenu = "ms0:/PSP/MUSIC/";
	  DesktopIconsActive = 0;
	  StartListMenu ();
	}
      //Videos
      else if (cursorPosition.x > 0 && cursorPosition.x < 70
	       && cursorPosition.y > 217 && cursorPosition.y < 227)
	{
	  mstart = 1;
	  substart = 0;
	  stopmenu = 0;
	  DPad_PositionX = 1;
	  DPad_PositionY = 1;
	  smpage = 1;
	  selectmenu = "ms0:/PSP/VIDEO/";
	  DesktopIconsActive = 0;
	  StartListMenu ();
	}	
      //Pictures
      else if (cursorPosition.x > 0 && cursorPosition.x < 70
	       && cursorPosition.y > 227 && cursorPosition.y < 237)
	{
	  mstart = 1;
	  substart = 0;
	  stopmenu = 0;
	  DPad_PositionX = 1;
	  DPad_PositionY = 1;
	  smpage = 1;
	  selectmenu = "ms0:/PSP/PHOTO/";
	  DesktopIconsActive = 0;
	  StartListMenu ();
	}
      //System
      else if (cursorPosition.x > 0 && cursorPosition.x < 70
	       && cursorPosition.y > 237 && cursorPosition.y < 247)
	{
	  mstart = 1;
	  substart = 0;
	  stopmenu = 0;
	  DPad_PositionX = 1;
	  DPad_PositionY = 1;
	  smpage = 1;
	  selectmenu = "ms0:/NOTREALFOROURUSEONLY";
	  settings = 3;		//System is used to define how may items we have in this folder
	  DesktopIconsActive = 0;
	  StartListMenu ();
	}

      //Shut down
      else if (cursorPosition.x > 0 && cursorPosition.x < 70
	       && cursorPosition.y > 247 && cursorPosition.y < 257)
	{
	  mstart = 1;
	  stopmenu = 0;
	  ShutDown_Prompt ();
	}
    }

}

void
SubmenuDPad ()
{
  DesktopIconsActive = 0;
  if (substart == 0 && empty != 1 && right == 1)
    {
      cursorPosition.x = 130 - fourcolumns;
      cursorPosition.y = 15 * (substartdpad + 1) - 1;
      substart = 1;
    }
  else
    {
      substart = 1;
      if (empty != 1)
	{
	  //Allows a user to slect an icon using the dpad.
	  if (pad.Buttons & PSP_CTRL_DOWN)
	    {
	      DPad_PositionY++;
	      if (DPad_PositionY >= subdpad + 1)
		{
		  DPad_PositionY = subdpad;
		}
	      if (DPad_PositionY == 1)
		{
		  cursorPosition.y = 15 * substartdpad - 1;
		}
	      else if (DPad_PositionY == 2)
		{
		  cursorPosition.y = 15 * (substartdpad + 1) - 1;
		}
	      else if (DPad_PositionY == 3)
		{
		  cursorPosition.y = 15 * (substartdpad + 2) - 1;
		}
	      else if (DPad_PositionY == 4)
		{
		  cursorPosition.y = 15 * (substartdpad + 3) - 1;
		}
	      else if (DPad_PositionY == 5)
		{
		  cursorPosition.y = 15 * (substartdpad + 4) - 1;
		}
	      else if (DPad_PositionY == 6)
		{
		  cursorPosition.y = 15 * (substartdpad + 5) - 1;
		}
	      else if (DPad_PositionY == 7)
		{
		  cursorPosition.y = 15 * (substartdpad + 6) - 1;
		}
	      else if (DPad_PositionY == 8)
		{
		  cursorPosition.y = 15 * (substartdpad + 7) - 1;
		}
	      else if (DPad_PositionY == 9)
		{
		  cursorPosition.y = 15 * (substartdpad + 8) - 1;
		}
	      else if (DPad_PositionY == 10)
		{
		  cursorPosition.y = 15 * (substartdpad + 9) - 1;
		}
	      else if (DPad_PositionY == 11)
		{
		  cursorPosition.y = 15 * (substartdpad + 10) - 1;
		}
	      else if (DPad_PositionY == 12)
		{
		  cursorPosition.y = 15 * (substartdpad + 11) - 1;
		}
	      else if (DPad_PositionY == 13)
		{
		  cursorPosition.y = 15 * (substartdpad + 12) - 1;
		}
	      else if (DPad_PositionY == 14)
		{
		  cursorPosition.y = 15 * (substartdpad + 13) - 1;
		}
	      else if (DPad_PositionY == 15)
		{
		  cursorPosition.y = 15 * (substartdpad + 14) - 1;
		}
	      else if (DPad_PositionY == 16)
		{
		  cursorPosition.y = 15 * (substartdpad + 15) - 1;
		}

	      PauseVbl (5);
	    }

	  if (pad.Buttons & PSP_CTRL_UP)
	    {
	      DPad_PositionY--;
	      if (DPad_PositionY <= 1)
		{
		  DPad_PositionY = 2;
		}
	      if (DPad_PositionY == 1)
		{
		  cursorPosition.y = 15 * substartdpad - 1;
		}
	      else if (DPad_PositionY == 2)
		{
		  cursorPosition.y = 15 * (substartdpad + 1) - 1;
		}
	      else if (DPad_PositionY == 3)
		{
		  cursorPosition.y = 15 * (substartdpad + 2) - 1;
		}
	      else if (DPad_PositionY == 4)
		{
		  cursorPosition.y = 15 * (substartdpad + 3) - 1;
		}
	      else if (DPad_PositionY == 5)
		{
		  cursorPosition.y = 15 * (substartdpad + 4) - 1;
		}
	      else if (DPad_PositionY == 6)
		{
		  cursorPosition.y = 15 * (substartdpad + 5) - 1;
		}
	      else if (DPad_PositionY == 7)
		{
		  cursorPosition.y = 15 * (substartdpad + 6) - 1;
		}
	      else if (DPad_PositionY == 8)
		{
		  cursorPosition.y = 15 * (substartdpad + 7) - 1;
		}
	      else if (DPad_PositionY == 9)
		{
		  cursorPosition.y = 15 * (substartdpad + 8) - 1;
		}
	      else if (DPad_PositionY == 10)
		{
		  cursorPosition.y = 15 * (substartdpad + 9) - 1;
		}
	      else if (DPad_PositionY == 11)
		{
		  cursorPosition.y = 15 * (substartdpad + 10) - 1;
		}
	      else if (DPad_PositionY == 12)
		{
		  cursorPosition.y = 15 * (substartdpad + 11) - 1;
		}
	      else if (DPad_PositionY == 13)
		{
		  cursorPosition.y = 15 * (substartdpad + 12) - 1;
		}
	      else if (DPad_PositionY == 14)
		{
		  cursorPosition.y = 15 * (substartdpad + 13) - 1;
		}
	      else if (DPad_PositionY == 15)
		{
		  cursorPosition.y = 15 * (substartdpad + 14) - 1;
		}
	      else if (DPad_PositionY == 16)
		{
		  cursorPosition.y = 15 * (substartdpad + 15) - 1;
		}

	      PauseVbl (5);
	    }

	  if (pad.Buttons & PSP_CTRL_LEFT)
	    {
	      DPad_PositionX--;
	      if (DPad_PositionX < 1)
		{
		  cursorPosition.x = 35;
		  cursorPosition.y = (DPad_Position * 10) + 190;
		  stopmenu2 = 1;
		  stopmenu = 1;
		  StartMenu ();
		}

	      if (DPad_PositionX == 1)
		{
		  cursorPosition.x = 130 - fourcolumns;
		}
	      else if (DPad_PositionX == 2)
		{
		  cursorPosition.x = 230 - fourcolumns;
		}
	      else if (DPad_PositionX == 3)
		{
		  cursorPosition.x = 330 - fourcolumns;
		}
	      else if (DPad_PositionX == 4)
		{
		  cursorPosition.x = 430 - fourcolumns;
		}

	      PauseVbl (10);
	    }

	  if (pad.Buttons & PSP_CTRL_RIGHT)
	    {
	      DPad_PositionX++;
	      if (startcounter == 1)
		{
		  if (DPad_PositionX >= 2)
		    {
		      DPad_PositionX = 1;
		    }
		}
	      else if (startcounter == 2)
		{
		  if (DPad_PositionX >= 3)
		    {
		      DPad_PositionX = 2;
		    }
		}
	      else if (startcounter == 3)
		{
		  if (DPad_PositionX >= 4)
		    {
		      DPad_PositionX = 3;
		    }
		}
	      else if (startcounter == 4)
		{
		  if (DPad_PositionX >= 5)
		    {
		      DPad_PositionX = 4;
		    }
		}

	      if (DPad_PositionX == 1)
		{
		  cursorPosition.x = 130 - fourcolumns;
		}
	      else if (DPad_PositionX == 2)
		{
		  cursorPosition.x = 230 - fourcolumns;
		}
	      else if (DPad_PositionX == 3)
		{
		  cursorPosition.x = 330 - fourcolumns;
		}
	      else if (DPad_PositionX == 4)
		{
		  cursorPosition.x = 430 - fourcolumns;
		}

	      PauseVbl (10);
	    }
	}
      else
	{
	  if (pad.Buttons & PSP_CTRL_RIGHT || pad.Buttons & PSP_CTRL_LEFT)
	    {
	      cursorPosition.x = 35;
	      cursorPosition.y = (DPad_Position * 10) + 190;
	      stopmenu2 = 1;
	      StartMenu ();
	    }
	  else if (pad.Buttons & PSP_CTRL_UP)
	    {
	      DPad_Position--;
	      cursorPosition.x = 35;
	      cursorPosition.y = (DPad_Position * 10) + 190;
	      stopmenu2 = 1;
	      StartMenu ();
	    }
	  else if (pad.Buttons & PSP_CTRL_DOWN)
	    {
	      DPad_Position++;
	      cursorPosition.x = 35;
	      cursorPosition.y = (DPad_Position * 10) + 190;
	      stopmenu2 = 1;
	      StartMenu ();
	    }
	}
    }
}
