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

void MessageWindow (int MessageWindowHeader, int MessageWindowMessage);
void FadeScreenMessage (int FadeMessageWindowHeader,
			int FadeMessageWindowMessageLine1,
			int FadeMessageWindowMessageLine2,
			int FadeMessageWindowMessageLine3);
void Configuration ();
void DrawFullscreenWindow (int FullscreenWindowHeader);
void StartMenu ();
void StartSubMenu ();

int MessageWindowX;
int MessageWindowY;
