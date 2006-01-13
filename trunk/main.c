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

//PSP-OSS Main code
#include "main.h"

#include "startup.h"
#include "cursor.h"
#include "actions.h"
#include "functions.h"
#include "keyboard.h"
#include "desktop.h"
#include "filebrowser.h"
#include "settings.h"

PSP_MODULE_INFO ("PSP-OSS", 0x1000, 1, 1);	// 0x1000 = Kernel MODE
PSP_MAIN_THREAD_ATTR (0);	// 0 for kernel mode too

//In case something goes wrong, this is what will be displayed
void
BlueScreen (PspDebugRegBlock * regs)
{
  disableGraphics ();
  pspDebugScreenInit ();
  pspDebugScreenClear ();

  PrintAscii ();
  pspDebugScreenSetTextColor (WHITE);	//White
  pspDebugScreenPrintf ("Something went wrong...\n");

  int check = FileCheck ("ms0:/PSP-OSS/CRASHED");
  if (check == 0)
    {
      Write_config ("ms0:/PSP-OSS/CRASHED",
		    "OH NOES! PSP-OSS DIED! LYKE OMGZ!");
      pspDebugScreenPrintf ("Rebooting in ");
      pspDebugScreenPrintf ("3..");
      PauseVbl (60);
      pspDebugScreenPrintf ("2..");
      PauseVbl (60);
      pspDebugScreenPrintf ("1..");
      PauseVbl (60);
      pspDebugScreenSetTextColor (RED);	//Red
      pspDebugScreenPrintf ("NOW!");
      pspDebugScreenSetTextColor (WHITE);	//And back to white, just in case...
      Reboot ();
    }
  else
    {
      pspDebugScreenPrintf ("Can't boot... \n");
      pspDebugScreenPrintf ("Exiting in ");
      pspDebugScreenPrintf ("3..");
      PauseVbl (60);
      pspDebugScreenPrintf ("2..");
      PauseVbl (60);
      pspDebugScreenPrintf ("1..");
      PauseVbl (60);
      pspDebugScreenSetTextColor (RED);	//Red
      pspDebugScreenPrintf ("NOW!");
      pspDebugScreenSetTextColor (WHITE);	//And back to white, just in case...
      ShutDown ();
    }
}


/*
This is our main loop
*/
void
osLoop ()
{

  while (1)
    {

      //Get key input
      GetUserInput ();

      //If the desktop is active, display it.
      if (DesktopActive == 1)
	{
	  DoActiveDesktop ();

	  if (pad.Buttons & PSP_CTRL_CONFIRM)
	    {
	      Execute ();
	    }
	  if (pad.Buttons & PSP_CTRL_TRIANGLE)
	    {
	      RightClick_Desktop (cursorPosition.x, cursorPosition.y);
	    }


	  //Toggle wallpapers
	  if (toggle_wallpapers == "LRT")
	    {
	      if (pad.Buttons & PSP_CTRL_RTRIGGER)
		{
		  Toggle_Wallpapers ("R");
		}
	      else if (pad.Buttons & PSP_CTRL_LTRIGGER)
		{
		  Toggle_Wallpapers ("L");
		}
	    }
	  else if (toggle_wallpapers == "SEL")
	    {
	      if (pad.Buttons & PSP_CTRL_SELECT)
		{
		  if (pad.Buttons & PSP_CTRL_RTRIGGER)
		    {
		      Toggle_Wallpapers ("R");
		    }
		  else if (pad.Buttons & PSP_CTRL_LTRIGGER)
		    {
		      Toggle_Wallpapers ("L");
		    }
		}
	    }
	}
      //Display our cursor.
      //Remember to display the cursor last, so it'll get at top.
      PutGFX (0, 0, 32, 32, cursor, cursorPosition.x, cursorPosition.y);

      //Print everything to screen :)
      PrintScreen ();

    }
}

/*
This is where we start.
*/
int
main (int argc, char *argv[])
{
  pspKernelSetKernelPC ();

  ebootpath = argv[0];

  //In case something goes wrong, we got an error message to display
  pspDebugInstallErrorHandler (BlueScreen);
  
  SceUID file;
  file = sceIoOpen ("ms0:/PSP-OSS/SYSTEM/CONFIG/CALLBACK.cfg", PSP_O_RDONLY, 0);
  char callback[1];
  sceIoRead (file, callback, 1);
  callback[1] = 0x00;
  sceIoClose (file);
  
  if (strcmp (callback, "1") == 0)
    {
		Write_config("ms0:/PSP-OSS/SYSTEM/CONFIG/CALLBACK.cfg", "0");
  	Reboot ();
  }
  else
  {
  	//Startup code. Display bootup screen, load images, init gfx.
  	StartUp ();
  }

  //Wlan drivers
  nlhLoadDrivers (&module_info);

  //Did we crash last time?
  int check = FileCheck ("ms0:/PSP-OSS/CRASHED");
  if (check == 1)
    {
      sceIoRemove ("ms0:/PSP-OSS/CRASHED");
      MessageWindow ("Sorry", "Sorry about the crash.");
    }

  //Our main loop
  osLoop ();
}
