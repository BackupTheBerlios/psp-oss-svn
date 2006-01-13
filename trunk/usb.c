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
#include "usb.h"

void
USB_Mode ()
{
  //Activate USB
  sceUsbStart (PSP_USBBUS_DRIVERNAME, 0, 0);
  sceUsbStart (PSP_USBSTOR_DRIVERNAME, 0, 0);
  sceUsbstorBootSetCapacity (0x800000);
  sceUsbActivate (0x1c8);

  while (1)
    {
      usbState = sceUsbGetState ();

      //USB active
      if (usbState & PSP_USB_CONNECTION_ESTABLISHED)
	{
	  FadeScreenMessage ("USB Mode", "USB active.", "", "");
	}

      //Cable connected, but USB not active
      else if (usbState & PSP_USB_CABLE_CONNECTED)
	{
	  FadeScreenMessage ("USB Mode", "Please wait...", "", "");
	}

      //USB not active. most likely because of no USB cable connected.
      else
	{
	  FadeScreenMessage ("USB Mode", "Please connect an USB cable.", "",
			     "");
	}

      PrintScreen ();

      //Get key input
      GetUserInput ();

      if (pad.Buttons & PSP_CTRL_START || pad.Buttons & PSP_CTRL_BACK)
	{
	  sceUsbStop (PSP_USBSTOR_DRIVERNAME, 0, 0);
	  sceUsbDeactivate ();
	  frtd = 1;		//Update desktop
	  break;
	}
    }
}
