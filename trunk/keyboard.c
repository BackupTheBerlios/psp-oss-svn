#include "keyboard.h"
#include "main.h"
#include "functions.h"

void
Keyboard_CharsetLowercase ()
{
  Keyboard_Characters = "abcdefghijklmnopqrstuvwxyz.,:   ";
  Keyboard_Charset = "Lowercase";
}

void
Keyboard_CharsetUppercase ()
{
  Keyboard_Characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ.,:   ";
  Keyboard_Charset = "Uppercase";
}

void
Keyboard_CharsetOther ()
{
  Keyboard_Characters = "1234567890!?#%&/()[]=-+*^_$    ";
  Keyboard_Charset = "Other";
}

int
Keyboard (char *Keyboard_Output_Temp)
{

  Keyboard_CurrentKey = 1;
  Keyboard_Characters = 0;
  Keyboard_CharsetLowercase ();
  PauseVbl (30);		//Pause for half a second

  while (1)
    {
      GetUserInput ();

      PutGFX (0, 0, 480, 270, wallpaper, 0, 0);	//Wallpaper
      PutGFX (0, 0, 480, 15, Keyboard_Output, 0, 242);
      PutTextFont (5, 245, Keyboard_Output_Temp, KeyboardC);

      Keyboard_ButtonTemp = 1;

      while (Keyboard_ButtonTemp < 33)
	{
	  if (Keyboard_CurrentKey == Keyboard_ButtonTemp)
	    {
	      PutGFX (0, 0, 15, 15, Keyboard_Button2,(15 * (Keyboard_ButtonTemp - 1)), 257);
	    }
	  else
	    {
	      PutGFX (0, 0, 15, 15, Keyboard_Button1,(15 * (Keyboard_ButtonTemp - 1)), 257);
	    }

	  char buffer[10];
	  sprintf (buffer, "%c",Keyboard_Characters[(Keyboard_ButtonTemp - 1)]);
	  PutTextFont ((15 * (Keyboard_ButtonTemp - 1) + 3), 260, buffer,Keyboard2C);

	  Keyboard_ButtonTemp += 1;
	}

      if (pad.Buttons != old_buttons)
	{
	  old_buttons = pad.Buttons;

	  if (pad.Buttons & PSP_CTRL_CONFIRM&& strlen (Keyboard_Output_Temp) < 50)
	    {
	    	int size;
	    	size = strlen (Keyboard_Output_Temp);
	      Keyboard_Output_Temp[size] =	Keyboard_Characters[(Keyboard_CurrentKey - 1)];
	      Keyboard_Output_Temp[size+1] = '\0';	      
	    }

	  //Space
	  if (pad.Buttons & PSP_CTRL_TRIANGLE
	      && strlen (Keyboard_Output_Temp) < 50)
	    {
	      Keyboard_Output_Temp[strlen (Keyboard_Output_Temp)] = ' ';
	    }

	  //Delete
	  if (pad.Buttons & PSP_CTRL_SQUARE)
	    {
	      Keyboard_Output_Temp[strlen (Keyboard_Output_Temp) - 1] = 0;
	    }


	  //Move right
	  if (pad.Buttons & PSP_CTRL_RIGHT)
	    {

	      Keyboard_CurrentKey += 1;

	      if (Keyboard_CurrentKey == 34)
		{
		  Keyboard_CurrentKey = 1;
		}
	    }

	  //Move left
	  if (pad.Buttons & PSP_CTRL_LEFT)
	    {

	      Keyboard_CurrentKey -= 1;

	      if (Keyboard_CurrentKey == 0)
		{
		  Keyboard_CurrentKey = 33;
		}
	    }

	  //Done
	  if (pad.Buttons & PSP_CTRL_START)
	    {
	      return Keyboard_Output_Temp;
	    }


	  //Change charset
	  if (pad.Buttons & PSP_CTRL_SELECT)
	    {
	      if (Keyboard_Charset == "Lowercase")
		{
		  Keyboard_CharsetUppercase ();
		}
	      else if (Keyboard_Charset == "Uppercase")
		{
		  Keyboard_CharsetOther ();
		}
	      else if (Keyboard_Charset == "Other")
		{
		  Keyboard_CharsetLowercase ();
		}
	    }
	}
      //Fast right
      if (pad.Buttons & PSP_CTRL_RTRIGGER)
	{

	  Keyboard_CurrentKey += 1;

	  if (Keyboard_CurrentKey == 34)
	    {
	      Keyboard_CurrentKey = 1;
	    }
	}

      //Fast left
      if (pad.Buttons & PSP_CTRL_LTRIGGER)
	{

	  Keyboard_CurrentKey -= 1;

	  if (Keyboard_CurrentKey == 0)
	    {
	      Keyboard_CurrentKey = 33;
	    }
	}


      PutGFX (0, 0, 32, 32, cursor, cursorPosition.x, cursorPosition.y);
      PrintScreen ();
    }
}
