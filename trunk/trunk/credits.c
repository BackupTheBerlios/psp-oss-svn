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

#include "functions.h"
#include "main.h"

void
Credits ()
{
  InitAnimatedSkyBackground ();

  int TextPosition1 = 1;
  int TextPosition2 = 1;

  int Textline1 = "PSP-OSS";
  int Textline2 = OSSVersion;
  int Textline3 = "WwW.PsP-OsS.com";
  int Textline4 = "Coded by:";
  int Textline5 = "ELZ";
  int Textline6 = "Canti";
  int Textline7 = "Daurnimator";
  int Textline8 = "Mondy";
  int Textline8AndAHalf = "INK";
  int Textline9 = "GFX by:";
  int Textline10 = "System";
  int Textline11 = "Posty";
  int Textline12 = "Enjoy ;)";
  int Textline13 = "Check PSP-OSS[DOT]COM for updates!";
  int Textline14 = "Oh, I almost forgot; FUCK YOU SASUKE!";


  while (1)
    {
      AnimateSkyBackground ();
      GetUserInput ();

      PutTextFont (TextPosition2, 262, "PSP-OSS - WwW.PsP-OsS.CoM", DARK_RED);
      PutTextFont (TextPosition2, 0, "PSP-OSS - WwW.PsP-OsS.CoM", DARK_RED);

      PutTextFont (5, TextPosition1, Textline1, BLACK);
      PutTextFont (20, (TextPosition1 + 10), Textline2, RED);
      PutTextFont (40, (TextPosition1 + 20), Textline3, RED);

      PutTextFont (5, (TextPosition1 + 50), Textline4, ORANGE);
      PutTextFont (5, (TextPosition1 + 60), Textline5, CYAN);
      PutTextFont (5, (TextPosition1 + 70), Textline6, CYAN);
      PutTextFont (5, (TextPosition1 + 80), Textline7, CYAN);
      PutTextFont (5, (TextPosition1 + 90), Textline8, CYAN);
      PutTextFont (5, (TextPosition1 + 100), Textline8AndAHalf, CYAN);

      PutTextFont (5, (TextPosition1 + 130), Textline9, ORANGE);
      PutTextFont (5, (TextPosition1 + 140), Textline10, CYAN);
      PutTextFont (5, (TextPosition1 + 150), Textline11, CYAN);

      PutTextFont (5, (TextPosition1 + 190), Textline12, BLUE);

      PutTextFont (5, (TextPosition1 + 230), Textline13, BLACK);

      PutTextFont (5, (TextPosition1 + 250), Textline14, BLACK);

      PauseVbl (5) TextPosition2++;

      if (TextPosition1 == 272)
	{
	  TextPosition1 = 0;
	}

      if (TextPosition2 == 480)
	{
	  TextPosition2 = 0;
	}

      PrintScreen ();

      if (pad.Buttons & PSP_CTRL_DOWN)
	{
	  TextPosition1++;
	}
      if (pad.Buttons & PSP_CTRL_UP)
	{
	  TextPosition1--;
	}


      if (pad.Buttons & PSP_CTRL_START)
	{
	  break;
	}
    }
}
