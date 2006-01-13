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
PSP-OSS
*/

//PSP-OSS functions
#include "main.h"
#include "functions.h"

void
PauseVbl (unsigned int tempo)
{
  unsigned int i;

  for (i = 0; i <= tempo; i++)
    {
      sceDisplayWaitVblankStart ();
    }
}


/* Define buffer size */
#define BUFSIZE      65536
static char buf[BUFSIZE];

void
CopyExecute (const char *zFileSrc, const char *zFileDest)
{
  int fd1, fd2, len;

  //Read
  fd1 = sceIoOpen (zFileSrc, PSP_O_RDONLY, 0);

  //Write
  fd2 = sceIoOpen (zFileDest, PSP_O_WRONLY | PSP_O_CREAT | PSP_O_TRUNC, 0777);

  //If we cant open the file, display a error. Most likely the file doesnt excist
  if (fd1 < 0)
    {
      pspDebugScreenInit ();

      pspDebugScreenSetBackColor (0x00FF0000);	//Blue
      pspDebugScreenSetTextColor (0xFFFFFFFF);	//White

      pspDebugScreenClear ();

      pspDebugScreenPrintf ("Ooops!\n");
      pspDebugScreenPrintf
	("Can't find source file (%s). Will exit in a few seconds...\n",
	 zFileSrc);
      PauseVbl (10 * 60);
      Reboot ();
    }

  while (1)
    {
      len = sceIoRead (fd1, buf, BUFSIZE);
      if (len == 0)
	break;
      sceIoWrite (fd2, buf, len);
    }

  sceIoClose (fd1);
  sceIoClose (fd2);
}


int
FileCheck (const char *filename)
{

  SceUID file;			//This is where we store the files we open

  file = sceIoOpen (filename, PSP_O_RDONLY, 0);	//Try to open the file

  //If it doesnt excist
  if (file < 0)
    {
      sceIoClose (file);	//Close the open file when we're finished with it
      return 0;
    }
  else
    {
      sceIoClose (file);	//Close the open file when we're finished with it
      return 1;
    }
}

//Load and start a module (PRX)
int
LoadStartModule (char *path)
{
  u32 loadResult;
  u32 startResult;
  int status;

  loadResult = sceKernelLoadModule (path, 0, NULL);
  if (loadResult & 0x80000000)
    return -1;
  else
    startResult = sceKernelStartModule (loadResult, 0, NULL, &status, NULL);

  if (loadResult != startResult)
    return -2;

  return 0;
}

//Print ASCII
void
PrintAscii ()
{
  pspDebugScreenSetTextColor (DARK_RED);	//Dark Red
  pspDebugScreenPrintf ("PSP-OSS\n\n");
  /*
     pspDebugScreenSetTextColor(0x00FF0000);//Blue
     pspDebugScreenPrintf("                                                   \n");
     pspDebugScreenPrintf(" *****   ****  *****         *****     ****   **** \n");
     pspDebugScreenPrintf(" ****** ****** ******       *******   ****** ******\n");
     pspDebugScreenPrintf(" **  ** **  *  **  **      **    ***  **  *  **  * \n");
     pspDebugScreenPrintf(" **  **  **    **  **     **      **   **     **   \n");
     pspDebugScreenPrintf(" ******   **   ****** *** **      **    **     **  \n");
     pspDebugScreenPrintf(" *****      ** *****  *** **      **     **     ** \n");
     pspDebugScreenPrintf(" **         ** **         ***    **      **     ** \n");
     pspDebugScreenPrintf(" **     ****** **          *******   ****** ****** \n");
     pspDebugScreenPrintf(" **      ****  **           *****     ****   ****  \n");
     pspDebugScreenPrintf("                  WwW.PsP-OsS.CoM                  \n");
     pspDebugScreenPrintf(" -PlayStation Portable Open-Source Shell           \n");
     pspDebugScreenPrintf("                             Version 0,1           \n");
     pspDebugScreenPrintf("                                                   \n");
   */
}


void
OpenFile (const char *filename)
{
  char *suffix = strrchr (filename, '.');

  if (!suffix)
    {
      //Something went wrong
    }

  else
    {

      if (stricmp (suffix, ".jpg") == 0 || stricmp (suffix, ".jpeg") == 0
	  || stricmp (suffix, ".thm") == 0)
	{
	  ViewImage (filename);
	}
      else if (stricmp (suffix, ".png") == 0)
	{
	  ViewImage (filename);
	}
      else if (stricmp (suffix, ".mp3") == 0 || stricmp (suffix, ".ogg") == 0)
	{
	  Audio_Play (filename);
	  PauseVbl (1 * 60);
	}
      else if (stricmp (suffix, ".pbp") == 0 || stricmp (suffix, ".elf") == 0
	       || stricmp (suffix, ".psp") == 0)
	{
	  ELF_Run (filename);
	}
      else if (stricmp (suffix, ".lua") == 0)
	{
	  LUA_Run (filename);
	}
      //Shortcut
      else if (stricmp (suffix, ".pol") == 0 || stricmp (suffix, ".ql") == 0)
	{
	  Shortcut_Run (filename);
	}
      
         else {
         MessageWindow("Unknown", "Unknown filetype");
         }
       
    }
}



void
GetUserInput ()
{
  //Read what keys are pressed
  sceCtrlReadBufferPositive (&pad, 1);

  //Get cursor position
  cursorHandler (pad.Lx, pad.Ly);
}

void
ShutDown ()
{
  scePowerSetClockFrequency (222, 222, 111);
  pspAudioEnd ();
  sceKernelExitGame ();
}

void
Reboot ()
{
  char *filename;
  filename = "ms0:/PSP-OSS/SYSTEM/PSP-OSS.elf";

  struct SceKernelLoadExecParam execParam;
  const u32 total_length = (strlen (filename) + 1);

  execParam.args = total_length;
  execParam.argp = (const char *) filename;
  execParam.key = NULL;
  execParam.size = sizeof (execParam) + total_length;

  pspAudioEnd ();
  sceKernelLoadExec (filename, &execParam);
}

//Code from http://forums.ps2dev.org/viewtopic.php?t=4567&sid=b9b535d20d2dca10b26aa1457eef9b5b
float
GetRAMFree ()
{
  float ram;
  //a hacky little way to estimate RAM left to use
  int ramAdd[320];
  int i = 0;
  for (i = 0; i < 320; i++)
    {
      ramAdd[i] = malloc (100000);
      if (ramAdd[i] == 0)
	{			//malloc failed 
	  ram = (float) i;
	  int z = 0;
	  for (z = 0; z < i; z++)
	    {
	      free (ramAdd[z]);
	    }
	  break;
	}
    }
  return ram / 10;
}

void
Write_config (const char *filename, const char *content)
{
  SceUID file;
  file = sceIoOpen (filename, PSP_O_WRONLY | PSP_O_CREAT | PSP_O_TRUNC, 0777);

  sceIoWrite (file, content, strlen (content));
  sceIoClose (file);
}
