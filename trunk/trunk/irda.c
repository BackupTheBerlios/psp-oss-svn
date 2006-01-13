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
// InfaRed PSP-2-PSP Communication

#include "main.h"
#include "irda.h"

void
IrdaChat ()
{
  int a = 0;
  int b = a;
  DesktopIconsActive = 0;

  int fd = sceIoOpen ("irda0:", PSP_O_RDWR, 0);
  char buffer[100];

  while (1)
    {
      GetUserInput ();
      DrawFullscreenWindow ("IRDA Chat");

      if (pad.Buttons & PSP_CTRL_CONFIRM)
	{
	  //Get input
	  unsigned char message;
	  message = Keyboard ("");

	  //Send it
	  unsigned char SendData = message >> 8;
	  sceIoWrite (fd, &SendData, 1);

	  a++;
	  int ReciveData = SendData << 8;
	  IrdaChatMessage[a] = ReciveData;
	}

      if (pad.Buttons & PSP_CTRL_BACK)
	{
	  DesktopIconsActive = 1;
	  sceIoClose (fd);
	  break;
	}

      //Check for data
      unsigned char data;
      int len = sceIoRead (fd, &data, 1);
      int ReciveData = data << 8;

      //Recive data
      if (len == 1)
	{
	  a++;
	  IrdaChatMessage[a] = ReciveData;
	}

      //Display messages
      b = 0;
      while (b < a)
	{
	  //For some reason this line crashes it :/
	  //PutTextFont(5,(15*(b+1)),IrdaChatMessage[b],BLACK);

	  PutTextFont (5, (15 * (b + 1)), "Message sent/recived", BLACK);
	  b++;
	}

      PutGFX (0, 0, 32, 32, cursor, cursorPosition.x, cursorPosition.y);
      PrintScreen ();
    }


}
