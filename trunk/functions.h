/*
  PSP-OSS
*/

struct MessageWindow
{
  int title;
  int message;
  int x;
  int y;
};

//PSP-OSS functions
void PauseVbl (unsigned int tempo);

//Load an .ELF
//void loadELF(const char* filename); 
// Moved to Actions.c

void CopyExecute (const char *zFileSrc, const char *zFileDest);

void SetWallpaper (const char *NewWallpaper);

int FileCheck (const char *filename);

//Load and start a module (PRX)
int LoadStartModule (char *path);

//Is USB activated?
//Moved
//void DrawUSBState();

//Battery status
//Moved
//void DrawBattery(int scePowerIsPowerOnline, int scePowerGetBatteryLifePercent, int scePowerIsLowBattery);

void PrintAscii ();

//Animate SKY as wallpaper
void InitAnimatedSkyBackground ();
void AnimateSkyBackground ();

void MessageWindow ();
void InitMessageWindow ();

void FadeScreenMessage ();

void GrabComicGarfield ();

void InitFullscreenWindow (int title);
void FullscreenWindow (int analogX, int analogY, int Buttons);

void Write_config (const char *filename, const char *content);

//Moved
//void DrawMediaStatus(int Buttons);
//void drawtime ();
//void initTimezone ();
