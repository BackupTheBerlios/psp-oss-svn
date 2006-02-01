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

void StartUp (void);
void StartListMenu ();
void findStartMenu ();
void drawSettings ();
void Startmenulist ();
void Startmenulistover ();
void SubmenuDPad ();

int numberoffilesinlist;
char *startitemname[256];
char *isdir[256];

struct MenuPosition
{
  int row1;
  int col1;
} MenuSelected;

#define menuXSize 100
#define menuYSize 15

int FilebrowserRightclickActive;
int FilebrowserRightclickPosX;
int FilebrowserRightclickPosY;
int RCMdir;
const char *FilebrowserRightclickFilepath;
const char *FilebrowserRightclickFilename;
